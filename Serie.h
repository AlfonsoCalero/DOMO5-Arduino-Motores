//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%																												%%
//%%																												%%
//%%																												%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%																												%%
//%%																												%%
//%%																												%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//====================================================================================================================
//====================================================================================================================
void Serie_Envia(char Parametro, String Texto)
{
  Serial.print(Parametro);
  Serial.print(F(":"));
  Serial.print(Texto);
  Serial.println(F("#"));
}

//====================================================================================================================
// INICIALIZACION
//====================================================================================================================
void Serie_Inicializa()
{
   Serial.begin(9600);
   Serie_Envia('0',"serie");
   //Serial.println(F("Puerto serie inicializado a 9600 bps"));
}
