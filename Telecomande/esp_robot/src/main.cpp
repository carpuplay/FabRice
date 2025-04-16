#include <esp_now.h>
#include <WiFi.h>
#include <SPI.h>

#include <esp32-hal-log.h>

#include <led.h>

// Broches
#define LED_PIN 18   // LED principale
#define LEDR_PIN 19  // Deuxième LED
#define SS_PIN 7     // Sélection de l'esclave SPI (Arduino Giga)

/* Data structure */
typedef struct {

  uint16_t xLeft;
  uint16_t xRight;

  uint16_t yLeft;
  uint16_t yRight;

  bool joystickButtonLeft;
  bool joystickButtonRight;

  bool buttonA;
  bool buttonB;
  bool switchArm;
} TelecommandData;


Led ledJoystickLeft(LED_PIN);
Led ledJoystickRight(LEDR_PIN);

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

  log_d("Joystick reçu - X: %d | Y: %d | XR: %d | YR: %d | LED 1: %s | LED 2: %s",
         joystick.x, joystick.y, joystick.xr, joystick.yr,
         joystick.led ? "ON" : "OFF", joystick.ledr ? "ON" : "OFF");

  // Contrôle des LEDs
  if (joystick.buttonLeft) {
    ledJoystickLeft.on();
  } else {
    ledJoystickLeft.off();
  }
  if (joystick.buttonRight) {
    ledJoystickRight.on();
  } else {
    ledJoystickRight.off();
  }

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
