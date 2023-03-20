//
//  NGSpriteDot.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 20.03.23.
//

#include "NGSpriteDot.h"

NGSpriteDot::NGSpriteDot(NGIPaintableComponent *ipc) {
    _create(ipc, false);
}

NGSpriteDot::NGSpriteDot(NGIPaintableComponent *ipc, bool transparent) {
    _create(ipc, transparent);
}

void NGSpriteDot::_create(NGIPaintableComponent *ipc, bool transparent) {
    NGCustomSprite::_create(ipc);
    _name = "Dot";
    _width = 8;
    _height = 8;
    _color = COLR_RED;
    _background = COLOR_BLACK;
    _transparent = transparent;
}

void NGSpriteDot::_doRender(int x, int y) {
    _ipc->drawLine(x + 2, y, x + 5, y, _color);
    _ipc->drawLine(x + 1, y + 1, x + 6, y + 1, _color);
    for (int i = 2; i < 6; i++) {
        _ipc->drawLine(x, y + i, x + 7, y + i, _color);
    }
    _ipc->drawLine(x + 1, y + 6, x + 6, y + 6, _color);
    _ipc->drawLine(x + 2, y + 7, x + 5, y + 7, _color);
}
