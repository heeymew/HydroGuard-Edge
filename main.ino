// Permite conectar o esp32 à internet.
#include <WiFi.h>
// Biblioteca para utilizar o protocolo MQTT, que envia os dados para o Node-Red
#include <PubSubClient.h>
// Controla o sensor de temperatura e umidade DHT22
#include <DHT.h>
// Permite controlar os ServoMotores, simulando abertura das comportas
#include <ESP32Servo.h>

// Define o nome da rede Wi-Fi e a porta do servidor MQTT
const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;

// Variáveis, definição de pinos e inicialização de objetos

WiFiClient espClient;
PubSubClient client(espClient);

#define ledR 26
#define ledG 25
#define Servo1PIN 19
#define Servo2PIN 18
#define trigger 17
#define echo 16
#define DHTPIN 5
#define DHTTYPE DHT22

Servo myServo1;
Servo myServo2;
DHT dht(DHTPIN, DHTTYPE);

long duracao;
int dist = 0;

// Conexão com Wi-Fi

void setup_wifi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" conectado");
}

// Reconecta ao MQTT caso caia

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32Client-Wokwi")) {
      Serial.println("conectado");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

// Setup principal, iniciando motores, conexão MQTT, Leds, Ultrasônico e DHT.

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  dht.begin();
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  myServo1.setPeriodHertz(50);
  myServo1.attach(Servo1PIN, 500, 2400);
  myServo2.setPeriodHertz(50);
  myServo2.attach(Servo2PIN, 500, 2400);
  myServo1.write(0);
  myServo2.write(0);
}

// Loop Principal

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

// Medidor de distância com sensor ultrassônico

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duracao = pulseIn(echo, HIGH);
  dist = duracao / 58;

// Leitura de temperatura e umidade

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

// Publicação de dados via MQTT

  client.publish("iot/agua/distancia", String(dist).c_str());
  client.publish("iot/agua/temperatura", String(temperatura).c_str());
  client.publish("iot/agua/umidade", String(umidade).c_str());

// Debug de Serial

  Serial.print("Distancia: ");
  Serial.println(dist);

  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  Serial.print("Umidade: ");
  Serial.println(umidade);

// Lógica de Alerta e controla das comportas

  if (dist < 10) {
    myServo1.write(0);
    myServo2.write(0);
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, HIGH);
    client.publish("iot/agua/alerta", "Nível seguro: comporta fechada");
  } else {
    myServo1.write(90);
    myServo2.write(90);
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    client.publish("iot/agua/alerta", "Comporta aberta: nível crítico");
  }

  delay(2000);
}
