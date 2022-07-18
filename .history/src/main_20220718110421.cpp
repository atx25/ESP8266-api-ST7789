#include <Arduino.h>
#include <ESP8266HTTPClient.h> 
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TFT_eSPI.h>
#include <Tools/Create_Smooth_Font/Create_font/FontFiles/fontsimkai_30.h>
#define BLK 150
TFT_eSPI tft = TFT_eSPI();
const char* AP_SSID     = "HUAWEI-0409E6";         // XXXXXX -- 使用时请修改为当前你的 wifi ssid
const char* AP_PSK = "15660090095";        // XXXXXX -- 使用时请修改为当前你的 wifi 密码
WiFiClientSecure client; 
HTTPClient https; //创建一个网络对象
String location="411627";
String key="d4055a0ac0848d29ab8bb6e4ad498d7a";
String extensions="all";           
const char* city[2];
const char* tianqiday[2];
const char*tianqinight[2];
const char* date[2];
const char* tianqi;
const char* tempday[2];//白天的温度，最高气温
const char* tempnight[2];//夜间温度，最低气温

void wifi_start_connect()              //连接WIFI
{
  WiFi.mode(WIFI_STA);                 //设置esp8266 工作模式 
  Serial.println("Connecting to ");    //写几句提示
  Serial.println(AP_SSID);
  WiFi.begin(AP_SSID, AP_PSK);         //连接wifi
  WiFi.setAutoConnect(true);
  while (WiFi.status()!= WL_CONNECTED) //这个函数是wifi连接状态，返回wifi链接状态
        {  
         delay(500);
         tft.init();                           //初始化
          tft.setRotation(0);
          tft.setTextColor(TFT_BLUE);         //设置文本颜色为黑色
          tft.loadFont(fontsimkai_30);
          tft.drawCentreString("content...",100,100,50);
          tft.unloadFont();
          Serial.print(".");
        }
  Serial.println("WiFi connected IP is");
  Serial.println(WiFi.localIP()); 
}

//显示天气
void xianshi(const char* tianqiday[],const char* tianqinightp[]){
  tft.init();                           //初始化
  tft.setRotation(0);
  tft.fillScreen(TFT_WHITE);            //屏幕颜色
  tft.setTextColor(TFT_YELLOW);         //设置文本颜色为黄色
  tft.loadFont(fontsimkai_30);
  tft.drawString(date[0],0,20);
  String s=String(tianqiday[0]) +"转"+ String(tianqinight[0]);
  const char* yubao=s.c_str();
  tft.drawString(yubao,0,60);
  tft.unloadFont();
}

//解析程序,预报未来3天的天气
void putjson(const char* content){
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(4) + 2*JSON_OBJECT_SIZE(5) + 4*JSON_OBJECT_SIZE(10) + 700;
  DynamicJsonBuffer jsonBuffer(capacity);

  const char* json = content;

  JsonObject& root = jsonBuffer.parseObject(json);

  const char* status = root["status"]; // "1"
  const char* count = root["count"]; // "1"
  const char* info = root["info"]; // "OK"
  const char* infocode = root["infocode"]; // "10000"

  JsonObject& forecasts_0 = root["forecasts"][0];
  const char* forecasts_0_city = forecasts_0["city"]; // "东城区"
  const char* forecasts_0_adcode = forecasts_0["adcode"]; // "110101"
  const char* forecasts_0_province = forecasts_0["province"]; // "北京"
  const char* forecasts_0_reporttime = forecasts_0["reporttime"]; // "2022-07-17 15:02:57"

  JsonArray& forecasts_0_casts = forecasts_0["casts"];

  JsonObject& forecasts_0_casts_0 = forecasts_0_casts[0];
//当天的天气
  const char* forecasts_0_casts_0_date = forecasts_0_casts_0["date"]; // "2022-07-17"
  const char* forecasts_0_casts_0_dayweather = forecasts_0_casts_0["dayweather"]; // "晴"
  const char* forecasts_0_casts_0_nightweather = forecasts_0_casts_0["nightweather"]; // "晴"
  const char* forecasts_0_casts_0_daytemp = forecasts_0_casts_0["daytemp"]; // "35"
  const char* forecasts_0_casts_0_nighttemp = forecasts_0_casts_0["nighttemp"]; // "23"
//明天的天气
  JsonObject& forecasts_0_casts_1 = forecasts_0_casts[1];
  const char* forecasts_0_casts_1_date = forecasts_0_casts_1["date"]; // "2022-07-18"
  const char* forecasts_0_casts_1_dayweather = forecasts_0_casts_1["dayweather"]; // "晴"
  const char* forecasts_0_casts_1_nightweather = forecasts_0_casts_1["nightweather"]; // "多云"
  const char* forecasts_0_casts_1_daytemp = forecasts_0_casts_1["daytemp"]; // "35"
  const char* forecasts_0_casts_1_nighttemp = forecasts_0_casts_1["nighttemp"]; // "22"

//填充
 //城市
  city[0] =  (forecasts_0_province);
  city[1] =  (forecasts_0_city);
 //今日天气
  date[0] =  (forecasts_0_casts_0_date);
  tianqiday[0] =  (forecasts_0_casts_0_dayweather);
  tianqinight[0] =  (forecasts_0_casts_0_nightweather);
  tempday[0] =  (forecasts_0_casts_0_daytemp);
  tempnight[0] =  (forecasts_0_casts_0_nighttemp);
 //明日天气
  date[1] =  (forecasts_0_casts_1_date);
  tianqiday[1] =  (forecasts_0_casts_1_dayweather);
  tianqinight[1] =  (forecasts_0_casts_1_nightweather);
  tempday[1] =  (forecasts_0_casts_1_daytemp);
  tempnight[1] =  (forecasts_0_casts_1_nighttemp);
  tianqi =  (forecasts_0_casts_1_daytemp);
  xianshi(tianqiday,tianqinight);
  Serial.println(forecasts_0_province);
  Serial.println(forecasts_0_city);
  Serial.println(forecasts_0_casts_0_date);
}
//连接服务器查询天气，并在串口输出
void getapi(){
  client.setInsecure();
  Serial.println("[HTTPS] begin...");
  String url = "https://restapi.amap.com/v3/weather/weatherInfo?&city="
                + location + "&key=" + key + "&extensions=" + extensions;
  if(https.begin(client,url)){
    Serial.println("[HTTPS] GET...");
    int httpCode = https.GET();
    if(httpCode >= 0){
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) { // 服务器响应
        String str = https.getString();
        const char* s=str.c_str();
        putjson(s);
      }
    } else { // 错误返回负值
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
    }
  else { // HTTPS连接失败
    Serial.printf("[HTTPS] Unable to connect\n");
  }
  xianshi(tianqiday,tianqinight); 
  delay(10000);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);//设置波特率
  client.setTimeout(5000);//设置服务器连接超时
}
void loop() {
  while(1){
    getapi();
    xianshi(tianqiday,tianqinight); 
  }
}