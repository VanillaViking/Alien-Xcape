#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;

//bitmap encoded using the Bitmap Encoder which can be found here : http://gamebuino.com/wiki/index.php?title=Download
const byte pointerBitmap[] PROGMEM = {5, 5, 0x50, 0xF8, 0xA8, 0x70, 0x88,};
int move_array[5] = {7, 24, 41, 58, 75}; //Array for the positions of each lane
int lane = 2;

void setup() {
  gb.begin();
  gb.titleScreen(F("Bitmap example"));
}

void loop() {
  if (gb.update()) {
    //draw the pointer bitmap at coordinates x=0 and y=0 (top left corner)
    gb.display.drawBitmap(move_array[lane], 40, pointerBitmap);

    if (gb.buttons.pressed(BTN_RIGHT)) {
      if (lane < 4) {
        lane++;
      }
    }

    if (gb.buttons.pressed(BTN_LEFT)) {
      if (lane > 0) {
        lane--;
      }

    }

    //don't forget to allow the user to get back to the title screen when C is used :
    if (gb.buttons.pressed(BTN_C)) {
      gb.titleScreen(F("Bitmap example"));
    }
  }
}
