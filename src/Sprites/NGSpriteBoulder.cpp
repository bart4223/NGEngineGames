//
//  NGSpriteBoulder.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 19.03.23.
//

#include "NGSpriteBoulder.h"

NGSpriteBoulder::NGSpriteBoulder(NGIPaintableComponent *ipc) {
    _create(ipc, false);
}

NGSpriteBoulder::NGSpriteBoulder(NGIPaintableComponent *ipc, bool transparent) {
    _create(ipc, transparent);
}

void NGSpriteBoulder::_create(NGIPaintableComponent *ipc, bool transparent) {
    NGCustomSprite::_create(ipc);
    _name = "Boulder";
    _width = 8;
    _height = 8;
    _background = COLOR_BLACK;
    _transparent = transparent;
}

void NGSpriteBoulder::_doRender(int x, int y) {
    _ipc->drawLine(x + 2, y, x + 5, y, COLOR_DARKGRAY);
    _ipc->drawLine(x, y + 2, x, y + 5, COLOR_DARKGRAY);
    _ipc->drawLine(x + 1, y + 1, x + 1, y + 2, COLOR_DARKGRAY);
    _ipc->drawLine(x + 6, y + 1, x + 6, y + 2, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 5, y + 2, COLOR_DARKGRAY);
    _ipc->drawLine(x + 3, y + 1, x + 4, y + 1, COLOR_DARKGRAY);
    _ipc->drawLine(x + 2, y + 3, x + 4, y + 3, COLOR_DARKGRAY);
    _ipc->drawLine(x + 1, y + 5, x + 4, y + 5, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 3, y + 4, COLOR_DARKGRAY);
    _ipc->drawLine(x + 6, y + 4, x + 6, y + 6, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 5, y + 6, COLOR_DARKGRAY);
    _ipc->drawLine(x + 1, y + 6, x + 2, y + 6, COLOR_DARKGRAY);
    _ipc->drawPoint(x + 2, y + 1, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 4, y + 2, COLOR_LIGHTGRAY);
    _ipc->drawLine(x + 5, y + 3, x + 5, y + 4, COLOR_LIGHTGRAY);
    _ipc->drawLine(x + 1, y + 3, x + 2, y + 4, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 4, y + 6, COLOR_LIGHTGRAY);
    _ipc->drawPoint(x + 5, y + 1, COLOR_BLACK);
    _ipc->drawLine(x + 2, y + 2, x + 3, y + 2, COLOR_BLACK);
    _ipc->drawPoint(x + 6, y + 3, COLOR_BLACK);
    _ipc->drawLine(x + 4, y + 4, x + 5, y + 5, COLOR_BLACK);
    _ipc->drawPoint(x + 5, y + 5, COLOR_BLACK);
    _ipc->drawPoint(x + 3, y + 6, COLOR_BLACK);
    _ipc->drawPoint(x + 1, y + 4, COLOR_BLACK);    
    _ipc->drawLine(x + 7, y + 2, x + 7, y + 5, COLOR_DARKGRAY);
    _ipc->drawLine(x + 2, y + 7, x + 5, y + 7, COLOR_DARKGRAY);
}
