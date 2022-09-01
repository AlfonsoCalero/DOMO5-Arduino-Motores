//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%																												                                                        %%
//%%																												                                                        %%
//%%																												                                                        %%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%																												                                                        %%
//%%																												                                                        %%
//%%																												                                                        %%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#define  Pin_SensorDistancia_Echo_Centro        2
#define  Pin_SensorDistancia_Trigger_Centro     3

#define  Pin_SensorDistancia_Echo_Izquierda     A0
#define  Pin_SensorDistancia_Trigger_Izquierda  A1

#define  Pin_SensorDistancia_Echo_Derecha       A2
#define  Pin_SensorDistancia_Trigger_Derecha    A3

#define Distancia_Paro 20         // Disancia en cm. en la que se para
#define Distancia_Aviso 30        // Distancia en cm. en la que nos avisa con led rojo

int iRangoAnteriorDerecha=1000;
int iRangoAnteriorCentro=1000;
int iRangoAnteriorIzquierda=1000;

unsigned long tAntes1 = 0;

//====================================================================================================================
// INICIALIZACION
//====================================================================================================================
void Distancia_Incializa()
{
   pinMode(Pin_SensorDistancia_Trigger_Centro, OUTPUT);
   pinMode(Pin_SensorDistancia_Echo_Centro, INPUT);
   pinMode(Pin_SensorDistancia_Trigger_Izquierda, OUTPUT);
   pinMode(Pin_SensorDistancia_Echo_Izquierda, INPUT);
   pinMode(Pin_SensorDistancia_Trigger_Derecha, OUTPUT);
   pinMode(Pin_SensorDistancia_Echo_Derecha, INPUT);
}

//====================================================================================================================
// PING Y DEVUELVE DISTANCIA EN CM.
//====================================================================================================================
int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}

//====================================================================================================================
//====================================================================================================================
int Distancia_DevuelveDistanciaFrontal()
{
  int cm =   ping(Pin_SensorDistancia_Trigger_Centro, Pin_SensorDistancia_Echo_Centro);
   //Serie_Envia('DF',(String)cm);
  return cm;
}

//====================================================================================================================
//====================================================================================================================
int Distancia_DevuelveDistanciaIzquierda()
{
  int cm =   ping(Pin_SensorDistancia_Trigger_Izquierda, Pin_SensorDistancia_Echo_Izquierda);
   //Serie_Envia('DI',(String)cm);
  return cm;
}

//====================================================================================================================
//====================================================================================================================
int Distancia_DevuelveDistanciaDerecha()
{
  int cm =   ping(Pin_SensorDistancia_Trigger_Derecha, Pin_SensorDistancia_Echo_Derecha);
   //Serie_Envia('DD',(String)cm);
  return cm;
}

//====================================================================================================================
//====================================================================================================================
int Rango(int cm)
{
     int iRango;

    iRango = (int)(cm/10); 
    iRango=iRango*10;
   return iRango;
}

//====================================================================================================================
//====================================================================================================================
void EnviaSerieDistancia(char Parametro, int iDistancia)
{
     if( tAhora - tAntes1 > 1000 )
   {
      tAntes1 = tAhora;
      // Si ha pasado 1 segundo desde el ultimo envio enviamos (para no saturar al receptor)
      Serie_Envia(Parametro,String(iDistancia));
   }
   

}
//====================================================================================================================
//====================================================================================================================
void Distancia_Lee()
{
    // MEDIMOS DISTANCIA, Y LO PASAMOS A RANGO
   int iRangoCentro = Rango(Distancia_DevuelveDistanciaFrontal());
  // CENTRO
  if (iRangoCentro!=iRangoAnteriorCentro)
  {
    bool bCentro=false;
    iRangoAnteriorCentro=iRangoCentro;
    
    if (iRangoCentro <=Distancia_Aviso) {Leds_Sensor(CRGB::Green,6,7); bCentro=true;}                                     // Rojo
    //   if (cm_centro >Distancia_Aviso and cm_centro <=75) {Leds_Sensor(CRGB::Yellow,6,7); bCentro=true;}                // Amarillo
    //   if (cm_centro >75 and cm_centro <=100) {Leds_Sensor(CRGB::Red,6,7); bCentro=true;}                               //Verde
    if (iRangoCentro<=Distancia_Paro && iDireccion==DireccionAdelante)      {Motor_Parar(); EnviaSerieDistancia('F',iRangoCentro); } //Motor_CorregirTrayectoria(); }   // Paro
    if (!bCentro) Leds_Sensor_Apaga(6,7);
  }
   delayMicroseconds(10);
   int iRangoDerecha   = Rango(Distancia_DevuelveDistanciaDerecha());
  // DERECHA
  if (iRangoDerecha!=iRangoAnteriorDerecha)
  {
    bool bDerecha=false;
    iRangoAnteriorDerecha=iRangoDerecha;
    
    if (iRangoDerecha <=Distancia_Aviso) {Leds_Sensor(CRGB::Green,1,2); bDerecha=true;}                                     // Rojo
    //   if (iRangoDerecha >Distancia_Aviso and iRangoDerecha <=75) {Leds_Sensor(CRGB::Yellow,1,2); bDerecha=true;}                // Amarillo
    //   if (iRangoDerecha >75 and iRangoDerecha <=100) {Leds_Sensor(CRGB::Red,1,2); bDerecha=true;}                               //Verde
    if (iRangoDerecha<=Distancia_Paro && iDireccion==DireccionDerecha)   {Motor_Parar(); EnviaSerieDistancia('D',iRangoDerecha); } //Motor_CorregirTrayectoria(); }   // Paro
    if (!bDerecha) Leds_Sensor_Apaga(1,2);
  }
   delayMicroseconds(10);
   int iRangoIzquierda = Rango(Distancia_DevuelveDistanciaIzquierda());
   // IZQUIERDA
  if (iRangoIzquierda!=iRangoAnteriorIzquierda)
  {
    bool bIzquierda=false;
    
    iRangoAnteriorIzquierda=iRangoIzquierda;
    
    if (iRangoIzquierda <=Distancia_Aviso) {Leds_Sensor(CRGB::Green,10,11); bIzquierda=true;}                                     // Rojo
    //   if (iRangoIzquierda >Distancia_Aviso and iRangoIzquierda <=75) {Leds_Sensor(CRGB::Yellow,10,11); bIzquierda=true;}                // Amarillo
    //   if (iRangoIzquierda >75 and iRangoIzquierda <=100) {Leds_Sensor(CRGB::Red,10,11); bIzquierda=true;}                               //Verde
    if (iRangoIzquierda<=Distancia_Paro && iDireccion==DireccionIzquierda) {Motor_Parar(); EnviaSerieDistancia('I',iRangoIzquierda); } //Motor_CorregirTrayectoria(); }   // Paro
    if (!bIzquierda) Leds_Sensor_Apaga(10,11);
  }
}
