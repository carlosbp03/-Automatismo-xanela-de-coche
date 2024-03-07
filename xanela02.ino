/*
Programa para simular el funcionamiento de la ventanilla de un coche.
El botón activa el motor de elevación cuando se presiona y una segunda
pulsación detiene el motor y a la tercera hace que se accione el motor
de bajada.Se añaden 2 finales de carrera (pin 5, pin 6), uno para 
arriba y otro para abajo.

Entradas: Pulsador,finales de carrera (3x dixital)
Salidas: Relé (2x digital)

Autor: Juan Carlos Breijo Pérez
Data: Febrero de 2024
*/

#define ventanillaArriba 11
#define ventanillaAbajo 12
#define pulsador     7
#define fcArriba     6
#define fcAbajo     5

int estado = 1;    //valores: 0(arriba) , 1(paro) , 2(abajo) , 3(para)
int contador = 0; // Contador para el número de impulsos al motor

void setup() {
  pinMode(ventanillaArriba, OUTPUT);
  pinMode(ventanillaAbajo, OUTPUT);
  pinMode(pulsador, INPUT);
  pinMode(fcArriba, INPUT);
  pinMode(fcAbajo, INPUT);
  
  Serial.begin(9600);
  int estado;
  
  Serial.println(estado);
}

void loop() {
  // Lectura del pulsador
  if(digitalRead(pulsador)) {
    estado++; 
    if(estado > 3) {
      estado = 0;
    }
    
    contador = 100;
    while(digitalRead(pulsador)) {
      delay(20);
    }
  }
  
  if(digitalRead(fcArriba)) {
    if(estado != 2) {
      estado = 1;
    }
    delay(20);
  }
  
  if(digitalRead(fcAbajo)) {
   if(estado != 0) {
      estado = 3;
   }
    delay(20);
  }
  // Fin de la lectura del pulador
  
  Serial.print("valor do contador: ");
  Serial.println(contador);
  Serial.print("estado: ");
  Serial.println(estado);
  
  // Accionamiento de los motores
  if(contador > 0) {
    if(estado == 0) {
      digitalWrite(ventanillaArriba, HIGH);
      digitalWrite(ventanillaAbajo, LOW);
      delay(70);
    }
    else if(estado == 2) {
      digitalWrite(ventanillaArriba, LOW);
      digitalWrite(ventanillaAbajo, HIGH);
      delay(70);
    }
    else {
      digitalWrite(ventanillaArriba, LOW);
      digitalWrite(ventanillaAbajo, LOW);
    }
  }
}
