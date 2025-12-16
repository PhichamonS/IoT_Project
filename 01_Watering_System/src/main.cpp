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

// WiFi credentials.
char ssid[] = "TN-HK7286";
char pass[] = "TankAdHyryn6";

// Define component pins 
#define MOISTURE_SENSOR_PIN A0
#define WATER_PUMP D3

// Define the Virtual Pin on Blynk
#define BLYNK_VIRTUAL_MOISTURE_PIN V3 // Using V3 for moisture data


BlynkTimer timer;
// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}

// Define your calibrated sensor values
const int DRY_VALUE = 950;  
const int WET_VALUE = 300; 

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

  if (moisturePercentage > 30)
  {
      digitalWrite(D1, LOW);    // Red LED OFF
      digitalWrite(D2, HIGH);   // Green LED ON
  }
  else
  {
      digitalWrite(D1, HIGH);   // Red LED ON
      digitalWrite(D2, LOW);    // Green LED OFF
  }
  
}

void setup()
{
  Serial.begin(115200);

  // Digital component
  pinMode(D1, OUTPUT);  // LED Red
  pinMode(D2, OUTPUT);  // LED Green
  pinMode(D3, OUTPUT);  // Pump

  // Initialize the sensor
  digitalWrite(WATER_PUMP, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Set up a function to be called every second (for uptime)
  timer.setInterval(1000L, myTimerEvent);

  // Set up a function to be called every 5 seconds (for sensor data)
  timer.setInterval(5000L, SendData);
}

// This function is called every time the Virtual Pin 4 state changes
BLYNK_WRITE(V4)
{
  int water_status = param.asInt();
  digitalWrite(D3, water_status);
}


void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

