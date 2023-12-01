#include "graphics.h"
#include "generated/background_night.h"
#include "generated/textures_32.h"

#include <iostream>

void Graphics::init(){
    videoSetMode(MODE_5_3D);

    glScreen2D();
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankF(VRAM_F_TEX_PALETTE);

    glLoadTileSet(background, 256, 256, 256, 256, GL_RGB256,
                  TEXTURE_SIZE_256, TEXTURE_SIZE_256, TEXGEN_OFF,
                  256, (u16*) background_nightPal, (uint8*) background_nightBitmap);

    tree.init();
}

void Graphics::update(int day){
    snow.update(1);

    glBegin2D();
    glSprite(0, 0, 0, background);
    tree.render(day);
    snow.render();

    glEnd2D();
    glFlush(0);
}
