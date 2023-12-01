#include <gl2d.h>

#include "generated/textures_32.h"
#include "christmasTree.h"

#define MAX_X 255
#define MID_X (255 / 2)
#define MAX_Y 191

void ChristmasTree::init() {
    glLoadTileSet(textures_32, 32, 32, 128, 32, GL_RGB256,
                  TEXTURE_SIZE_128, TEXTURE_SIZE_32, TEXGEN_OFF|GL_TEXTURE_COLOR0_TRANSPARENT,
                  256, (u16*)textures_32Pal, (u8*)textures_32Bitmap);
}

void ChristmasTree::render(int day){
    int height = 70;

    glBoxFilled(MID_X - 10, MAX_Y + 1, MID_X + 10, MAX_Y - 40, RGB15(5, 3, 0));
    glTriangleFilledGradient(MID_X - 75, MAX_Y - 30,
                             MID_X + 75, MAX_Y - 30,
                             MID_X, MAX_Y - 30 - height,
                             RGB15(0, 3, 1),
                             RGB15(0, 3, 1),
                             RGB15(0, 7, 2));

    glTriangleFilledGradient(MID_X - 60, MAX_Y - 70,
                             MID_X + 60, MAX_Y - 70,
                             MID_X, MAX_Y - 70 - height,
                             RGB15(0, 3, 1),
                             RGB15(0, 3, 1),
                             RGB15(0, 7, 2));

    glTriangleFilledGradient(MID_X - 40, MAX_Y - 110,
                             MID_X + 40, MAX_Y - 110,
                             MID_X, MAX_Y - 110 - height + 30,
                             RGB15(0, 3, 1),
                             RGB15(0, 3, 1),
                             RGB15(0, 7, 2));

    size_t total = 0;
    if (total == day){
        return;
    }

    glSprite(star[0], star[1], GL_FLIP_NONE, &textures_32[0]);
    total += 1;
    if (total == day){
        return;
    }
}
