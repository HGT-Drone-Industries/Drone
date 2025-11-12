#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define PIN_CE 7
#define PIN_CSN 8

#define PIN_MOTOR_0 3
#define PIN_MOTOR_1 5
#define PIN_MOTOR_2 6
#define PIN_MOTOR_3 9

RF24 radio(PIN_CE, PIN_CSN); // CE, CSN

const byte address[6] = "00001";

struct Vec2i {
  int16_t x;
  int16_t y;
};

struct Input {
  Vec2i left;
  bool left_button;
  Vec2i right;
  bool right_button;
};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  Serial.println("Setup radio");
  pinMode(3, OUTPUT);;
}

void vec2i_print(const Vec2i *vec2i) {
  Serial.print("{.x = ");
  Serial.print(vec2i->x);
  Serial.print(", .y = ");
  Serial.print(vec2i->y);
  Serial.print("}");
}

void input_print(const Input *input) {
  Serial.print("{.left = ");
  vec2i_print(&input->left);
  Serial.print(", .right = ");
  vec2i_print(&input->right);
  Serial.print(", .left_button = ");
  Serial.print(input->left_button);
  Serial.print(", .right_button = ");
  Serial.print(input->right_button);
  Serial.println("}");
}

Input input = {
  {500, 500},   // left
  0,            // left_button
  {500, 500},   // right
  0             // right_button
};

void motors_power_all(uint8_t power) {
    analogWrite(PIN_MOTOR_0, power);
    analogWrite(PIN_MOTOR_1, power);
    analogWrite(PIN_MOTOR_2, power);
    analogWrite(PIN_MOTOR_3, power);
}

void loop() {
  Serial.println("Slay");
  if (radio.available()) {
    Serial.println("Radio is available");
    radio.read(&input, sizeof(Input));
    input_print(&input);
  }

  if (input.left.y < 100 || input.right.y < 100) {
    motors_power_all(255);
  } else {
    motors_power_all(0);
  }
}
                                                           