#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15

//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8
//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9
#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6
#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3
#define EN_PIN_1 A0
#define EN_PIN_2 A1
#define MOTOR_1 0
#define MOTOR_2 1

// Motor speeds
short usSpeed1 = 150;  // Motor 1 speed
short usSpeed2 = 150;  // Motor 2 speed

// Motor status variables (one for each motor)
unsigned short usMotor1_Status = CW;
unsigned short usMotor2_Status = CW;

// Timing variables
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
const long interval1 = 3000;  // Motor 1 changes direction every 3 seconds
const long interval2 = 5000;  // Motor 2 changes direction every 5 seconds

void setup() {
    pinMode(MOTOR_A1_PIN, OUTPUT);
    pinMode(MOTOR_B1_PIN, OUTPUT);
    pinMode(MOTOR_A2_PIN, OUTPUT);
    pinMode(MOTOR_B2_PIN, OUTPUT);
    pinMode(PWM_MOTOR_1, OUTPUT);
    pinMode(PWM_MOTOR_2, OUTPUT);
    pinMode(CURRENT_SEN_1, OUTPUT);
    pinMode(CURRENT_SEN_2, OUTPUT);  
    pinMode(EN_PIN_1, OUTPUT);
    pinMode(EN_PIN_2, OUTPUT);

    // Enable both motors
    digitalWrite(EN_PIN_1, HIGH);
    digitalWrite(EN_PIN_2, HIGH);

    // Start both motors
    motorGo(MOTOR_1, usMotor1_Status, usSpeed1);
    motorGo(MOTOR_2, usMotor2_Status, usSpeed2);
}

void loop() {
    unsigned long currentMillis = millis();

    // Control Motor 1
    if (currentMillis - previousMillis1 >= interval1) {
        previousMillis1 = currentMillis;
        // Toggle direction
        usMotor1_Status = (usMotor1_Status == CW) ? CCW : CW;
        motorGo(MOTOR_1, usMotor1_Status, usSpeed1);
    }

    // Control Motor 2
    if (currentMillis - previousMillis2 >= interval2) {
        previousMillis2 = currentMillis;
        // Toggle direction
        usMotor2_Status = (usMotor2_Status == CW) ? CCW : CW;
        motorGo(MOTOR_2, usMotor2_Status, usSpeed2);
    }
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) {
    if(motor == MOTOR_1) {
        if(direct == CW) {
            digitalWrite(MOTOR_A1_PIN, LOW); 
            digitalWrite(MOTOR_B1_PIN, HIGH);
        }
        else if(direct == CCW) {
            digitalWrite(MOTOR_A1_PIN, HIGH);
            digitalWrite(MOTOR_B1_PIN, LOW);      
        }
        else {
            digitalWrite(MOTOR_A1_PIN, LOW);
            digitalWrite(MOTOR_B1_PIN, LOW);            
        }
        analogWrite(PWM_MOTOR_1, pwm); 
    }
    else if(motor == MOTOR_2) {
        if(direct == CW) {
            digitalWrite(MOTOR_A2_PIN, LOW);
            digitalWrite(MOTOR_B2_PIN, HIGH);
        }
        else if(direct == CCW) {
            digitalWrite(MOTOR_A2_PIN, HIGH);
            digitalWrite(MOTOR_B2_PIN, LOW);      
        }
        else {
            digitalWrite(MOTOR_A2_PIN, LOW);
            digitalWrite(MOTOR_B2_PIN, LOW);            
        }
        analogWrite(PWM_MOTOR_2, pwm);
    }
}