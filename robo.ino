//Patrick Ernandes
//
//
//arquivo da ponte H_brige fritzing retirado de: https://github.com/yohendry/arduino_L298N
//
//
int motorE1 = 8;
int motorE2 = 9;
int motorD1 = 10;
int motorD2 = 11;
int motorDelay = 10;
void motorParar();
void motorFrente();
void motorRe();
void motorDireita();
void motorEsquerda();


void setup() 
{
  Serial.begin(9600); //inicia a porta serial
  pinMode(motorE1, OUTPUT);
  pinMode(motorE2, OUTPUT);
  pinMode(motorD1, OUTPUT);
  pinMode(motorD2, OUTPUT);
  Serial.println("Sistema Iniciado!!");  
 
}

void loop() 
{
   
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
