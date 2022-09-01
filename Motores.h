//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%																												%%
//%%																												%%
//%%																												%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%																												%%
//%%																												%%
//%%																												%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//---------------------------------------------------------------------------
// MOTOR A
//---------------------------------------------------------------------------
#define  pinENA 6 // (PWM, para control de velocidad valores: 0-255)
#define  pinIN1 7 // (sentido de giro del motor)
#define  pinIN2 8 // (sentido de giro del motor)
//---------------------------------------------------------------------------
// MOTOR B
//---------------------------------------------------------------------------
#define  pinIN3 9   // (sentido de giro del motor)
#define  pinIN4 10  // (sentido de giro del motor)
#define  pinENB 11  // (PWM, para control de velocidad valores: 0-255)

const int pinMotorA[3] = { pinENA, pinIN1, pinIN2 };
const int pinMotorB[3] = { pinENB, pinIN3, pinIN4 };

int  iPorcentajeVelocidad = 100; // Valor entre 0 y 100, Se puede establecer mediante funcion Velocidad

//====================================================================================================================
// INICIALIZACION
//====================================================================================================================
void Motor_Inicializa()
{
    Serie_Envia('0',"Motores");
   pinMode(pinIN1, OUTPUT);
   pinMode(pinIN2, OUTPUT);
   pinMode(pinENA, OUTPUT);
   pinMode(pinIN3, OUTPUT);
   pinMode(pinIN4, OUTPUT);
   pinMode(pinENB, OUTPUT);
   iDireccion=DireccionParo;
   iPorcentajeVelocidad = 50;			// Velocidad = 50%
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%                                                                        %%
//%%                    FUNCIONES ALTO NIVEL                                %%
//%%                                                                        %%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//====================================================================================================================
// FUNCION BAJO NIVEL : ADELANTE 1 MOTOR
// Parametro: El pin del motor, la velocidad
//====================================================================================================================
void Adelante(const int pinMotor[3], int speed)
{
   digitalWrite(pinMotor[1], HIGH);
   digitalWrite(pinMotor[2], LOW);
   analogWrite(pinMotor[0], speed);
}
 
//====================================================================================================================
// FUNCION BAJO NIVEL : ATRAS 1 MOTOR
// Parametro: El pin del motor, la velocidad
//====================================================================================================================
void Atras(const int pinMotor[3], int speed)
{
   digitalWrite(pinMotor[1], LOW);
   digitalWrite(pinMotor[2], HIGH);
   analogWrite(pinMotor[0], speed);
}
 
//============================================================================
// FUNCION BAJO NIVEL : PARAR 1 MOTOR
// Parametro: El pin del motor
//============================================================================
void Parar(const int pinMotor[3])
{
   digitalWrite(pinMotor[1], LOW);
   digitalWrite(pinMotor[2], LOW);
   analogWrite(pinMotor[0], 0);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%                                                                        %%
//%%                    FUNCIONES BASICAS                                   %%
//%%                                                                        %%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//====================================================================================================================
// FUNCION BASICA: ADELANTE 2 MOTORES
// Parametro: Porcentaje de velocidad: 0% -100%
//====================================================================================================================
void Motor_Adelante(int Porcentaje)
{
  int Velocidad=(Porcentaje/100)*255;
   Adelante(pinMotorA, Velocidad);
   Adelante(pinMotorB, Velocidad);
   iDireccion=DireccionAdelante;
   //Serial.println("Motor:Adelante");
   Serie_Envia('M',"U");
}

//============================================================================
// FUNCION BASICA: ATRAS 2 MOTORES
// Parametro: Porcentaje de velocidad: 0% -100%
//============================================================================
void Motor_Atras(int Porcentaje)
{
  int Velocidad=(Porcentaje/100)*255;
   Atras(pinMotorA, Velocidad);
   Atras(pinMotorB, Velocidad);
   iDireccion=DireccionAtras;
   //Serial.println(F("Motor:Atras"));
   Serie_Envia('M',"D");
}

//============================================================================
// FUNCION BASICA: PARAR 2 MOTORES
//============================================================================
void Motor_Parar()
{
   Parar(pinMotorA);
   Parar(pinMotorB);
   iDireccion=DireccionParo;
   //Serial.println(F("Motor:Parar"));
   Serie_Envia('M',"S");
}


//============================================================================
// FUNCION BASICA: DERECHA 2 MOTORES
// Parametro: Porcentaje de velocidad: 0% -100%
// Version en movimiento: reducir velocidad al 50% de rueda contraria al giro
//============================================================================
void Motor_Derecha(int Porcentaje)
{
  int Velocidad=(Porcentaje/100)*255;
  int VelocidadMitad=Velocidad/2;
   Adelante(pinMotorA,VelocidadMitad);
   Adelante(pinMotorB, Velocidad);
   iDireccion=DireccionDerecha;
   //Serial.println(F("Motor:Derecha"));
   Serie_Envia('M',"R");
}

//============================================================================
// FUNCION BASICA: IZQUERDA 2 MOTORES
// Parametro: Porcentaje de velocidad: 0% -100%
// Version en movimiento: reducir velocidad al 50% de rueda contraria al giro
//============================================================================
void Motor_Izquierda(int Porcentaje)
{
  int Velocidad=(Porcentaje/100)*255;
  int VelocidadMitad=Velocidad/2;
   Adelante(pinMotorB,VelocidadMitad);
   Adelante(pinMotorA, Velocidad);
   iDireccion=DireccionIzquierda;
   Serie_Envia('M',"L");
   //Serial.println(F("Motor:Izquierda"));
}

//============================================================================
// FUNCION BASICA: DERECHA 2 MOTORES
// GIRO A LA DERECHA PARADO
// Parametro: Porcentaje de velocidad: 0% -100%
// Version anterior: motor B adelante, motor B atras.
//============================================================================
void Motor_Derecha_Parado(int Porcentaje)
{
  int Velocidad=(Porcentaje/100)*255;
   Atras(pinMotorA,Velocidad);
   Adelante(pinMotorB, Velocidad);
   iDireccion=DireccionDerecha;
   //Serial.println(F("Motor:Derecha"));
   Serie_Envia('M',"R");
}

//============================================================================
// FUNCION BASICA: IZQUERDA 2 MOTORES
// GIRO A LA IZQUIERDA PARADO
// Parametro: Porcentaje de velocidad: 0% -100%
// Version anterior: motor A adelante, motor B atras.
//============================================================================
void Motor_Izquierda_Parado(int Porcentaje)
{
  int Velocidad=(Porcentaje/100)*255;
   Atras(pinMotorB,Velocidad);
   Adelante(pinMotorA, Velocidad);
   iDireccion=DireccionIzquierda;
   Serie_Envia('M',"L");
   //Serial.println(F("Motor:Izquierda"));
}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%                                                                        %%
//%%                    FUNCIONES ALTO NIVEL                                %%
//%%                                                                        %%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//============================================================================
// Funcion provisional que corrige trayectoria (mejorable)
//============================================================================
void Motor_CorregirTrayectoria()
{
    Motor_Atras(iPorcentajeVelocidad);       // Movemos atras
    Espera(1000);
    
    Motor_Izquierda(iPorcentajeVelocidad);   // A la izquierda
    Espera(1000);
    
    Motor_Adelante(iPorcentajeVelocidad);    // Continuamos
}

//============================================================================
// MOVIMIENTO ALEATORIO??
//============================================================================
void Motor_Aleatorio()
{
    int iTiempoAleatorio=250;
    int iMovimientoAleatorio=250;
    
    Motor_Atras(iPorcentajeVelocidad);
    Espera(iTiempoAleatorio);
    Motor_Izquierda(iPorcentajeVelocidad);   // A la izquierda
    Espera(iTiempoAleatorio);
    Motor_Derecha(iPorcentajeVelocidad);   // A la izquierda
    Espera(iTiempoAleatorio);
    Motor_Parar();
}


//============================================================================
// MOVIMIENTO ABURRIDO: Giro a derecha e izquierda rapidamente un par de veces
//============================================================================
void Motor_Aburrido()
{
    Motor_Izquierda(iPorcentajeVelocidad);   // A la izquierda
    Espera(250);
    Motor_Derecha(iPorcentajeVelocidad);   // A la izquierda
    Espera(750);
    Motor_Izquierda(iPorcentajeVelocidad);   // A la izquierda
    Espera(750);
    Motor_Derecha(iPorcentajeVelocidad);   // A la izquierda
    Espera(750);
    Motor_Parar();
}


//============================================================================
// MOVIMIENTO SORPRESA: Tiro para atras un poco
//============================================================================
void Motor_Sorpresa()
{
      Motor_Atras(iPorcentajeVelocidad);       // Movemos atras
      Espera(500);
      Motor_Parar();
}

//====================================================================================================================
// MOVIMIENTO SUSTO: Tiro para atras un poco mas que con sorpresa
//====================================================================================================================
void Motor_Susto()
{
      Motor_Atras(iPorcentajeVelocidad);       // Movemos atras
      Espera(1000);
      Motor_Parar();
}

//====================================================================================================================
// MOVIMIENTO A CARGADOR: Me oriento hacia el cargador
// Deberiamos activar el sensor de infrarojos para obtener señar del receptor
// y encararnos asi a la estacion
//====================================================================================================================
void Motor_ACargador()
{
  // Activar sensor de infrarojos
}

//====================================================================================================================
// Establecemos el porcetaje de velocidad. Regulamos los Pines PWM de los motores. Podriamos incluso variar la 
// velocidad de cada uno de los motores por separado
//====================================================================================================================
void Motor_Velocidad(int Porcentaje)
{
	iPorcentajeVelocidad = Porcentaje; 
}
