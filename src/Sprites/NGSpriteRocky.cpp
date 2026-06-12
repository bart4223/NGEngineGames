//
//  NGSpriteRocky.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.03.23.
//

#include "NGSpriteRocky.h"

NGSpriteRocky::NGSpriteRocky(NGIPaintableComponent *ipc) {
    _create(ipc, false);
}

NGSpriteRocky::NGSpriteRocky(NGIPaintableComponent *ipc, bool transparent) {
    _create(ipc, transparent);
}

void NGSpriteRocky::_create(NGIPaintableComponent *ipc, bool transparent) {
    NGCustomSprite::_create(ipc);
    _name = "Rocky";
    _width = 8;
    _height = 8;
    _color = COLOR_BLUE;
    _background = COLOR_BLACK;
    _transparent = transparent;
}

void NGSpriteRocky::_doRender(int x, int y) {
    _ipc->drawLine(x + 1, y, x + 6, y, _color);
    if (!_blink) {
        _ipc->drawPoint(x, y + 1, _color);
        _ipc->drawPoint(x + 7, y + 1, _color);
        _ipc->drawLine(x + 3, y + 1, x + 4, y + 1, _color);
        _ipc->drawLine(x + 1, y + 1, x + 2, y + 1, COLOR_YELLOW);
        _ipc->drawLine(x + 5, y + 1, x + 6, y + 1, COLOR_YELLOW);
    } else {
        _ipc->drawLine(x, y + 1, x + 7, y + 1, _color);
    }
    if (millis() - _lastBlink > BLINKDELAY) {
        _blink = !_blink;
        _lastBlink = millis();
    }
    _ipc->drawLine(x + 1, y + 2, x + 6, y + 2, _color);
    for (int i = 4; i < 6; i++) {
        _ipc->drawLine(x + 1, y + i, x + 6, y + i, _color);
    }
    _ipc->drawLine(x + 3, y + 3, x + 4, y + 3, _color);
    _ipc->drawPoint(x + 2, y + 6, _color);
    _ipc->drawPoint(x + 5, y + 6, _color);
    _ipc->drawLine(x + 1, y + 7, x + 2, y + 7, _color);
    _ipc->drawLine(x + 5, y + 7, x + 6, y + 7, _color);
}
