#define R_PIN 7
#define G_PIN 6
#define B_PIN 5
#define CYCLE_DELAY 5000 // microseconds
#define BRIGHTNESS_STEP 1


uint8_t R_duty_cycle = 255;
uint8_t G_duty_cycle = 0;
uint8_t B_duty_cycle = 0;
uint8_t animation_step = 0;
uint16_t R_time_on;
uint16_t G_time_on;
uint16_t B_time_on;
uint32_t cycle_start_microseconds;


void setup() {
    Serial.begin(115200);
    pinMode(R_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);
    pinMode(13, OUTPUT);
    update_PWM();
}

void loop() {
    if (R_time_on != 0) {
        digitalWrite(R_PIN, HIGH);
    }
    if (G_time_on != 0) {
        digitalWrite(G_PIN, HIGH);
    }
    if (B_time_on != 0) {
        digitalWrite(B_PIN, HIGH);
    }
    update_PWM();
    cycle_start_microseconds = micros();
    while (micros() - cycle_start_microseconds < CYCLE_DELAY) {
        if (micros() - cycle_start_microseconds >= R_time_on) {
            digitalWrite(R_PIN, LOW);
        }
        if (micros() - cycle_start_microseconds >= G_time_on) {
            digitalWrite(G_PIN, LOW);
        }
        if (micros() - cycle_start_microseconds >= B_time_on) {
            digitalWrite(B_PIN, LOW);
        }
    }
}

void update_PWM() {
    switch (animation_step) {
    case 0:
        if (G_duty_cycle < 255) {
            G_duty_cycle += BRIGHTNESS_STEP;
        }
        else {
            G_duty_cycle = 255;
            animation_step = 1;
            // Serial.println("Step: 1");
        }
        break;
    case 1:
        if (R_duty_cycle > 0) {
            R_duty_cycle -= BRIGHTNESS_STEP;
        }
        else {
            R_duty_cycle = 0;
            animation_step = 2;
            // Serial.println("Step: 2");
        }
        break;
    case 2:
        if (B_duty_cycle < 255) {
            B_duty_cycle += BRIGHTNESS_STEP;
        }
        else {
            B_duty_cycle = 255;
            animation_step = 3;
            // Serial.println("Step: 3");
        }
        break;
    case 3:
        if (G_duty_cycle > 0) {
            G_duty_cycle -= BRIGHTNESS_STEP;
        }
        else {
            G_duty_cycle = 0;
            animation_step = 4;
            // Serial.println("Step: 4");
        }
        break;
    case 4:
        if (R_duty_cycle < 255) {
            R_duty_cycle += BRIGHTNESS_STEP;
        }
        else {
            R_duty_cycle = 255;
            animation_step = 5;
            // Serial.println("Step: 5");
        }
        break;
    case 5:
        if (B_duty_cycle > 0) {
            B_duty_cycle -= BRIGHTNESS_STEP;
        }
        else {
            B_duty_cycle = 0;
            animation_step = 0;
            // Serial.println("Step: 0");
        }
        break;
    default:
        break;
    }

    R_time_on = get_delay(R_duty_cycle, CYCLE_DELAY);
    // R_time_off = get_delay(255 - R_duty_cycle, CYCLE_DELAY);
    G_time_on = get_delay(G_duty_cycle, CYCLE_DELAY);
    // G_time_off = get_delay(255 - G_duty_cycle, CYCLE_DELAY);
    B_time_on = get_delay(B_duty_cycle, CYCLE_DELAY);
    // B_time_off = get_delay(255 - B_duty_cycle, CYCLE_DELAY);
}

uint16_t get_delay(uint8_t duty_cicle, uint16_t total_microseconds) {
    uint16_t time = total_microseconds * (float)duty_cicle / 255;
    return time;
}