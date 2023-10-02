const int AlimentadorPin =  12;
const int CortadorPin =  13;
const int VibradorPin = 11;

boolean AlimentadorPinEstado = LOW;
boolean CortadorPinEstado = LOW;
boolean VibradorPinEstado = LOW;

unsigned long Tiempo = 0;
unsigned long PrevioAlimentadorTiempo = 0;
unsigned long PrevioCortadorTiempo = 0;
unsigned long PrevioVibradorTiempo = 0;

unsigned long IntervaloAlimentador = 100;
unsigned long IntervaloCorteBajo = 100;
unsigned long IntervaloCorteAlto = 500;
unsigned long IntervaloVibradorAtras = 100;
unsigned long IntervaloVibradorAdelante = 100;

String inString = "";
byte opcion = 0;
int inChar;
boolean bandera = 0;

void setup() {
    Serial.begin(9600);
    pinMode(AlimentadorPin, OUTPUT);
    pinMode(CortadorPin, OUTPUT);
    pinMode(VibradorPin, OUTPUT);
}

void loop()
{

  if (bandera == 0){
    Serial.println("Para seteo del periodo del reloj del ALIMENTADOR ingrese -a- seguido del valor");
    Serial.println("Para seteo del tiempo de la cuchilla en CORTE ingrese -c- seguido del valor");
    Serial.println("Para seteo del tiempo de la cuchilla en ESPERA ingrese -e- seguido del valor");
    Serial.println("Para seteo del tiempo del vibrador para atras -v- seguido del valor");
    Serial.println("Para seteo del tiempo del vibrador para adelante -b- seguido del valor");
    Serial.print("El periodo del reloj de Alimentador es:");
    Serial.println(IntervaloAlimentador);
    Serial.print("El tiempo de la cuchilla en CORTE es:");
    Serial.println(IntervaloCorteBajo);
    Serial.print("El tiempo de la cuchilla en ESPERA es:");
    Serial.println(IntervaloCorteAlto);
    Serial.print("El tiempo del vibrador ATRAS es:");
    Serial.println(IntervaloVibradorAtras);
    Serial.print("El tiempo del vibrador ADELANTE es:");
    Serial.println(IntervaloVibradorAdelante);
    bandera = 1;
  }
  
  while (Serial.available() > 0) 
  {
    inChar = Serial.read();
    
    if (isDigit(inChar)) {
      inString += (char)inChar; 
    }
    else if (inChar == 'a'){
      opcion = 1;
    }
    else if (inChar == 'c'){
      opcion = 2;
    }
    else if (inChar == 'e'){
      opcion = 3;
    }
    else if (inChar == 'v'){
      opcion = 4;
    }
    else if (inChar == 'b'){
      opcion = 5;
    }
    delay(10);
  }

  if (opcion > 0){
    switch (opcion){
        
      case 1:
      IntervaloAlimentador = inString.toInt();
      break;
    
      case 2:
      IntervaloCorteBajo = inString.toInt();
      break;
    
      case 3:
      IntervaloCorteAlto = inString.toInt();
      break;

      case 4:
      IntervaloVibradorAtras = inString.toInt();
      break;

      case 5:
      IntervaloVibradorAdelante = inString.toInt();
      break;
    }
    //Serial.println(inString.toInt());
    opcion = 0;
    inString = "";
    bandera = 0;
  }
  

  Tiempo = millis();
 
  if(Tiempo - PrevioAlimentadorTiempo >= IntervaloAlimentador) {
    PrevioAlimentadorTiempo = Tiempo;   

    if (AlimentadorPinEstado == LOW)
      AlimentadorPinEstado = HIGH;
    else
      AlimentadorPinEstado = LOW;

    digitalWrite(AlimentadorPin, AlimentadorPinEstado);
  }

  if (CortadorPinEstado == HIGH){ 
    if (Tiempo - PrevioCortadorTiempo >= IntervaloCorteBajo){
      CortadorPinEstado = LOW;
      PrevioCortadorTiempo = Tiempo;
      digitalWrite(CortadorPin, CortadorPinEstado);
    }
  }
  else{ 
    if (Tiempo - PrevioCortadorTiempo >= IntervaloCorteAlto){
      CortadorPinEstado = HIGH;
      PrevioCortadorTiempo = Tiempo;
      digitalWrite(CortadorPin, CortadorPinEstado);
    }
  }

  if (VibradorPinEstado == HIGH){ 
    if (Tiempo - PrevioVibradorTiempo >= IntervaloVibradorAtras){
      VibradorPinEstado = LOW;
      PrevioVibradorTiempo = Tiempo;
      digitalWrite(VibradorPin, VibradorPinEstado);
    }
  }
  else{ 
    if (Tiempo - PrevioVibradorTiempo >= IntervaloVibradorAdelante){
      VibradorPinEstado = HIGH;
      PrevioVibradorTiempo = Tiempo;
      digitalWrite(VibradorPin, VibradorPinEstado);
    }
  }


}


