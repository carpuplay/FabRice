#include <esp_now.h>
#include <WiFi.h>
#include <SPI.h>

// Broches
#define LED_PIN 18   // LED principale
#define LEDR_PIN 19  // Deuxième LED
#define SS_PIN 7     // Sélection de l'esclave SPI (Arduino Giga)

// Structure du message
typedef struct {
  int x;
  int xr;
  int y;
  int yr;
  bool led;
  bool ledr;
} JoystickData;

// Fonction d'envoi des données par SPI
void sendSPI(JoystickData joystick) {
  digitalWrite(SS_PIN, LOW); // Active l'esclave

  // Envoi des données en paquets (2 octets par entier, 1 octet par booléen)
  SPI.transfer16(joystick.x);
  SPI.transfer16(joystick.xr);
  SPI.transfer16(joystick.y);
  SPI.transfer16(joystick.yr);
  SPI.transfer(joystick.led);
  SPI.transfer(joystick.ledr);

  digitalWrite(SS_PIN, HIGH); // Désactive l'esclave
}

// Callback de réception ESP-NOW
void onReceive(const esp_now_recv_info_t *recvInfo, const uint8_t *incomingData, int len) {
  JoystickData joystick;
  memcpy(&joystick, incomingData, sizeof(joystick));

  Serial.print("🎮 Joystick reçu - X: ");
  Serial.print(joystick.x);
  Serial.print(" | Y: ");
  Serial.print(joystick.y);
  Serial.print(" | XR: ");
  Serial.print(joystick.xr);
  Serial.print(" | YR: ");
  Serial.print(joystick.yr);
  Serial.print(" | LED 1: ");
  Serial.print(joystick.led ? "ON" : "OFF");
  Serial.print(" | LED 2: ");
  Serial.println(joystick.ledr ? "ON" : "OFF");

  // Contrôle des LEDs
  digitalWrite(LED_PIN, joystick.led ? HIGH : LOW);
  digitalWrite(LEDR_PIN, joystick.ledr ? HIGH : LOW);

  // Envoi des données au Giga R1 par SPI
  sendSPI(joystick);
}

// Callback d'envoi (optionnel)
void onSent(const uint8_t *macAddr, esp_now_send_status_t status) {
  Serial.print("📡 Données envoyées, statut: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "✅ Succès" : "❌ Échec");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ Erreur d'initialisation ESP-NOW");
    return;
  }

  esp_now_register_send_cb(onSent);
  esp_now_register_recv_cb(onReceive);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LEDR_PIN, OUTPUT);
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH); // Désactive l'esclave au démarrage

  SPI.begin(); // Initialisation du SPI

  // Test des LEDs au démarrage
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LEDR_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LEDR_PIN, LOW);
}

void loop() {
  delay(10);
}
