//
//  NGSpriteLaserbeam.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 26.03.23.
//

#include "NGSpriteLaserbeam.h"

NGSpriteLaserbeam::NGSpriteLaserbeam(NGIPaintableComponent *ipc) {
    _create(ipc, false);
}

NGSpriteLaserbeam::NGSpriteLaserbeam(NGIPaintableComponent *ipc, bool transparent) {
    _create(ipc, transparent);
}

void NGSpriteLaserbeam::_create(NGIPaintableComponent *ipc, bool transparent) {
    NGCustomSprite::_create(ipc);
    _name = "Laserbeam";
    _width = 8;
    _height = 8;
    _color = COLOR_RED;
    _background = COLOR_BLACK;
    _transparent = transparent;
}

void NGSpriteLaserbeam::_doRender(int x, int y) {
    for (int i = 1; i < 7; i++) {
        if (i == 1 || i == 3 || i == 4 || i ==6) {
            _ipc->drawLine(x, y + i, x + 1, y + i, _color);
            _ipc->drawLine(x + 3, y + i, x + 4, y + i, _color);
            _ipc->drawLine(x + 6, y + i, x + 7, y + i, _color);
        }
    }
}

