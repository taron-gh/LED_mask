byte smile[6][8] {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
};
#include <FastLED.h>
#define NUM_LEDS 48
#define DATA_PIN 3
CRGB leds[NUM_LEDS];
int smileStateUsable = 6;
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

}

void loop() {
  /*
  delay(1000);
  smileStateUsable++;
  if (smileStateUsable > 7) {
    smileStateUsable = 0;
  }
  */
  switch (smileStateUsable) {
    case 1:
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
          if (i == 2) {
            smile[i][j] = 1;
          } else {
            smile[i][j] = 0;
          }
        }
      }
      break;
    case 2:
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
          smile[i][j] = 0;
        }
      }
      
      for (int i = 0; i < 8; i++) {
        smile[2][i] = 1;
      }
      for (int i = 1; i < 7; i++) {
        smile[3][i] = 1;
      }
      
      break;
    case 3:
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
          smile[i][j] = 0;
        }
      }
      
      for (int i = 0; i < 8; i++) {
        smile[2][i] = 1;
      }
      for (int i = 1; i < 7; i++) {
        smile[4][i] = 1;
      }
      smile[3][0] = 1;
      smile[3][7] = 1;
      
      Serial.println("!!!!!");
      break;
    case 4:
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
          smile[i][j] = 0;
        }
      }
    
      for (int i = 1; i < 7; i++) {
        smile[1][i] = 1;
      }
      
      for (int i = 1; i < 7; i++) {
        smile[4][i] = 1;
      }
      
      smile[2][0] = 1;
      smile[2][7] = 1;
      smile[3][0] = 1;
      smile[3][7] = 1;
      
      break;
    case 5:
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
          smile[i][j] = 0;
        }
      }
      for (int i = 1; i < 7; i++) {
        smile[1][i] = 1;
      }
      for (int i = 1; i < 7; i++) {
        smile[5][i] = 1;
      }
      smile[2][0] = 1;
      smile[2][7] = 1;
      smile[3][0] = 1;
      smile[3][7] = 1;
      smile[4][0] = 1;
      smile[4][7] = 1;
      break;
    case 6:
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
          smile[i][j] = 0;
        }
      }
      for (int i = 1; i < 7; i++) {
        smile[0][i] = 1;
      }
      for (int i = 1; i < 7; i++) {
        smile[5][i] = 1;
      }
      smile[1][0] = 1;
      smile[1][7] = 1;
      smile[2][0] = 1;
      smile[2][7] = 1;
      smile[3][0] = 1;
      smile[3][7] = 1;
      smile[4][0] = 1;
      smile[4][7] = 1;
      break;
  }

  int counter = 0;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      if (smile[i][j] == 1) {
        leds[counter] = CRGB::Yellow;
      } else {
        leds[counter] = CRGB::Black;
      }
      counter++;
    }
    FastLED.show();
  }


}
