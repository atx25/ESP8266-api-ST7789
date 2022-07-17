#include <Arduino.h>
#include <ESP8266HTTPClient.h> 
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
const char* AP_SSID     = "HUAWEI-0409E6";         // XXXXXX -- 使用时请修改为当前你的 wifi ssid
const char* AP_PSK = "15660090095";        // XXXXXX -- 使用时请修改为当前你的 wifi 密码
WiFiClientSecure client; 
HTTPClient https; //创建一个网络对象
String location="110101";
String key="d4055a0ac0848d29ab8bb6e4ad498d7a";
String extensions="all";                    
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
         Serial.print(".");
        }
  Serial.println("WiFi connected IP is");
  Serial.println(WiFi.localIP()); 
}

//解析程序
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
  const char* forecasts_0_casts_0_date = forecasts_0_casts_0["date"]; // "2022-07-17"
  const char* forecasts_0_casts_0_week = forecasts_0_casts_0["week"]; // "7"
  const char* forecasts_0_casts_0_dayweather = forecasts_0_casts_0["dayweather"]; // "晴"
  const char* forecasts_0_casts_0_nightweather = forecasts_0_casts_0["nightweather"]; // "晴"
  const char* forecasts_0_casts_0_daytemp = forecasts_0_casts_0["daytemp"]; // "35"
  const char* forecasts_0_casts_0_nighttemp = forecasts_0_casts_0["nighttemp"]; // "23"
  const char* forecasts_0_casts_0_daywind = forecasts_0_casts_0["daywind"]; // "北"
  const char* forecasts_0_casts_0_nightwind = forecasts_0_casts_0["nightwind"]; // "北"
  const char* forecasts_0_casts_0_daypower = forecasts_0_casts_0["daypower"]; // "≤3"
  const char* forecasts_0_casts_0_nightpower = forecasts_0_casts_0["nightpower"]; // "≤3"

  JsonObject& forecasts_0_casts_1 = forecasts_0_casts[1];
  const char* forecasts_0_casts_1_date = forecasts_0_casts_1["date"]; // "2022-07-18"
  const char* forecasts_0_casts_1_week = forecasts_0_casts_1["week"]; // "1"
  const char* forecasts_0_casts_1_dayweather = forecasts_0_casts_1["dayweather"]; // "晴"
  const char* forecasts_0_casts_1_nightweather = forecasts_0_casts_1["nightweather"]; // "多云"
  const char* forecasts_0_casts_1_daytemp = forecasts_0_casts_1["daytemp"]; // "35"
  const char* forecasts_0_casts_1_nighttemp = forecasts_0_casts_1["nighttemp"]; // "22"
  const char* forecasts_0_casts_1_daywind = forecasts_0_casts_1["daywind"]; // "南"
  const char* forecasts_0_casts_1_nightwind = forecasts_0_casts_1["nightwind"]; // "南"
  const char* forecasts_0_casts_1_daypower = forecasts_0_casts_1["daypower"]; // "≤3"
  const char* forecasts_0_casts_1_nightpower = forecasts_0_casts_1["nightpower"]; // "≤3"

  JsonObject& forecasts_0_casts_2 = forecasts_0_casts[2];
  const char* forecasts_0_casts_2_date = forecasts_0_casts_2["date"]; // "2022-07-19"
  const char* forecasts_0_casts_2_week = forecasts_0_casts_2["week"]; // "2"
  const char* forecasts_0_casts_2_dayweather = forecasts_0_casts_2["dayweather"]; // "多云"
  const char* forecasts_0_casts_2_nightweather = forecasts_0_casts_2["nightweather"]; // "多云"
  const char* forecasts_0_casts_2_daytemp = forecasts_0_casts_2["daytemp"]; // "33"
  const char* forecasts_0_casts_2_nighttemp = forecasts_0_casts_2["nighttemp"]; // "24"
  const char* forecasts_0_casts_2_daywind = forecasts_0_casts_2["daywind"]; // "西南"
  const char* forecasts_0_casts_2_nightwind = forecasts_0_casts_2["nightwind"]; // "西南"
  const char* forecasts_0_casts_2_daypower = forecasts_0_casts_2["daypower"]; // "≤3"
  const char* forecasts_0_casts_2_nightpower = forecasts_0_casts_2["nightpower"]; // "≤3"

  JsonObject& forecasts_0_casts_3 = forecasts_0_casts[3];
  const char* forecasts_0_casts_3_date = forecasts_0_casts_3["date"]; // "2022-07-20"
  const char* forecasts_0_casts_3_week = forecasts_0_casts_3["week"]; // "3"
  const char* forecasts_0_casts_3_dayweather = forecasts_0_casts_3["dayweather"]; // "多云"
  const char* forecasts_0_casts_3_nightweather = forecasts_0_casts_3["nightweather"]; // "晴"
  const char* forecasts_0_casts_3_daytemp = forecasts_0_casts_3["daytemp"]; // "32"
  const char* forecasts_0_casts_3_nighttemp = forecasts_0_casts_3["nighttemp"]; // "22"
  const char* forecasts_0_casts_3_daywind = forecasts_0_casts_3["daywind"]; // "西南"
  const char* forecasts_0_casts_3_nightwind = forecasts_0_casts_3["nightwind"]; // "西南"
  const char* forecasts_0_casts_3_daypower = forecasts_0_casts_3["daypower"]; // "≤3"
  const char* forecasts_0_casts_3_nightpower = forecasts_0_casts_3["nightpower"]; // "≤3"

  Serial.println(forecasts_0_province);
  Serial.println(forecasts_0_city);
  Serial.println(forecasts_0_casts_0_date);
  Serial.println(forecasts_0_casts_0_week);
  Serial.println(forecasts_0_casts_0_dayweather);

}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);//设置波特率
  wifi_start_connect();//连接wifi
  client.setTimeout(5000);//设置服务器连接超时
  
}
void loop() {
  // put your main code here, to run repeatedly:
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
        const char* str = https.getString().c_str;
        Serial.println(str);
        putjson(str);
      }
    } else { // 错误返回负值
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
    }
  else { // HTTPS连接失败
    Serial.printf("[HTTPS] Unable to connect\n");
  }  
  delay(10000);
}
