//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%  DOMO5: ARDUINO CONTROL MOTORES + SENSORES. Incluye:                   %%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%    - Comunicacion puerto Serie         (9600 baudios)                  %%
//%%------------------------------------------------------------------------%%
//%%    - Motor derecha.                  (Pines 6-7-8)                     %%
//%%    - Motor Izquierda.                (Pines 9-10-11)                   %%
//%%------------------------------------------------------------------------%%
//%%    - Sensor Distancia frontal        (Pines 2  (Echo) y 3  (trigger))  %%
//%%    - Sensor Distancia izquierda      (Pines A0 (Echo) y A1 (trigger))  %%
//%%    - Sensor Distancia derecha        (Pines A2 (Echo) y A3 (trigger))  %%
//%%------------------------------------------------------------------------%%
//%%    - Tira de leds                    (Pin   12)                        %%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%    COMANDOS SERIAL:                                                    %%
//%%                                                                        %%
//%%          BAJO NIVEL:                                                   %%
//%%                                                                        %%
//%%              - u    : Adelante                                         %%
//%%              - d    : Atras                                            %%
//%%              - l    : Izquierda                                        %%
//%%              - r    : Derecha                                          %%
//%%              - v    : giro Izquierda                                   %%
//%%              - w    : giro Derecha                                     %%
//%%              - s    : Stop                                             %%
//%%              - x    : Laser ON/OFF                                     %%
//%%              - t    : Temperatura                                      %%
//%%              - h    : Humedad                                          %%
//%%              - a    : Intensidad de luz                                %%
//%%              - k    : reset                                            %%
//%%              - m    : velocidad 25%                                    %%
//%%              - n    : velocidad 50%                                    %%
//%%              - o    : velocidad 75%                                    %%
//%%              - p    : velocidad 100%                                   %%
//%%                                                                        %%
//%%          ALTO NIVEL:                                                   %%
//%%                                                                        %%
//%%              - 0    : Aleatorio                                        %%
//%%              - 1    : Aburrido                                         %%
//%%              - 2    : Sorpresa                                         %%
//%%              - 3    : Susto                                            %%
//%%              - 4    : ACargador                                        %%
//%%              - 5    : Sígueme                                          %%
//%%                                                                        %%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//-----------------------------------------------------------------------------
// FUNCIONES
//-----------------------------------------------------------------------------
char cFuncion =(char) 0;   // Determina si estamos haciendo alguna funcion especial
                           // que requiere mas de un ciclo

#define  DireccionParo 0
#define  DireccionAdelante 1
#define  DireccionAtras 2
#define  DireccionDerecha 3
#define  DireccionIzquierda 4

int iDireccion=DireccionParo;    // Nos indica hacia donde nos movemos: 0:nada, 1 adelante, 2 detras, 3 derecha, 4 izquierda

void Distancia_Lee();
void Obstaculos_Lee();

unsigned long tAhora  = 0;

//============================================================================
// FUNCION GENERICA : ESPERA
//============================================================================
// Espera en Milisegundos, leyendo el serial por si recibimos cualquier orden
//============================================================================
void Espera(int iMiliSegundos)
{
  unsigned long inicio, fin, transcurrido;
  inicio = millis();
  fin = inicio + iMiliSegundos;
  transcurrido = 0;
  while (transcurrido <= fin)
  {
    transcurrido = millis();
    Serial_Lee();
    // Si solo queremos probar motores deshabilitamos esta linea
    Sensores_Lee();
  }
}

//============================================================================
// 2. SENSORES MOVIMIENTO (SI ME MUEVO)
//============================================================================
  void Sensores_Lee()
  {
  // Si me muevo, compruebo distancia al objeto mas proximo para corregir trayectoria
  if (iDireccion!=DireccionParo)
  {
    Distancia_Lee();          // Se lee distancia al objeto mas proximo y se actua en consecuencia
    // De momento no tenemos sensores de obstaculos
    //Obstaculos_Lee();         // Se lee sensor obstaculos y se actua en consecuencia
  }

  }

//-----------------------------------------------------------------------------
// LIBRERIAS
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Propias
//-----------------------------------------------------------------------------
#include "Serie.h"
#include "Motores.h"
#include "Leds.h"
#include "Distancia.h"
#include "FuncionesCombinadas.h"

//============================================================================
// INICIALIZACION
//============================================================================
void Reset()
{
  Serie_Inicializa();
  Motor_Inicializa();
  Distancia_Incializa();
  Leds_Inicializa();
}

//============================================================================
// INICIALIZACION
//============================================================================
void setup()
{
  Reset();
}

//============================================================================
// BUCLE INFINITO
//============================================================================
void loop()
{
  
  tAhora = millis();
  //-------------------------------------------------
  // 1. LEER SERIAL
  //-------------------------------------------------
  Serial_Lee();             // Se pueden mover motores, pedir temperatura, humedad o luminosidad

  Sensores_Lee();           // Si me muevo, compruebo distancia al objeto mas proximo para corregir trayectoria

  //-------------------------------------------------
  // 3. FUNCIONES ESPECIALES           
  //-------------------------------------------------
//  switch ((char)cFuncion) {
//    case 's': Motor_Sigueme();  break; // Funcion sigueme
//    case 'l': Latido_Lee();  break;// Se lee latido del corazon
//  }

  // Si nos estams moviendo hacemos el efecto kitt cada 5 segundos
  Efecto_KITT();
}

//=======================================================================
// SI leemos algo entendible del serial, mandamos la orden determinada
//=======================================================================
void Serial_Lee()
{
 if (Serial.available() > 0)
  {
    char TeclaApretada = Serial.read();
    Serie_Envia(TeclaApretada,"Motores: ok");
    switch ((char)TeclaApretada) {
      case 'u': Motor_Adelante(100);    break;
      case 'd': Motor_Atras(100);       break;
      case 'r': Motor_Derecha(100);     break;
      case 'l': Motor_Izquierda(100);   break;
      case 'w': Motor_Derecha_Parado(100);     break;
      case 'v': Motor_Izquierda_Parado(100);   break;
      case 's': Motor_Parar();          break;
//      case 'x': Laser_Encender();       break;
//      case 't': Temperatura_Enviar();   break;
//      case 'h': Humedad_Enviar();       break;
//      case 'a': Luz_Enviar();           break;
      case 'k': Reset();                break;
      case '0': Motor_Aleatorio();      break;
      case '1': Motor_Aburrido();       break;
      case '2': Motor_Sorpresa();       break;
      case '3': Motor_Susto();          break;
      case '4': Motor_ACargador();      break;
//      case '5': Motor_Sigueme();        break;
	  case 'm': Motor_Velocidad(25);			break;
	  case 'n': Motor_Velocidad(50);			break;
	  case 'o': Motor_Velocidad(75);			break;
	  case 'p': Motor_Velocidad(100);			break;
    case 'x': Leds_KnightRider();      break;
    case 'y': Leds_Efecto1(1);      break;
	  default:      break;
    }
  }
}
