//
//  NGCustomSprite.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 14.03.23.
//

#include "NGCustomSprite.h"

void NGCustomSprite::_create(NGIPaintableComponent *ipc) {
    _ipc = ipc;
}

void NGCustomSprite::render(int x, int y) {
    setPosition(x, y);
    render();
}

void NGCustomSprite::render() {
    int scale = _ipc->getScale();
    colorRGB background = _ipc->getBackground();
    _ipc->beginUpdate();
    _ipc->setScale(_scale);
    _ipc->setBackground(_background);
    if (!_transparent) {
        _ipc->fillRect(_posY * scale, _posX * scale, _posY * scale + _height - 1, _posX * scale + _width - 1, _background);
    }
    _doRender(_posX * scale, _posY * scale);
    _ipc->endUpdate();
    _ipc->setBackground(background);
    _ipc->setScale(scale);
}

void NGCustomSprite::setPosition(int x, int y) {
    _posX = x;
    _posY = y;
    render();
}

void NGCustomSprite::setTransparent(bool transparent) {
    _transparent = transparent;
}

bool NGCustomSprite::getTransparent() {
    return _transparent;
}

char* NGCustomSprite::getName() {
    return _name;
}

void NGCustomSprite::setScale(int scale) {
    _scale = scale;
}

int NGCustomSprite::getScale() {
    return _scale;
}

int NGCustomSprite::getWidth() {
    return _width;
}

int NGCustomSprite::getHeight() {
    return _height;
}
