//
//  NGSpriteHeart.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 15.03.23.
//

#include "NGSpriteHeart.h"

NGSpriteHeart::NGSpriteHeart(NGIPaintableComponent *ipc) {
    _create(ipc, false);
}

NGSpriteHeart::NGSpriteHeart(NGIPaintableComponent *ipc, bool transparent) {
    _create(ipc, transparent);
}

void NGSpriteHeart::_create(NGIPaintableComponent *ipc, bool transparent) {
    NGCustomSprite::_create(ipc);
    _name = "Heart";
    _width = 8;
    _height = 8;
    _background = COLOR_BLACK;
    _transparent = transparent;
}

void NGSpriteHeart::_doRender(int x, int y) {
    _ipc->drawLine(x + 1, y + 1, x + 2, y + 1, COLOR_RED);
    _ipc->drawLine(x + 5, y + 1, x + 6, y + 1, COLOR_RED);
    for (int i = 2; i < 5; i++) {
        _ipc->drawLine(x, y + i, x + 7, y + i, COLOR_RED);
    }
    _ipc->drawLine(x + 1, y + 5, x + 6, y + 5, COLOR_RED);
    _ipc->drawLine(x + 2, y + 6, x + 5, y + 6, COLOR_RED);
    _ipc->drawLine(x + 3, y + 7, x + 4, y + 7, COLOR_RED);
}
