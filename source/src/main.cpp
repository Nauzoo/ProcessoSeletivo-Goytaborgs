#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Arduino.h>
#include <DabbleESP32.h>


/* Definicao dos pinos PWM para o controle de cada um dos motores; */
// PS: Os valores dos pinos poderam ser alterados dps;
#define LEFT_ENGINE_A 25
#define LEFT_ENGINE_B 26

#define RIGHT_ENGINE_A 32
#define RIGHT_ENGINE_B 33

#define WEAPON_ACTIVATOR 27

#define SPIN_FULL_INTENSITY 255
#define SPIN_HALF_INTENSITY 127

const int right_engine_channel_a = 0; // canal de PWM, desse modo é possivel controlar o GPIO com facilidade
const int right_engine_channel_b = 1;
const int left_engine_channel_a = 2;
const int left_engine_channel_b = 3;

const int PWM_freq = 1000;            // 1Khz  
const int PWM_res = 8;                // 8bits (0-255)

struct Weapon
{
  public:
    static bool state;
    
    static void turnWeaponOn() {
      digitalWrite(WEAPON_ACTIVATOR, HIGH);
      state = true;
    }

    static void turnWeaponOff(){
      digitalWrite(WEAPON_ACTIVATOR, LOW);
      state = false;
    }

    static void togleWeapon(){
      state ? turnWeaponOff() : turnWeaponOn();
    }

};
bool Weapon::state = false;

struct Engines
{
  /*  PONTE H MX1508 VALORES
     IN1/IN3 | IN2/IN4 | DIR  
      
      LOW    |  LOW    | STANDBY
      PWM    |  LOW    | FOWARD
      LOW    |  PWM    | REVERSE
      HIGH   |  HIGH   | STATIC
  */
  public:
  static void leftEngineSpin(u_int8_t foward, u_int8_t backwards) {
    ledcWrite(LEFT_ENGINE_A, foward);
    ledcWrite(LEFT_ENGINE_B, backwards);
  }
  static void rightEngineSpin(u_int8_t foward, u_int8_t backwards) {
    ledcWrite(RIGHT_ENGINE_A, foward);
    ledcWrite(RIGHT_ENGINE_B, backwards);
  }
  
};

struct DirectionCore{

  public:
  static void move(){

    // Otimizações para reduzir a quantidade de condicionais

    u_int8_t pin_left_speed = GamePad.isSquarePressed() ? 0 : SPIN_FULL_INTENSITY;
    u_int8_t pin_right_speed = GamePad.isCirclePressed() ? 0 : SPIN_FULL_INTENSITY;

    if (GamePad.isUpPressed()) {
      Engines::leftEngineSpin(pin_left_speed, 0);
      Engines::rightEngineSpin(pin_right_speed, 0);
    }
    else if (GamePad.isDownPressed()){
      Engines::leftEngineSpin(0, pin_left_speed);
      Engines::rightEngineSpin(0, pin_right_speed);
    }
    else {
      if (pin_left_speed == 0 || pin_right_speed == 0){         // Necessario para n fazer o robo girar infinitamente
        Engines::leftEngineSpin(pin_left_speed, pin_right_speed);
        Engines::rightEngineSpin(pin_right_speed, pin_left_speed);
      }
    }
  }
};


void setup() {
  // CONFIGURANDO OS PINOS PARA A SAIDA DE DADOS;

  pinMode(WEAPON_ACTIVATOR, OUTPUT);
  Weapon::turnWeaponOff();          // iniciando com a arma desligada.

  ledcSetup(right_engine_channel_a, PWM_freq, PWM_res);
  ledcSetup(right_engine_channel_b, PWM_freq, PWM_res);
  ledcSetup(left_engine_channel_a, PWM_freq, PWM_res);
  ledcSetup(left_engine_channel_b, PWM_freq, PWM_res);

  ledcAttachPin(RIGHT_ENGINE_A, right_engine_channel_a);
  ledcAttachPin(RIGHT_ENGINE_B, right_engine_channel_b);
  ledcAttachPin(LEFT_ENGINE_A, left_engine_channel_a);
  ledcAttachPin(LEFT_ENGINE_B, left_engine_channel_b);

  Serial.begin(115200);                   // Iniciando o monitor serial para debugging
  Dabble.begin("ROBOT_NAME_IS_A_SECRET"); // Definindo o nome do bluetooth

}

void loop() {
  Dabble.processInput();              // verifica a cada ciclo se há novos inputs do controle
  
  if (!Dabble.isAppConnected()){      // Deliga todo o sistema caso o app seja desconectado
    Weapon::turnWeaponOff();
    Engines::leftEngineSpin(0, 0);
    Engines::rightEngineSpin(0, 0);
  }

  if (GamePad.isStartPressed()){
    Weapon::togleWeapon();
    delay(100);                     // solução temporaria, pode ser mudada para um "isTriangleReleased"
  }

  // Joystick não é uma boa opçao pq n há um meio de caucular precisamente a rotação do robo.
  // Vamos usar o D-Pad ao invés disso.
  DirectionCore::move();

}
