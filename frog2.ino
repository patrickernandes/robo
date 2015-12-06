//fonte: http://arduino.cc/en/Tutorial/StepperUnipolar
//branco+preto+preto+branco

/*
//fonte: http://blog.filipeflop.com/sensores/sensor-ultrassonico-hc-sr04.html
#include <Ultrasonic.h>
 
#define echoPin 13 //Pino 13 recebe o pulso do echo
#define trigPin 12 //Pino 12 envia o pulso para gerar o echo
 
//iniciando a função e passando os pinos
Ultrasonic ultrasonic(12,13);
 
void setup()
{
Serial.begin(9600); //inicia a porta serial
pinMode(echoPin, INPUT); // define o pino 13 como entrada (recebe)
pinMode(trigPin, OUTPUT); // define o pino 12 como saida (envia)
}
 
void loop()
{
//seta o pino 12 com um pulso baixo "LOW" ou desligado ou ainda 0
digitalWrite(trigPin, LOW);
// delay de 2 microssegundos
delayMicroseconds(2);
//seta o pino 12 com pulso alto "HIGH" ou ligado ou ainda 1
digitalWrite(trigPin, HIGH);
//delay de 10 microssegundos
delayMicroseconds(10);
//seta o pino 12 com pulso baixo novamente
digitalWrite(trigPin, LOW);
// função Ranging, faz a conversão do tempo de
//resposta do echo em centimetros, e armazena
//na variavel distancia
int distancia = (ultrasonic.Ranging(CM));
Serial.print("Distancia em CM: ");
Serial.println(distancia);
delay(1000); //espera 1 segundo para fazer a leitura novamente
}
*/

#include <Servo.h>
#include <IRremote.h>  

Servo s1; // Variável Servo
int servo1 = 2; // Porta Digital 2 PWM
int pos1; // Posição Servo

Servo s2; // Variável Servo
int servo2 = 3; // Porta Digital 3 PWM
int pos2; // Posição Servo

int infra = 0;
int led1 = 24;
int servoD = 1;
int servoE = 5;
int sonicecho = 48;
int sonictrig = 49;
int motorCD1 = 4;
int motorCD2 = 7;
int motorCD3 = 8;
int motorCD4 = 12;
int motorE1 = 6;
int motorE2 = 9;
int motorD1 = 10;
int motorD2 = 11;
int switch1 = 34;
int motorDelay = 10;
int objDistance = 20; //define a distancia pra acionar o sensor

//IR
int RECV_PIN = 25; //Ligado ao pino do receptor IR
int armazenavalor = 0;   
IRrecv irrecv(RECV_PIN);  
decode_results results;  

void setup() 
{
  Serial.begin(9600); //inicia a porta serial
  pinMode(servo1, OUTPUT);
  pinMode(servo2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(servoD, OUTPUT);
  pinMode(servoE, OUTPUT);
  pinMode(sonicecho, INPUT); 
  pinMode(sonictrig, OUTPUT); 
  pinMode(motorCD1, OUTPUT);
  pinMode(motorCD2, OUTPUT);
  pinMode(motorCD3, OUTPUT);
  pinMode(motorCD4, OUTPUT);
  pinMode(motorE1, OUTPUT);
  pinMode(motorE2, OUTPUT);
  pinMode(motorD1, OUTPUT);
  pinMode(motorD2, OUTPUT);
  pinMode(switch1, INPUT);
  Serial.println("Sistema Iniciado!!");  
  irrecv.enableIRIn(); // Inicializa o receptor IR  
  
}

void loop() 
{
  //led();
  ultrasonic(); 
  
  if(Serial.available() > 0)
  {
    int entrada = Serial.read();

    switch(entrada)
    {
      case 'f':
        motorParar();
        delay(1000);
        motorFrente();
        break;

      case 'r':
        motorParar();
        delay(1000);
        motorRe();
        break;

      case 'd':
        motorDireita();
        break;

      case 'e':
        motorEsquerda();
        break;
        
      case 'p':
        motorParar();
        break;

      default:
        motorParar();
    }
  }
  
  s1.attach(servo1);
  s1.write(0); // Inicia motor posição zero
  
  s2.attach(servo2);
  s2.write(0);
  
  for(pos1 = 0; pos1 < 180; pos1 += 1)  // goes from 0 degrees to 180 degrees
  {                                  // in steps of 1 degree
    s1.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for(pos1 = 180; pos1>=1; pos1-=1)     // goes from 180 degrees to 0 degrees
  {
    s1.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  //IR
  if (irrecv.decode(&results))   
  {  
    //Mostra na serial o valor lido pelo sensor IR
    Serial.print("Valor lido : "); 
    Serial.println(results.value, HEX);
    //Armazena o sinal recebido pelo sensor IR  
    armazenavalor = (results.value);   
    switch (armazenavalor)  
    { 
     case 0xFF42BD:
     irLed();
     break;
     
     case 0xFF02FD: //Verifica se a tecla vermelha foi acionada  
      motorParar();
      break;  
      
     case 0xFF629D: //Verifica se a tecla amarela foi acionada  
      motorParar();
      delay(1000);
      motorFrente();
      break;  
    }  
  irrecv.resume(); //Le o próximo valor  
  }   

 
}//FIM   

void irLed()
{
  if(digitalRead(led1)==LOW)
  {
    digitalWrite(led1, HIGH);
  }
  else
  {
    digitalWrite(led1, LOW);
  }
}


void led()
{
  if(digitalRead(switch1)==LOW)
  {      
    digitalWrite(led1, HIGH);   
    delay(1000);               
    digitalWrite(led1, LOW);    
    delay(1000);
  }
}

void ultrasonic()
{
  digitalWrite(sonictrig, LOW);
  delayMicroseconds(2);
  digitalWrite(sonictrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonictrig, LOW);  
  long duration = pulseIn(sonicecho,HIGH);
  long distancia = duration /29 / 2 ;
  Serial.print("Distancia em CM: ");
  Serial.println(distancia);
  delay(1000); //espera 1 segundo para fazer a leitura novamente
  if (distancia < objDistance and digitalRead(switch1)==LOW)
    {  
      Serial.println("Para cima!");
      for (int x=0; x<60; x++)
      {         
        forward();
      }   
      //while(digitalRead(switch1)==LOW) 
      //{ 
      //  Serial.println("oi!");        
      //  forward();        
      //}       
      
    } 
  else if(distancia < objDistance and (digitalRead(switch1)==HIGH))
    {
      Serial.println("Para baixo!");
      for (int x=0; x<60; x++)
      {         
        backward();
      }   
    }

}//FIM loop


void forward()
{    
  digitalWrite(motorCD1, HIGH);
  digitalWrite(motorCD2, LOW);
  digitalWrite(motorCD3, LOW);
  digitalWrite(motorCD4, LOW);
  delay(motorDelay);
  digitalWrite(motorCD1, LOW);
  digitalWrite(motorCD2, HIGH);
  digitalWrite(motorCD3, LOW);
  digitalWrite(motorCD4, LOW);
  delay(motorDelay);
  digitalWrite(motorCD1, LOW);
  digitalWrite(motorCD2, LOW);
  digitalWrite(motorCD3, HIGH);
  digitalWrite(motorCD4, LOW);
  delay(motorDelay);
  digitalWrite(motorCD1, LOW);
  digitalWrite(motorCD2, LOW);
  digitalWrite(motorCD3, LOW);
  digitalWrite(motorCD4, HIGH);
  delay(motorDelay); 
}

void backward()
{   
  digitalWrite(motorCD1, LOW);
  digitalWrite(motorCD2, LOW);
  digitalWrite(motorCD3, LOW);
  digitalWrite(motorCD4, HIGH);
  delay(motorDelay);
  digitalWrite(motorCD1, LOW);
  digitalWrite(motorCD2, LOW);
  digitalWrite(motorCD3, HIGH);
  digitalWrite(motorCD4, LOW);
  delay(motorDelay);
  digitalWrite(motorCD1, LOW);
  digitalWrite(motorCD2, HIGH);
  digitalWrite(motorCD3, LOW);
  digitalWrite(motorCD4, LOW);
  delay(motorDelay);
  digitalWrite(motorCD1, HIGH);
  digitalWrite(motorCD2, LOW);
  digitalWrite(motorCD3, LOW);
  digitalWrite(motorCD4, LOW);
  delay(motorDelay);   
}

void motorParar()
{
  Serial.println("Motor parado!");
  digitalWrite(motorE1, LOW);
  digitalWrite(motorE2, LOW);
  digitalWrite(motorD1, LOW);
  digitalWrite(motorD2, LOW);
}

void motorFrente()
{
  Serial.println("Robo para frente!");
  digitalWrite(motorD1, HIGH);
  digitalWrite(motorD2, LOW);
  digitalWrite(motorE1, HIGH);
  digitalWrite(motorE2, LOW);
}

void motorRe()
{
  Serial.println("Robo para traz!");
  digitalWrite(motorD1, LOW);
  digitalWrite(motorD2, HIGH);
  digitalWrite(motorE1, LOW);
  digitalWrite(motorE2, HIGH);
}  

void motorDireita()
{
  Serial.println("Robo para direita!");
  digitalWrite(motorD1, HIGH);
  digitalWrite(motorD2, LOW);    
}  

void motorEsquerda()
{
  Serial.println("Robo para esquerda!");
  digitalWrite(motorE1, HIGH);
  digitalWrite(motorE2, LOW);  
}  
