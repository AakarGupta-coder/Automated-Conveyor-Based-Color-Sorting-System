#include <Servo.h>

// ============== TCS3200 PINS ==============
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define OUT 8
#define OE 9

// ============== SERVO PINS ==============
#define BIG_SERVO_PIN 10
#define FLAP1_PIN 11
#define FLAP2_PIN 12

// ============== SETTINGS ==============
const int SERVO_SPEED = 100;
const int SERVO_STOP = 90;

const int FLAP_HOME = 125;
const int FLAP_PUSH = 30;

const unsigned long STOP_DELAY = 3200;
const unsigned long FLAP_MOVE_TIME = 700;

// ============== BASE REFERENCES ==============
// Original successful base-detection logic.
// These values are deliberately unchanged.

const float BASE_R = 4432;
const float BASE_G = 3693;
const float BASE_B = 4541;

const float BASE_TOLERANCE = 0.35;

// ============== UPDATED COLOR REFERENCES ==============

// Latest WHITE average
const float WHITE_R = 15531;
const float WHITE_G = 18231;
const float WHITE_B = 19863;

// Latest BROWN average
const float BROWN_R = 19070;
const float BROWN_G = 13023;
const float BROWN_B = 13031;

// Color comparison tolerance.
// Adjust after observing actual readings if necessary.
const float COLOR_TOLERANCE = 0.30;

// Require consecutive non-base readings.
const int REQUIRED_PACKAGE_READINGS = 3;

// ============== RGB STRUCTURE ==============
struct RGB {
  unsigned long r;
  unsigned long g;
  unsigned long b;
};

// ============== SERVOS ==============
Servo bigServo;
Servo flap1;
Servo flap2;

// ============== SYSTEM STATES ==============
enum SystemState {
  BELT_RUNNING,
  WAITING_TO_STOP,
  FLAPS_EXTENDED,
  FLAPS_RETURNED
};

SystemState state = BELT_RUNNING;

unsigned long packageDetectedAt = 0;
unsigned long flapMovedAt = 0;

int packageReadings = 0;

// Prevent repeated color messages for the same detection.
bool colorReported = false;

// ============== COLOR SENSOR ==============
unsigned long readChannel(bool s2, bool s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);

  delay(50);

  unsigned long pulse = pulseIn(OUT, LOW, 100000);

  if (pulse == 0) {
    return 0;
  }

  return 1000000UL / pulse;
}

RGB readRGB() {
  RGB x;

  x.r = readChannel(LOW, LOW);
  x.b = readChannel(LOW, HIGH);
  x.g = readChannel(HIGH, HIGH);

  return x;
}

// ============== VALID READING ==============
bool isValidReading(RGB x) {
  return x.r > 0 && x.g > 0 && x.b > 0;
}

// ============== BASE DETECTION ==============
bool channelMatches(float value, float reference,
                    float tolerance) {
  if (reference <= 0) {
    return false;
  }

  float difference = abs((long)value - (long)reference);

  return difference <= reference * tolerance;
}

bool isBase(RGB x) {
  if (!isValidReading(x)) {
    return false;
  }

  bool rMatch = channelMatches(
    x.r, BASE_R, BASE_TOLERANCE
  );

  bool gMatch = channelMatches(
    x.g, BASE_G, BASE_TOLERANCE
  );

  bool bMatch = channelMatches(
    x.b, BASE_B, BASE_TOLERANCE
  );

  return rMatch && gMatch && bMatch;
}

bool isPackage(RGB x) {
  if (!isValidReading(x)) {
    return false;
  }

  return !isBase(x);
}

// ============== COLOR CLASSIFICATION ==============

// Compare each channel to the reference using relative error.
// The average error across all three channels is used to choose
// the closest color, provided it falls within the tolerance.

float colorError(RGB x,
                 float refR,
                 float refG,
                 float refB) {
  float errorR = abs((long)x.r - (long)refR) / refR;
  float errorG = abs((long)x.g - (long)refG) / refG;
  float errorB = abs((long)x.b - (long)refB) / refB;

  return (errorR + errorG + errorB) / 3.0;
}

const char* detectColor(RGB x) {
  if (!isValidReading(x)) {
    return "WHITE";
  }

  // Use the original base detector first.
  if (isBase(x)) {
    return "BASE";
  }

  float whiteError = colorError(
    x, WHITE_R, WHITE_G, WHITE_B
  );

  float brownError = colorError(
    x, BROWN_R, BROWN_G, BROWN_B
  );

  // Find the closest reference.
  if (whiteError <= brownError &&
      whiteError <= COLOR_TOLERANCE) {
    return "WHITE";
  }

  if (brownError < whiteError &&
      brownError <= COLOR_TOLERANCE) {
    return "BROWN";
  }

  return "WHITE";
}

// ============== SETUP ==============
void setup() {
  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  pinMode(OE, OUTPUT);

  digitalWrite(OE, LOW);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  bigServo.attach(BIG_SERVO_PIN);
  flap1.attach(FLAP1_PIN);
  flap2.attach(FLAP2_PIN);

  // Initialize both flaps together.
  flap1.write(FLAP_HOME);
  flap2.write(FLAP_HOME);

  delay(1000);

  // Start the big servo.
  bigServo.write(SERVO_STOP);
  delay(500);
  bigServo.write(SERVO_SPEED);

  Serial.println("================================");
  Serial.println("INVENTORY SYSTEM READY");
  Serial.println("Big servo: D10");
  Serial.println("Flap 1: D11");
  Serial.println("Flap 2: D12");
  Serial.println("Both flaps initialized at 125 degrees.");
  Serial.println("Conveyor remains running during color detection.");
  Serial.println("================================");
}

// ============== MAIN LOOP ==============
void loop() {
  RGB x = readRGB();

  bool valid = isValidReading(x);
  bool baseDetected = valid && isBase(x);
  bool packageDetected = valid && isPackage(x);

  unsigned long now = millis();

  // Print readings every 500 ms.
  static unsigned long lastPrint = 0;

  if (now - lastPrint >= 500) {
    lastPrint = now;

    Serial.print("R:");
    Serial.print(x.r);

    Serial.print(" G:");
    Serial.print(x.g);

    Serial.print(" B:");
    Serial.print(x.b);

    if (!valid) {
      Serial.println(" | INVALID SENSOR READING");
    } else {
      Serial.print(" | COLOR: ");
      Serial.print(detectColor(x));

      if (baseDetected) {
        Serial.println(" | BASE");
      } else {
        Serial.println(" | POSSIBLE PACKAGE");
      }
    }
  }

  switch (state) {

    // ==================================
    // STATE 1: BELT RUNNING
    // ==================================
    case BELT_RUNNING:

      // Conveyor stays running while readings are taken.
      if (baseDetected) {
        packageReadings = 0;
        colorReported = false;
      } else if (packageDetected) {
        packageReadings++;

        // Report the detected color once for this detection.
        if (!colorReported) {
          Serial.print("DETECTED COLOR: ");
          Serial.println(detectColor(x));
          colorReported = true;
        }
      } else {
        packageReadings = 0;
      }

      // Confirm a package after consecutive non-base readings.
      if (packageReadings >= REQUIRED_PACKAGE_READINGS) {
        packageReadings = 0;
        packageDetectedAt = millis();

        state = WAITING_TO_STOP;

        Serial.println();
        Serial.println("PACKAGE CONFIRMED!");
        Serial.println("Color detection complete.");
        Serial.println("Conveyor continues for 3100 ms.");
      }

      break;

    // ==================================
    // STATE 2: WAIT 3100 MS, THEN STOP
    // ==================================
    case WAITING_TO_STOP:

      // The conveyor keeps running throughout this delay.
      if (millis() - packageDetectedAt >= STOP_DELAY) {
        bigServo.write(SERVO_STOP);

        Serial.println("BIG SERVO STOPPED");
        Serial.println("Both flaps moving to 30 degrees.");

        // Command both flaps together.
        flap1.write(FLAP_PUSH);
        flap2.write(FLAP_PUSH);

        flapMovedAt = millis();
        state = FLAPS_EXTENDED;
      }

      break;

    // ==================================
    // STATE 3: RETURN BOTH FLAPS
    // ==================================
    case FLAPS_EXTENDED:

      if (millis() - flapMovedAt >= FLAP_MOVE_TIME) {
        Serial.println("Both flaps returning to 125 degrees.");

        flap1.write(FLAP_HOME);
        flap2.write(FLAP_HOME);

        flapMovedAt = millis();
        state = FLAPS_RETURNED;
      }

      break;

    // ==================================
    // STATE 4: WAIT FOR FLAPS TO RETURN
    // ==================================
    case FLAPS_RETURNED:

      if (millis() - flapMovedAt >= FLAP_MOVE_TIME) {
        Serial.println("Both flaps returned to 125 degrees.");

        bigServo.write(SERVO_SPEED);

        Serial.println("Big servo restarted.");
        Serial.println("READY FOR NEXT PACKAGE!");
        Serial.println();

        packageReadings = 0;
        colorReported = false;

        state = BELT_RUNNING;
      }

      break;
  }

  delay(20);
}