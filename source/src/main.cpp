#include <Arduino.h>
#include <DabbleESP32.h>


/*
  Definicao dos pinos PWM para o controle de cada um dos motores;
 */

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

const int PWM_freq = 1000;          // 1Khz  
const int PWM_res = 8;              // 8bits (0-255)

void spinRightEngineFoward(int speed){
  /* Gira o motor direito na dirção anti-horaria */
  
  ledcWrite(RIGHT_ENGINE_A, speed); // Maldade do Vinicius: "usar a funcao ledcWrite ao inves de digital write" 
  ledcWrite(RIGHT_ENGINE_B, 0);
}

void spinRightEngineBackwards(int speed){
  /* Gira o motor direito na dirção horaria */
  
  ledcWrite(RIGHT_ENGINE_A, 0);                   // Maldade do Vinicius: "usar a funcao ledcWrite ao inves de digital write" 
  ledcWrite(RIGHT_ENGINE_B, speed);
}

void spinLeftEngineFoward(int speed){
  /* Gira o motor esquerdo na dirção anti-horaria */
  
  ledcWrite(LEFT_ENGINE_A, speed); // Maldade do Vinicius: "usar a funcao ledcWrite ao inves de digital write" 
  ledcWrite(LEFT_ENGINE_B, 0);
}

void spinLeftEngineBackwards(int speed){
  /* Gira o motor esquerdo na dirção horaria */
  
  ledcWrite(LEFT_ENGINE_A, 0);                   // Maldade do Vinicius: "usar a funcao ledcWrite ao inves de digital write" 
  ledcWrite(LEFT_ENGINE_B, speed);
}


void setup() {
  // CONFIGURANDO OS PINOS PARA A SAIDA DE DADOS;

  pinMode(WEAPON_ACTIVATOR, OUTPUT);

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
  Dabble.processInput();  // verifica a cada ciclo se há novos inputs do controle;
  
  if (GamePad.isTrianglePressed()){
    // Ativar arma
  }

  // Controlar a direcao de movimento pelo analogico
}
