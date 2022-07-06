#include <FastLED.h>
#define NUM_LEDS 48
#define DATA_PIN 3
CRGB leds[NUM_LEDS];
float signalMax = 0;
float signalMin = 1023;
float thisSignal;
float maxCoff = 0.997;
float minCoff = 1.007;
float signalValue = 0.1;
byte smileState = 1; // 1 - 8 - mouth 1 - 8; 20 - smile, 30 - sad smile
byte smileStateUsable = 0;
byte signalValueUsable = 0;
byte counter2 = 0;
long emojiTimer = 0;
bool emojiFlag = true;
long silentSmileTimer = 0;
//bool silentSmileState = false; // true - silent, false - talking
byte smile[6][8] {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
};
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

}

void loop() {
  thisSignal = analogRead(A1);
  if (thisSignal > signalMax) {
    signalMax = thisSignal;
  }
  if (thisSignal < signalMin) {
    signalMin = thisSignal;
  }

  if ((thisSignal + 7) < signalMax) {
    signalMax *= maxCoff;
    maxCoff -= 0.00005;
  }
  if ((thisSignal - 7) > signalMin) {
    signalMin *= minCoff;
    minCoff += 0.00005;
  }

  signalValue = signalMax - signalMin;
  //Serial.println(signalMax);
  //Serial.println(signalMax);
  //Serial.println(signalMax);
  smileState = constrain(map(signalValue, 0, 46, 1, 6), 1, 6);
  if (round(millis() / 150) % 2) {
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
      if (counter2 == 4) {
        if (smileState > smileStateUsable) {
          smileStateUsable++;
        } else if (smileState < smileStateUsable) {
          smileStateUsable--;
        }
        counter2 = 0;
      }

      counter2++;
      FastLED.show();
    }
  }
  //Serial.println(smileStateUsable);
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
  if (millis() - silentSmileTimer < 1500 && smileStateUsable == 1) {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 8; j++) {
        smile[i][j] = 0;
      }
    }
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 8; j++) {
        if (i == 2) {
          smile[i][j] = 1;
        } else {
          smile[i][j] = 0;
        }
      }

    }


  }
  else if (millis() - silentSmileTimer > 1500 && smileStateUsable == 1) {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 8; j++) {
        smile[i][j] = 0;
      }
    }
  } else if (smileStateUsable != 1) {
    silentSmileTimer = millis();
  }

  /*
    if(emojiFlag == true && signalValue > 200){
    emojiTimer = millis();
    }
    if(emojiFlag == false && signalValue > 200 && millis() - emojiTimer < 2000){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
          smile[i][j] = 0;
        }
    }
    smile[1][0] = 1;
    smile[1][7] = 1;
    smile[2][0] = 1;
    smile[2][7] = 1;
    smile[3][1] = 1;
    smile[3][6] = 1;
    smile[4][2] = 1;
    smile[4][3] = 1;
    smile[4][4] = 1;
    smile[4][5] = 1;
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
    if(emojiFlag == false && signalValue > 200 && millis() - emojiTimer > 2000){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
          smile[i][j] = 0;
        }
    }
    smile[1][2] = 1;
    smile[1][3] = 1;
    smile[1][4] = 1;
    smile[1][5] = 1;
    smile[2][1] = 1;
    smile[2][6] = 1;
    smile[3][0] = 1;
    smile[3][7] = 1;
    smile[4][0] = 1;
    smile[4][7] = 1;
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
  */
  if (round(millis() / 350) % 2) {
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
}
