//
//  NGSpriteSpaceship.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 28.03.23.
//

#include "NGSpriteSpaceship.h"

NGSpriteSpaceship::NGSpriteSpaceship(NGIPaintableComponent *ipc) {
    _create(ipc, false, 0, 0);
}

NGSpriteSpaceship::NGSpriteSpaceship(NGIPaintableComponent *ipc, bool transparent) {
    _create(ipc, transparent, 0, 0);
}

NGSpriteSpaceship::NGSpriteSpaceship(NGIPaintableComponent *ipc, bool transparent, int offsetX, int offsetY) {
    _create(ipc, transparent, offsetX, offsetY);
}

void NGSpriteSpaceship::_create(NGIPaintableComponent *ipc, bool transparent, int offsetX, int offsetY) {
    NGCustomSprite::_create(ipc);
    _name = "None";
    _width = 24;
    _height = 16;
    _color = COLOR_GREEN;
    _background = COLOR_BLACK;
    _transparent = transparent;
    _posOffsetX = offsetX;
    _posOffsetY = offsetY;
}

void NGSpriteSpaceship::_doRender(int x, int y) {
    _ipc->drawPoint(x + 11, y, _color);
    _ipc->drawPoint(x + 10, y + 1, _color);
    _ipc->drawPoint(x + 12, y + 1, _color);
    _ipc->drawPoint(x + 11, y + 1, COLOR_RED);
    _ipc->drawPoint(x + 11, y + 2, _color);
    _ipc->drawLine(x + 9, y + 3, x + 13, y + 3, _color);
    _ipc->drawLine(x + 7, y + 4, x + 15, y + 4, _color);
    _ipc->drawLine(x + 5, y + 5, x + 6, y + 5, _color);
    _ipc->drawLine(x + 7, y + 5, x + 15, y + 5, COLOR_LIGHTGRAY);
    _ipc->drawLine(x + 16, y + 5, x + 17, y + 5, _color);
    _ipc->drawLine(x + 3, y + 6, x + 4, y + 6, _color);
    _ipc->drawLine(x + 5, y + 6, x + 17, y + 6, COLOR_LIGHTGRAY);
    _ipc->drawLine(x + 18, y + 6, x + 19, y + 6, _color);
    _ipc->drawPoint(x + 2, y + 7, _color);
    _ipc->drawLine(x + 3, y + 7, x + 4, y + 7, COLOR_LIGHTGRAY);
    _ipc->drawLine(x + 5, y + 7, x + 7, y + 7, COLOR_YELLOW);
    _ipc->drawLine(x + 8, y + 7, x + 9, y + 7, COLOR_LIGHTGRAY);
    _ipc->drawLine(x + 10, y + 7, x + 12, y + 7, COLOR_YELLOW);
    _ipc->drawLine(x + 13, y + 7, x + 14, y + 7, COLOR_LIGHTGRAY);
    _ipc->drawLine(x + 15, y + 7, x + 17, y + 7, COLOR_YELLOW);
    _ipc->drawLine(x + 18, y + 7, x + 19, y + 7, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 20, y + 7, _color);
    _ipc->drawPoint(x + 1, y + 8, _color);
    _ipc->drawLine(x + 2, y + 8, x + 4, y + 8, COLOR_LIGHTGRAY);
    _ipc->drawLine(x + 5, y + 8, x + 7, y + 8, COLOR_YELLOW);
    _ipc->drawLine(x + 8, y + 8, x + 9, y + 8, COLOR_LIGHTGRAY);
    _ipc->drawLine(x + 10, y + 8, x + 12, y + 8, COLOR_YELLOW);
    _ipc->drawLine(x + 13, y + 8, x + 14, y + 8, COLOR_LIGHTGRAY);
    _ipc->drawLine(x + 15, y + 8, x + 17, y + 8, COLOR_YELLOW);
    _ipc->drawLine(x + 18, y + 8, x + 20, y + 8, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 21, y + 8, _color);
    _ipc->drawPoint(x + 1, y + 9, _color);
    _ipc->drawLine(x + 2, y + 9, x + 20, y + 9, COLOR_DARKGRAY);
    _ipc->drawLine(x + 21, y + 9, x + 23, y + 9, _color);
    _ipc->drawLine(x + 2, y + 10, x + 23, y + 10, _color);
    _ipc->drawLine(x + 2, y + 11, x + 20, y + 11, COLOR_LIGHTGRAY);
    _ipc->drawLine(x + 2, y + 12, x + 20, y + 12, _color);
    _ipc->drawLine(x + 3, y + 13, x + 5, y + 13, _color);
    _ipc->drawLine(x + 8, y + 13, x + 9, y + 13, _color);
    _ipc->drawLine(x + 13, y + 13, x + 14, y + 13, _color);
    _ipc->drawLine(x + 17, y + 13, x + 19, y + 13, _color);
    _ipc->drawLine(x + 2, y + 14, x + 4, y + 14, _color);
    _ipc->drawLine(x + 8, y + 14, x + 9, y + 14, _color);
    _ipc->drawLine(x + 13, y + 14, x + 14, y + 14, _color);
    _ipc->drawLine(x + 18, y + 14, x + 20, y + 14, _color);
    _ipc->drawLine(x + 1, y + 15, x + 3, y + 15, _color);
    _ipc->drawLine(x + 8, y + 15, x + 9, y + 15, _color);
    _ipc->drawLine(x + 13, y + 15, x + 14, y + 15, _color);
    _ipc->drawLine(x + 19, y + 15, x + 21, y + 15, _color);
}
