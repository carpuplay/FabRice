#include <WiFi.h>

// Remplace ces variables par les informations de ton réseau Wi-Fi
const char *ssid = "CheeseBalls"; // Nom du réseau Wi-Fi
const char *password = "jennyfucker"; // Mot de passe du réseau Wi-Fi

WiFiServer server(80); // Le serveur écoute sur le port 80 (HTTP par défaut)

void setup() {
Serial.begin(115200);
delay(1000);

// Connexion au réseau Wi-Fi
Serial.print("Recherche Wifi: ");
Serial.print(ssid);
WiFi.begin(ssid, password);

// Attente de la connexion
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}

Serial.println();
Serial.print("Connecté à Wi-Fi avec l'adresse IP: ");
Serial.println(WiFi.localIP());

// Démarre le serveur
server.begin();
}

void loop() {
// Vérifie si un client est connecté
WiFiClient client = server.available();

if (client) {
Serial.println("📡 Nouveau client connecté");

String receivedData = ""; // Stocker les données reçues

while (client.connected()) {
if (client.available()) {
char c = client.read();
Serial.write(c); // Affiche les données reçues dans le moniteur série
receivedData += c;

// Vérifier si un message complet a été reçu (fin de ligne)
if (c == '\n') {
receivedData.trim(); // Supprime les espaces et sauts de ligne

if (receivedData == "PING") {
Serial.println("🔄 PING reçu, envoi de PONG...");
client.println("PONG"); // Répond au client
}

receivedData = ""; // Réinitialise la variable
}
}
}

// Lorsque le client se déconnecte
Serial.println("❌ Client déconnecté");
client.stop();
}

// Vérifie la connexion Wi-Fi
if (WiFi.status() != WL_CONNECTED) {
Serial.println("⚠️ Connexion Wi-Fi perdue, tentative de reconnexion...");
WiFi.begin(ssid, password);
}
}