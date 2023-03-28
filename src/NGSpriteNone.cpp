//
//  NGSpriteNone.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 27.03.23.
//

#include "NGSpriteNone.h"

NGSpriteNone::NGSpriteNone(NGIPaintableComponent *ipc) {
    _create(ipc, true);
}

NGSpriteNone::NGSpriteNone(NGIPaintableComponent *ipc, bool transparent) {
    _create(ipc, transparent);
}

void NGSpriteNone::_create(NGIPaintableComponent *ipc, bool transparent) {
    NGCustomSprite::_create(ipc);
    _name = "None";
    _width = 8;
    _height = 8;
    _color = COLOR_BLACK;
    _background = COLOR_BLACK;
    _transparent = transparent;
}

void NGSpriteNone::_doRender(int x, int y) {
    
}
