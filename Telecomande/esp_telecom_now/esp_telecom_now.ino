#include <esp_now.h>
#include <WiFi.h>

#define VRX_PIN  4  // Joystick gauche X
#define VRY_PIN  5  // Joystick gauche Y
#define SW_PIN   8  // Bouton poussoir gauche

#define VRXR_PIN  1  // Joystick droit X
#define VRYR_PIN  0  // Joystick droit Y
#define SWR_PIN  11  // Bouton poussoir droit

#define BUZZER_PIN 10 // Buzzer
#define BTN1_A_PIN 18
#define BTN1_B_PIN 19
#define SW_ARM 15
#define LOW_BAT_LED 20
#define V_SENSE_PIN 2

uint8_t robotMAC[] = {0xF0, 0xF5, 0xBD, 0x0C, 0x04, 0x28};

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 100; // Envoi toutes les 100 ms

// Structure des données envoyées
typedef struct {
  int x;
  int xr;
  int y;
  int yr;
  bool led;
  bool ledr;
} JoystickData;

typedef struct {
  bool btn1_a;
  bool btn1_b;
  bool sw_arm;
  float v_bat;
} DataTelec;

void onSent(const uint8_t *macAddr, esp_now_send_status_t status) {
  Serial.print("📡 Données envoyées, statut: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "✅ Succès" : "❌ Échec");

  if (status != ESP_NOW_SEND_SUCCESS) {
    Serial.println("⚠️ Échec de l'envoi, activation du buzzer !");
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(200);
      digitalWrite(BUZZER_PIN, LOW);
      delay(200);
    }
  }
}

float vBat() {
  const float R1 = 10000.0;  // 10kΩ
  const float R2 = 8200.0;   // 8.2kΩ
  const float VREF = 3.3;    // Référence ADC
  const int ADC_MAX = 4095;

  int rawValue = analogRead(V_SENSE_PIN);
  float voltage = (rawValue / (float)ADC_MAX) * VREF;

  // Calculer la tension réelle de la batterie
  float batteryVoltage = voltage * (R1 + R2) / R2;

  Serial.print("🔋 Tension Batterie: ");
  Serial.print(batteryVoltage);
  Serial.println("V");

  float batteryPercentage = (batteryVoltage / 8.4) * 100;
  Serial.print("🔋 Batterie: ");
  Serial.print(batteryPercentage);
  Serial.println("%");

  if (batteryVoltage < 7.4) {
    digitalWrite(LOW_BAT_LED, HIGH); // Alerte batterie faible
  } else {
    digitalWrite(LOW_BAT_LED, LOW);
  }

  return batteryVoltage;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(VRXR_PIN, INPUT);
  pinMode(VRYR_PIN, INPUT);
  pinMode(SWR_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN1_A_PIN, INPUT_PULLUP);
  pinMode(BTN1_B_PIN, INPUT_PULLUP);
  pinMode(SW_ARM, INPUT_PULLUP);
  pinMode(LOW_BAT_LED, OUTPUT);
  pinMode(V_SENSE_PIN, INPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LOW_BAT_LED, LOW);

  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ Erreur d'initialisation ESP-NOW");
    return;
  }

  esp_now_register_send_cb(onSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, robotMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("❌ Erreur ajout du peer");
    return;
  }
}

void loop() {
  if (millis() - lastSendTime >= sendInterval) {
    JoystickData joystick;
    DataTelec data;

    // Lecture des joysticks
    joystick.x = analogRead(VRX_PIN);
    joystick.y = analogRead(VRY_PIN);
    joystick.xr = analogRead(VRXR_PIN);
    joystick.yr = analogRead(VRYR_PIN);

    joystick.led = digitalRead(SW_PIN) == LOW;
    joystick.ledr = digitalRead(SWR_PIN) == LOW;

    // Lecture des boutons
    data.btn1_a = digitalRead(BTN1_A_PIN) == LOW;
    data.btn1_b = digitalRead(BTN1_B_PIN) == LOW;
    data.sw_arm = digitalRead(SW_ARM) == LOW;

    // Lecture de la tension de batterie
    data.v_bat = vBat();

    // Debug
    Serial.print("📤 Envoi - X: "); Serial.print(joystick.x);
    Serial.print(" | Y: "); Serial.print(joystick.y);
    Serial.print(" | XR: "); Serial.print(joystick.xr);
    Serial.print(" | YR: "); Serial.print(joystick.yr);
    Serial.print(" | LED: "); Serial.print(joystick.led ? "ON" : "OFF");
    Serial.print(" | LEDR: "); Serial.println(joystick.ledr ? "ON" : "OFF");

    Serial.print("📤 Boutons - A: "); Serial.print(data.btn1_a);
    Serial.print(" | B: "); Serial.print(data.btn1_b);
    Serial.print(" | ARM: "); Serial.print(data.sw_arm);
    Serial.print(" | Batterie: "); Serial.print(data.v_bat);
    Serial.println("V");

    // Envoi des données
    esp_now_send(robotMAC, (uint8_t *)&joystick, sizeof(joystick));
    esp_now_send(robotMAC, (uint8_t *)&data, sizeof(data));

    lastSendTime = millis();
  }

  delay(10);
}
