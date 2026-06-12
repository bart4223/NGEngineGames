//
//  NGSpriteDiamond.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.03.23.
//

#include "NGSpriteDiamond.h"

NGSpriteDiamond::NGSpriteDiamond(NGIPaintableComponent *ipc) {
    _create(ipc, false);
}

NGSpriteDiamond::NGSpriteDiamond(NGIPaintableComponent *ipc, bool transparent) {
    _create(ipc, transparent);
}

void NGSpriteDiamond::_create(NGIPaintableComponent *ipc, bool transparent) {
    NGCustomSprite::_create(ipc);
    _name = "Diamond";
    _width = 8;
    _height = 8;
    _background = COLOR_BLACK;
    _transparent = transparent;
}

void NGSpriteDiamond::_doRender(int x, int y) {
    _ipc->drawLine(x + 3, y, x + 4, y, COLOR_TEAL);
    if (!_blink) {
        _ipc->drawPoint(x + 2, y + 1, COLOR_TEAL);
        _ipc->drawPoint(x + 5, y + 1, COLOR_TEAL);
        _ipc->drawLine(x + 3, y + 1, x + 4, y + 1, COLOR_YELLOW);
        for (int i = 3; i < 5; i++) {
            _ipc->drawLine(x + 1, y + i, x + 6, y + i, COLOR_YELLOW);
            _ipc->drawPoint(x, y + i, COLOR_TEAL);
            _ipc->drawPoint(x + 7, y + i, COLOR_TEAL);
        }
        _ipc->drawPoint(x + 2, y + 6, COLOR_TEAL);
        _ipc->drawPoint(x + 5, y + 6, COLOR_TEAL);
        _ipc->drawLine(x + 3, y + 6, x + 4, y + 6, COLOR_YELLOW);
    } else {
        _ipc->drawLine(x + 2, y + 1, x + 5, y + 1, COLOR_TEAL);
        for (int i = 3; i < 5; i++) {
            _ipc->drawLine(x, y + i, x + 7, y + i, COLOR_TEAL);
        }
        _ipc->drawLine(x + 2, y + 6, x + 5, y + 6, COLOR_TEAL);
    }
    if (millis() - _lastBlink > BLINKDELAY) {
        _blink = !_blink;
        _lastBlink = millis();
    }
    _ipc->drawLine(x + 1, y + 2, x + 6, y + 2, COLOR_TEAL);
    _ipc->drawLine(x + 1, y + 5, x + 6, y + 5, COLOR_TEAL);
    _ipc->drawLine(x + 3, y + 7, x + 4, y + 7, COLOR_TEAL);
}
