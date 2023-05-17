const int analogPin = A0;
const int numSamples = 50;
int samples[numSamples];

int ledPinSine = 2;
int ledPinSquare = 3;

void setup() {
  pinMode(ledPinSine, OUTPUT);
  pinMode(ledPinSquare, OUTPUT);
  Serial.begin(2000000);
}

void loop() {
  analogWrite(ledPinSquare, 128);

  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n');
    receivedData.trim();  // Remove leading/trailing white spaces

    // Split the received data using ":"
    int delimiterIndex = receivedData.indexOf(":");
    if (delimiterIndex != -1) {
      String waveType = receivedData.substring(0, delimiterIndex);
      int waveValue = receivedData.substring(delimiterIndex + 1).toInt();

      // Perform actions based on wave type
      if (waveType.equalsIgnoreCase("sine")) {
        digitalWrite(ledPinSine, HIGH);
        digitalWrite(ledPinSquare, LOW);
      } else if (waveType.equalsIgnoreCase("square")) {
        int pwmValue = map(waveValue, 0, 100, 0, 255);
        analogWrite(ledPinSquare, pwmValue);
        digitalWrite(ledPinSine, LOW);
      } else {
        digitalWrite(ledPinSine, LOW);
        digitalWrite(ledPinSquare, LOW);
      }
    }
  }

  // Read back 50 samples from analog pin and store in array
  for (int i = 0; i < numSamples; i++) {
    int value = analogRead(analogPin);
    samples[i] = value;
    delay(10);
  }

  // Send samples via serial
  for (int i = 0; i < numSamples; i++) {
    Serial.print(samples[i]);
    Serial.print(",");
  }
  Serial.println();
}

