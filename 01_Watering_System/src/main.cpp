/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL4ADffiksU"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "ojVupkYz5H5pMW-zqKDJWJD4jF2wkv3F"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// #include <DHT.h>
// #include <Adafruit_Sensor.h>
// DHT dht(D5, DHT11);

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TN-HK7286";
char pass[] = "TankAdHyryn6";

// Define the pin for the moisture sensor (A0 is the analog pin)
#define MOISTURE_SENSOR_PIN A0
// Define the Virtual Pin for the moisture data on Blynk
#define BLYNK_VIRTUAL_MOISTURE_PIN V3 // Using V3 for moisture data now


BlynkTimer timer;

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

// void SendData() {

//   float h = dht.readHumidity();
//   float t = dht.readTemperature();

//   // Check if any reads failed and exit early (good practice)
//   if (isnan(h) || isnan(t)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;
//   }

//   Blynk.virtualWrite(V3, t);
//   Blynk.virtualWrite(V4, h);

//   Serial.print("Temperature: ");
//   Serial.println(t, 1);
//   Serial.print("Humidity: ");
//   Serial.println(h, 1);
// }

// Define your calibrated sensor values
const int DRY_VALUE = 950;  // Adjust this based on your calibration
const int WET_VALUE = 300;  // Adjust this based on your calibration

// Function to read the moisture sensor and send data to Blynk
void SendData() {
  // Read the analog value from the moisture sensor
  int rawMoistureValue = analogRead(MOISTURE_SENSOR_PIN);

  // Map the raw value to a percentage
  int moisturePercentage = map(rawMoistureValue, DRY_VALUE, WET_VALUE, 0, 100);

  // The sensor typically returns a value between 0 (wet) and 1023 (dry).
  Blynk.virtualWrite(BLYNK_VIRTUAL_MOISTURE_PIN, moisturePercentage);

  Serial.print("Raw Moisture Value: ");
  Serial.println(rawMoistureValue);
  Serial.print("Moisture Percentage: ");
  Serial.println(moisturePercentage);
}


void setup()
{
  // LED (Red , Green)
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  // Debug console  
  Serial.begin(115200);

  // Initialize the DHT sensor
  // dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Set up a function to be called every second (for uptime)
  timer.setInterval(1000L, myTimerEvent);

  // Set up a function to be called every 5 seconds (for sensor data)
  timer.setInterval(5000L, SendData);
}


// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  int val_1 = param.asInt();
  digitalWrite(D1, val_1);
}

BLYNK_WRITE(V1)
{
  int val_2 = param.asInt();
  digitalWrite(D2, val_2);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

