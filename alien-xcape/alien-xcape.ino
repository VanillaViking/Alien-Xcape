#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;

//bitmap encoded using the Bitmap Encoder which can be found here : http://gamebuino.com/wiki/index.php?title=Download
const byte player[] PROGMEM = {5, 5, 0x50, 0xF8, 0xA8, 0x70, 0x88,};
const byte enemy[] PROGMEM = {7, 6, 0x38, 0x7C, 0x92, 0xFE, 0x7C, 0x28};
int move_array[5] = {7, 24, 41, 58, 75}; //Array for the positions of each lane
int lane = 2;

int enemy_x = 2;
int enemy_y = 0;
int enemy_vely = 3;

void setup() {
  gb.begin();
  gb.titleScreen(F("Bitmap example"));
}

void loop() {
  if (gb.update()) {
    //draw the pointer bitmap at coordinates x=0 and y=0 (top left corner)
    gb.display.drawBitmap(move_array[lane], 40, player);
    gb.display.drawBitmap(move_array[enemy_x], enemy_y, enemy);

    if (enemy_y > 64) {
      enemy_y = 0;
      enemy_x = random(0, 5);
    }
    else {
      enemy_y = enemy_y + enemy_vely;
    }
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
    if (gb.collideRectRect(move_array[lane], 40, 5, 5, move_array[enemy_x], enemy_y, 7, 6)) {
      gb.display.clear();
      gb.titleScreen(F("you dieded lol"));
      enemy_x = 0;
    }

    //don't forget to allow the user to get back to the title screen when C is used :
    if (gb.buttons.pressed(BTN_C)) {
      gb.titleScreen(F("Bitmap example"));
    }
  }
}
