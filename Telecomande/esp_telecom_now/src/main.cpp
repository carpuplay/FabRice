#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include <joystick.h>
#include <moyenne.h>
#include <battery.h>
#include <buzzer.h>
#include <button.h>
#include <led.h>

#include <esp32-hal-log.h>

/*
==================================================================================
                                   CONFIG
==================================================================================
*/

/* Left joystick PINs */
#define VRX_LEFT_PIN  4  // Joystick gauche X
#define VRY_LEFT_PIN  5  // Joystick gauche Y
#define SW_LEFT_PIN   8  // Bouton poussoir gauche

// Right joystick PINs
#define VRX_RIGHT_PIN  1  // Joystick droit X
#define VRY_RIGHT_PIN  0  // Joystick droit Y
#define SW_RIGHT_PIN  11  // Bouton poussoir droit

/* Buzzer PIN */
#define BUZZER_PIN 10 // Buzzer

/* Button PINs */
#define BTN1_A_PIN 18
#define BTN1_B_PIN 19
#define SW_ARM 15
#define LOW_BAT_LED 20
#define V_SENSE_PIN 3

/* Battery voltage sensor */
#define MAX_VBAT 8.4 // Tension max de la batterie
#define R1 10000.0 // Résistance de 10k ohm
#define R2 8600.0 // Résistance de 8.2k ohm
#define VREF 3.3 // Tension de référence de l'ADC

/* ESP-NOW MAC address of the robot */
uint8_t robotMAC[] = {0xF0, 0xF5, 0xBD, 0x0C, 0x04, 0x28};

/* Interval for sending data (in milliseconds) */
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 25;

extern "C" int lwip_hook_ip6_input(void *p) {
  return 1;
}

/* Data structure */
typedef struct {
  uint32_t xl;
  uint32_t xr;
  int yl;
  int yr;
  bool ledl;
  bool ledr;
} JoystickData;

typedef struct {
  bool btn1_a;
  bool btn1_b;
  bool sw_arm;
  float v_bat;
} DataTelec;

/* Telecommande Module */
Joystick joystickLeft(VRX_LEFT_PIN, VRY_LEFT_PIN, SW_LEFT_PIN);
Joystick joystickRight(VRX_RIGHT_PIN, VRY_RIGHT_PIN, SW_RIGHT_PIN);
Battery batterie(V_SENSE_PIN, MAX_VBAT, R1, R2, VREF);

Buzzer buzzer(BUZZER_PIN);

Button btn1_a(BTN1_A_PIN);
Button btn1_b(BTN1_B_PIN);
Button sw_arm(SW_ARM);

Led lowBatLed(LOW_BAT_LED);

/* Utils */
Moyenne<int> moyenneXL(5);
Moyenne<int> moyenneYL(5);
Moyenne<int> moyenneXR(5);
Moyenne<int> moyenneYR(5);

Moyenne<float> moyenneBat(25);



/*
==================================================================================
                                Functions
==================================================================================
*/


void onSent(const uint8_t *macAddr, esp_now_send_status_t status) {
  if (status != ESP_NOW_SEND_SUCCESS) {
    log_e("Erreur d'envoi des données %d", status);
    buzzer.multipleBeeps(3, 100, 100);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    log_e("Erreur d'initialisation d'ESP-NOW");
    buzzer.beep(500);
    return;
  }

  esp_now_register_send_cb(onSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, robotMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    log_e("Erreur d'ajout du pair ESP-NOW");
    buzzer.multipleBeeps(2, 500, 200);
    return;
  }
}

void getData(JoystickData *joystick, DataTelec *data) {
  joystick->xl = joystickLeft.getX();
  joystick->yl = joystickLeft.getY();
  joystick->xr = joystickRight.getX();
  joystick->yr = joystickRight.getY();

  joystick->ledl = joystickLeft.isPressed();
  joystick->ledr = joystickRight.isPressed();

  data->btn1_a = digitalRead(BTN1_A_PIN) == LOW;
  data->btn1_b = digitalRead(BTN1_B_PIN) == LOW;
  data->sw_arm = digitalRead(SW_ARM) == LOW;

  moyenneBat + batterie.readVoltage();
  data->v_bat = moyenneBat.getMoyenne();
}

void loop() {
  if (millis() - lastSendTime >= sendInterval) {
    JoystickData joystickData;
    DataTelec dataTelec;

    getData(&joystickData, &dataTelec);

    // Debug
    log_d("Envoi - X: %d | Y: %d | XR: %d | YR: %d | LEDL: %s | LEDR: %s",
          joystick.xl, joystick.yl, joystick.xr, joystick.yr,
          joystick.ledl ? "ON" : "OFF", joystick.ledr ? "ON" : "OFF");
    log_d("Boutons - A: %d | B: %d | ARM: %d | Batterie: %.2fV",
          data.btn1_a, data.btn1_b, data.sw_arm, data.v_bat);

    // Data transmission
    
    esp_now_send(robotMAC, (uint8_t *)&joystick, sizeof(joystick));
    esp_now_send(robotMAC, (uint8_t *)&data, sizeof(data));
    

    lastSendTime = millis();
  }
  delay(10);
}