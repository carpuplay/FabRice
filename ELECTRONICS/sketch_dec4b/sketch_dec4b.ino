#include <WiFiNINA.h>

// Nombre de la red (SSID) y contraseña
const char* ssid = "bahamas";
const char* password = "12345678"; // Cambia esto por tu contraseña (mínimo 8 caracteres)

// Variables para verificar el estado del hardware WiFi
int status = WL_IDLE_STATUS;

void setup() {
  // Inicia la comunicación serie para depuración
  Serial.begin(115200);
  while (!Serial) {
    ; // Espera a que el puerto serie esté listo (solo necesario para algunos entornos)
  }

  // Verifica si el hardware WiFi está presente
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("El módulo WiFi no se encuentra.");
    while (true); // Detiene el programa
  }

  // Configura el modo punto de acceso (AP)
  Serial.println("Configurando modo AP...");
  if (WiFi.beginAP(ssid, password)) {
    Serial.println("Punto de acceso configurado correctamente.");
    Serial.print("Nombre de la red (SSID): ");
    Serial.println(ssid);
    Serial.print("Dirección IP del AP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Error al configurar el punto de acceso.");
  }
}

void loop() {
  // El programa principal puede permanecer vacío si no hay tareas adicionales
}
