#include <FastLED.h>

#define NUM_LEDS    14
#define LED_PIN     12

CRGB leds[NUM_LEDS];


//====================================================================================================================
//====================================================================================================================
void Leds_Sensor(CRGB color, int led1, int led2)
{
  leds[led1] = color;
  leds[led2] = color;
  FastLED.show();
}

//====================================================================================================================
//====================================================================================================================
void Leds_Sensor_Apaga(int led1, int led2)
{
  leds[led1] = CRGB::Black;
  leds[led2] = CRGB::Black;
  FastLED.show();
}

//====================================================================================================================
//====================================================================================================================
void Leds_ApagaTodos() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

//====================================================================================================================
//====================================================================================================================
void Leds_Set()
{
  LEDS.addLeds<WS2812B,LED_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(84);
}

//====================================================================================================================
//====================================================================================================================
void Leds_Efecto1(int NumeroVeces)
{
  Leds_Set();
  
  for(int k = 0; k < NumeroVeces; k++) {
  
    static uint8_t hue = 0;
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    Leds_ApagaTodos();
    // Wait a little bit before we loop around and do it again
    delay(20);
  }

  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
     leds[i] = CRGB::Black;
    Leds_ApagaTodos();
    // Wait a little bit before we loop around and do it again
    delay(20);
   }
  }
  Leds_ApagaTodos();
  FastLED.show(); 
}

//====================================================================================================================
//====================================================================================================================
void Leds_KnightRider()
{
    // Envia que inicia por si queremos lanzar el sonido
    Serie_Envia('9',"");
  
    for(int dot = 4;dot <= 9; dot++)
    { 
    leds[dot] = CRGB::Green;
    FastLED.show();
    Espera(60);
    leds[dot] = CRGB::Black;
    }
    Espera(60);

    for(int dot=9 ; dot >=4 ; dot--)
    {
    leds[dot] = CRGB::Green;
    FastLED.show();
    Espera(60);
    leds[dot] = CRGB::Black;
    }
    FastLED.show();
}

//====================================================================================================================
// INICIALIZACION
//====================================================================================================================
void Leds_Inicializa()
{
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS);
    Leds_Efecto1(5);
}
