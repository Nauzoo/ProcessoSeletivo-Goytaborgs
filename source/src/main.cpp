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

void spinRightEngineFoward(){
  /* Gira o motor direito na dirção anti-horaria */
  
  ledcWrite(RIGHT_ENGINE_A, SPIN_FULL_INTENSITY); // Maldade do Vinicius: "usar a funcao ledcWrite ao inves de digital write" 
  ledcWrite(RIGHT_ENGINE_B, 0);
}

void spinRightEngineBackwards(){
  /* Gira o motor direito na dirção horaria */
  
  ledcWrite(RIGHT_ENGINE_A, 0); // Maldade do Vinicius: "usar a funcao ledcWrite ao inves de digital write" 
  ledcWrite(RIGHT_ENGINE_B, SPIN_FULL_INTENSITY);
}


void setup() {
  // CONFIGURANDO OS PINOS PARA A SAIDA DE DADOS;
  pinMode(LEFT_ENGINE_A, OUTPUT);
  pinMode(LEFT_ENGINE_B, OUTPUT);
  pinMode(WEAPON_ACTIVATOR, OUTPUT);

  Serial.begin(115200); // Iniciando o monitor serial para debugging
  Dabble.begin("ROBOT_NAME_IS_A_SECRET"); // Definindo o nome do bluetooth

}

void loop() {
  Dabble.processInput();  // verifica a cada ciclo se há novos inputs do controle;

}
