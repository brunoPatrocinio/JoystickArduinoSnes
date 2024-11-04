//Controle Snes com Arduino e Joystick shield V 1.0.0
//Bruno Patrocinio - coder
//######################################################

#define x A0
#define y A1
#define k 8
#define fSelect 7
#define eStart 6
#define dY 5
#define cB 4
#define bA 3
#define aX 2
#define bL 9
#define bR 10

//Pinos para comunicação com o Snes
const int dataPin = 11;
const int latchPin = 12;
const int clockPin = 13;

//array dos botões
int buttonStates[12];

void setup() {
  for(int i =0; i <=10; i++){
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(latchPin, INPUT);
  pinMode(clockPin, INPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  buttonStates[0] = digitalRead(cB);
  buttonStates[1] = digitalRead(dY);
  buttonStates[2] = digitalRead(fSelect);
  buttonStates[3] = digitalRead(eStart);
  //buttonStates[4] = digitalRead(buttonUp);
  //buttonStates[5] = digitalRead(buttonDown);
  if(analogRead(y) >= 556){
    buttonStates[4] = HIGH; //up
  }
  else if(analogRead(y) <= 450){
    buttonStates[5] = HIGH; //down
  }
  else if(analogRead(x) >= 570){
    buttonStates[7] = HIGH; //right
  }
  else if(analogRead(x) <= 450){ //left
    buttonStates[6] = HIGH;
  }
  else{
    //nada
  }
  buttonStates[8] = digitalRead(bA);
  buttonStates[9] = digitalRead(aX);
  buttonStates[10] = digitalRead(bL);
  buttonStates[11] = digitalRead(bR);

  //aguarda pelo pulso de sincronismo do snes
  if(digitalRead(latchPin) == HIGH){
    //envia cada estado de botão a cada pulso de clock
    for(int i=0; i <12; i++){
      while(digitalRead(clockPin) == HIGH);
      while(digitalRead(clockPin) == LOW);

      //envia o estado de cada pino
      digitalWrite(dataPin, buttonStates[i]);
    }
    digitalWrite(dataPin, HIGH);
  }
  //para testes
  /*
  int x_read = analogRead(x);
  int y_read = analogRead(y);
  Serial.print("X val:  ");
  Serial.println("Y val:  ");
  Serial.println(x_read);
  Serial.print("    ");
  Serial.println(y_read);

       if(!digitalRead(k)) Serial.println("K pressionado");
  else if(!digitalRead(fSelect)) Serial.println("F pressionado");
  else if(!digitalRead(eStart)) Serial.println("E pressionado");
  else if(!digitalRead(dY)) Serial.println("D pressionado");
  else if(!digitalRead(cB)) Serial.println("C pressionado");
  else if(!digitalRead(bA)) Serial.println("B pressionado");
  else if(!digitalRead(aX)) Serial.println("A pressionado");
  else    Serial.print("Nada Pressionado.");
  */
  delay(100);

}
