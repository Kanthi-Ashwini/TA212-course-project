#define BRAKE 0
#define CW 1
#define CCW 2
#define CS_THRESHOLD 15  // Safety current threshold

// Motor 1 control pins (Forward/Backward)
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

// Motor 2 control pins (Left/Right)
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

// PWM pins for Motor 1 and Motor 2
#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

// Current sensing pins for Motor 1 and Motor 2
#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3

// Enable pins for Motor 1 and Motor 2
#define EN_PIN_1 A0
#define EN_PIN_2 A1

// Motor identifiers
#define MOTOR_1 0
#define MOTOR_2 1

short usSpeed = 250;  // Default motor speed
unsigned short usMotor1_Status = BRAKE;  // Forward/Backward motor status
unsigned short usMotor2_Status = BRAKE;  // Left/Right motor status

void setup() {
    // Motor 1 control pins
    pinMode(MOTOR_A1_PIN, OUTPUT);
    pinMode(MOTOR_B1_PIN, OUTPUT);

    // Motor 2 control pins
    pinMode(MOTOR_A2_PIN, OUTPUT);
    pinMode(MOTOR_B2_PIN, OUTPUT);

    // PWM pins
    pinMode(PWM_MOTOR_1, OUTPUT);
    pinMode(PWM_MOTOR_2, OUTPUT);

    // Current sensing pins
    pinMode(CURRENT_SEN_1, INPUT);
    pinMode(CURRENT_SEN_2, INPUT);

    // Enable pins
    pinMode(EN_PIN_1, OUTPUT);
    pinMode(EN_PIN_2, OUTPUT);

    Serial.begin(9600);
    Serial.println("Begin motor control");
    Serial.println();
    Serial.println("Enter number for control option:");
    Serial.println("e. STOP");
    Serial.println("q. STOP Turning");
    Serial.println("w. FORWARD");
    Serial.println("s. REVERSE");
    Serial.println("a. Left");
    Serial.println("d. Right");
    Serial.println("+. INCREASE SPEED");
    Serial.println("-. DECREASE SPEED");
    Serial.println();
}

void loop() {
    if (Serial.available()) {
        char user_input = Serial.read(); // Read user input without flushing
        // Remove the flush command to allow continuous input processing.

        digitalWrite(EN_PIN_1, HIGH);
        digitalWrite(EN_PIN_2, HIGH);

        switch (user_input) {
            case 'e':
                Stop();
                break;
            case 'q':
                Stop_Turn();
                break;
            case 'w':
                Forward();
                break;
            case 's':
                Reverse();
                break;
            case 'a':
                Left_Turn();
                break;
            case 'd':
                Right_Turn();
                break;
            case '+':
                IncreaseSpeed();
                break;
            case '-':
                DecreaseSpeed();
                break;
            default:
                Serial.println("Invalid option entered.");
                break;
        }
    }
    delay(100);
}

void Stop() {
    Serial.println("Stop");
    usMotor1_Status = BRAKE;
    motorGo(MOTOR_1, usMotor1_Status, 0);
}

void Stop_Turn() {
    Serial.println("Stop Turning");
    usMotor2_Status = BRAKE;
    motorGo(MOTOR_2, usMotor2_Status, 0);
}

void Forward() {
    Serial.println("Forward");
    usMotor1_Status = CW;
    motorGo(MOTOR_1, usMotor1_Status, usSpeed);
}

void Reverse() {
    Serial.println("Reverse");
    usMotor1_Status = CCW;
    motorGo(MOTOR_1, usMotor1_Status, usSpeed);
}

void Right_Turn() {
    Serial.println("Right");
    usMotor2_Status = CW;
    motorGo(MOTOR_2, usMotor2_Status, usSpeed);
}

void Left_Turn() {
    Serial.println("Left");
    usMotor2_Status = CCW;
    motorGo(MOTOR_2, usMotor2_Status, usSpeed);
}

void IncreaseSpeed() {
    usSpeed = min(usSpeed + 10, 255);
    Serial.print("Speed +: ");
    Serial.println(usSpeed);
    motorGo(MOTOR_1, usMotor1_Status, usSpeed);
    motorGo(MOTOR_2, usMotor2_Status, usSpeed);
}

void DecreaseSpeed() {
    usSpeed = max(usSpeed - 10, 0);
    Serial.print("Speed -: ");
    Serial.println(usSpeed);
    motorGo(MOTOR_1, usMotor1_Status, usSpeed);
    motorGo(MOTOR_2, usMotor2_Status, usSpeed);
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) {
    if (motor == MOTOR_1) {
        if (direct == CW) {
            digitalWrite(MOTOR_A1_PIN, LOW);
            digitalWrite(MOTOR_B1_PIN, HIGH);
        } else if (direct == CCW) {
            digitalWrite(MOTOR_A1_PIN, HIGH);
            digitalWrite(MOTOR_B1_PIN, LOW);
        } else {
            digitalWrite(MOTOR_A1_PIN, LOW);
            digitalWrite(MOTOR_B1_PIN, LOW);
        }
        analogWrite(PWM_MOTOR_1, pwm);
    } else if (motor == MOTOR_2) {
        if (direct == CW) {
            digitalWrite(MOTOR_A2_PIN, LOW);
            digitalWrite(MOTOR_B2_PIN, HIGH);
        } else if (direct == CCW) {
            digitalWrite(MOTOR_A2_PIN, HIGH);
            digitalWrite(MOTOR_B2_PIN, LOW);
        } else {
            digitalWrite(MOTOR_A2_PIN, LOW);
            digitalWrite(MOTOR_B2_PIN, LOW);
        }
        analogWrite(PWM_MOTOR_2, pwm);
    }
}
