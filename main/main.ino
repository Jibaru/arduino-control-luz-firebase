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

  pinMode(16, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);

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

void loop() {

  if (Firebase.getInt(firebaseData, "/focos/foco1/rojo")) {

    if (firebaseData.dataType() == "int") {
      Serial.print("Rojo:");
      int valor = firebaseData.intData();
      Serial.println(valor);
      iotHome.setValue(14, valor);
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
  delay(1000);
  if (Firebase.getInt(firebaseData, "/focos/foco1/verde")) {

    if (firebaseData.dataType() == "int") {
      Serial.print("Verde:");
      int valor = firebaseData.intData();
      Serial.println(valor);
      iotHome.setValue(16, valor);
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
  delay(1000);
  if (Firebase.getInt(firebaseData, "/focos/foco1/amarillo")) {

    if (firebaseData.dataType() == "int") {
      Serial.print("Azul:");
      int valor = firebaseData.intData();
      Serial.println(valor);
      iotHome.setValue(12, valor);
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
  delay(1000);
  Serial.println("---------------------------------------");

}
