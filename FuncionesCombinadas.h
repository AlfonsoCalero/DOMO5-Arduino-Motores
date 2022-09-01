//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%																												%%
//%%																												%%
//%%																												%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%																												%%
//%%																												%%
//%%																												%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

bool bContando=false;
unsigned long TiempoKITT=0;

//====================================================================================================================
// FUNCION "SIGUEME"
// Obtenemos la distancia al objeto que tenemos delante e intentamos 
// mantener esa distancia hasta que el objeto que tenemos delante se vaya de rango
// o nos den la orden de "DEJA DE SEGUIRME" o "PARA"
//====================================================================================================================
void Motor_Sigueme()
{

  cFuncion ='s';
  
  // Obtenemos la distancia actual
  int cm = Distancia_DevuelveDistanciaFrontal();

  if (cm>50)
  {
    //---------------------------------------------------------------------
    // Donde estas?
    //---------------------------------------------------------------------
       Serie_Envia('S',"error");      // Devolvemos: funcion sigueme "S", "error"
       Serial.print(F("¿Donde estas? Detecto objeto a "));
       Serial.print(cm);
       Serial.println(F(" cm."));
       cFuncion=(char) 0; // Reseteamos la variable 
  }
  else
  {
    //---------------------------------------------------------------------
    // Si la distancia es de < 50 cm hemos capturado el objeto
    //---------------------------------------------------------------------
    // el rango sera de +-10cm, fuera de ese rango dejamos de seguir

  
  }
}

void Efecto_KITT()
{
  // si me estoy moviendo
  if (iDireccion!=DireccionParo)
  {
    if (!bContando)
    {
      // y han pasado 5 segundos desde el ultimo 
      Leds_KnightRider();
      // Empezamos el conteo del siguiente
      bContando=true;
      TiempoKITT=tAhora;
    }
    else
    {
        // y han pasado 5 segundos desde el ultimo 
       if( tAhora - TiempoKITT > 5000 )
     {
        Leds_KnightRider();
        TiempoKITT = tAhora;
     }   
    }
  }
}
