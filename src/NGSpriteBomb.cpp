//
//  NGSpriteBomb.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 19.03.23.
//

#include "NGSpriteBomb.h"

NGSpriteBomb::NGSpriteBomb(NGIPaintableComponent *ipc) {
    _create(ipc, false);
}

NGSpriteBomb::NGSpriteBomb(NGIPaintableComponent *ipc, bool transparent) {
    _create(ipc, transparent);
}

void NGSpriteBomb::_create(NGIPaintableComponent *ipc, bool transparent) {
    NGCustomSprite::_create(ipc);
    _name = "Bomb";
    _width = 8;
    _height = 8;
    _background = COLOR_BLACK;
    _transparent = transparent;
}

void NGSpriteBomb::_doRender(int x, int y) {
    _ipc->drawLine(x + 2, y + 1, x + 4, y + 1, COLOR_RED);
    _ipc->drawLine(x + 1, y + 2, x + 5, y + 2, COLOR_RED);
    _ipc->drawLine(x + 6, y + 1, x + 7, y, COLOR_RED);
    _ipc->drawLine(x, y + 3, x + 6, y + 3, COLOR_RED);
    _ipc->drawLine(x, y + 4, x + 3, y + 4, COLOR_RED);
    _ipc->drawLine(x, y + 5, x + 2, y + 5, COLOR_RED);
    _ipc->drawLine(x + 1, y + 6, x + 2, y + 6, COLOR_RED);
    _ipc->drawLine(x + 2, y + 7, x + 4, y + 7, COLOR_RED);
    _ipc->drawPoint(x + 6, y + 4, COLOR_RED);
    _ipc->drawLine(x + 5, y + 5, x + 6, y + 5, COLOR_RED);
    _ipc->drawLine(x + 4, y + 6, x + 5, y + 6, COLOR_RED);
    _ipc->drawLine(x + 4, y + 4, x + 5, y + 4, COLOR_WHITE);
    _ipc->drawLine(x + 3, y + 5, x + 4, y + 5, COLOR_WHITE);
    _ipc->drawPoint(x + 3, y + 6, COLOR_WHITE);
}
