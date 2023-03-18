//
//  NGSpriteDirt.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 14.03.23.
//

#include "NGSpriteDirt.h"

NGSpriteDirt::NGSpriteDirt(NGIPaintableComponent *ipc) {
    _create(ipc);
}

void NGSpriteDirt::_create(NGIPaintableComponent *ipc) {
    NGCustomSprite::_create(ipc);
    _name = "Dirt";
    _width = 8;
    _height = 8;
    _background = COLOR_BROWN;
}

void NGSpriteDirt::_doRender(int x, int y) {
    _ipc->drawPoint(x + 2, y, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 5, y, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 6, y, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 1, y + 1, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 2, y + 1, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 4, y + 1, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x, y + 2, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 2, y + 2, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 7, y + 2, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 1, y + 3, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 5, y + 3, COLOR_DARKGRAY);
    _ipc->drawPoint(x, y + 4, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 4, y + 4, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 5, y + 4, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 6, y + 4, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 1, y + 5, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 2, y + 5, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 5, y + 5, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 6, y + 5, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 2, y + 6, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 5, y + 6, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 3, y + 7, COLOR_LIGHTGRAY);
}
