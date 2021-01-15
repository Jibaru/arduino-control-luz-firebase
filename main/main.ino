#include <FirebaseESP8266.h> // https://github.com/mobizt/Firebase-ESP8266
#include <ESP8266WiFi.h>
#include "arduino_secrets.h"
#include "IotHome.h"

// FirebaseData
FirebaseData firebaseData;

// IotHome
IotHome iotHome = IotHome();

void setup() {
  Serial.begin(9600);

  // Inicializando pines
  iotHome.init();

  // IP Configuracion
  IPAddress staticIP(192, 168, 1, 9);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(8, 8, 8, 8);

  // Inicializando Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Inicializando conexion WIFI
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(WIFI_SID, WIFI_PASSWORD);

  // Tiempo de espera en conexion
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Datos de conexion
  Serial.println("");
  Serial.print("Conectado a ");
  Serial.println(WIFI_SID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

}

void getBooleanDataAndTry(const String& path, void (*callback)(bool data)) {
  if (Firebase.getBool(firebaseData, path)) {
    if (firebaseData.dataType() == "boolean") {
      callback(firebaseData.boolData());
    }
  } else {
    Serial.println(firebaseData.errorReason());
  }
}

void loop() {

  if (Firebase.getInt(firebaseData, "/test/led")) {

    if (firebaseData.dataType() == "int") {
      Serial.println(firebaseData.intData());
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
  delay(1000);

  // Envio datos
  if (Firebase.setBool(firebaseData, "led1", true)) {
    Serial.println("Enviado");
  } else {
    Serial.println(firebaseData.errorReason());
  }
  delay(1000);


  if (Firebase.getBool(firebaseData, "led2")) {

    if (firebaseData.dataType() == "boolean") {

      if (!firebaseData.boolData()) {
        Serial.println("Apaga pin 2");
        iotHome.tryOn(PIN_2);
      } else {
        Serial.println("Enciende pin 2");
        iotHome.tryOff(PIN_2);
      }
    }
  } else {
    Serial.println(firebaseData.errorReason());
  }
  delay(1000);

  getBooleanDataAndTry("led1", [](bool data)-> void {
    if (!data) {
      Serial.println("Apaga pin 2");
      iotHome.tryOn(PIN_2);
    } else {
      Serial.println("Enciende pin 2");
      iotHome.tryOff(PIN_2);
    }
  });
}
