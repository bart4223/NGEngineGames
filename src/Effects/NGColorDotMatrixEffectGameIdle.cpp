//
//  NGColorDotMatrixEffectGameIdle.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 01.10.26.
//

#include "NGColorDotMatrixEffectGameIdle.h"

NGColorDotMatrixEffectGameIdle::NGColorDotMatrixEffectGameIdle(NGIPaintableComponent *ipc, NGCustomGame *game) {
    _create(ipc, game, DEFIDLEEFFECTMODE);
}

void NGColorDotMatrixEffectGameIdle::_create(NGIPaintableComponent *ipc, NGCustomGame *game, gameIdleEffectMode mode) {
    _ipc = ipc;
    _game = game;
    _text = new NGColorDotMatrixText(_ipc);
    _mode = mode;
}

void NGColorDotMatrixEffectGameIdle::initialize() {
    _text->setColor(_textColor);
    _text->setColorBackground(_ipc->getBackground());
}

void NGColorDotMatrixEffectGameIdle::processingLoop() {
    _ipc->clear();
    _ipc->beginUpdate();
    int scaleOrg = _ipc->getScale();
    int scale;
    int len = strlen(_game->getName());
    int fact;
    switch(_mode) {
        case giemSimple:
            if (len > 5) {
                scale = 8;
                fact = 4;
            } else {
                scale = 16;
                fact = 2;
            }               
            _ipc->setScale(scale);
            _text->setPosX((_ipc->getWidth() - len) / fact - 1);
            _text->setPosY(_ipc->getHeight() + (scale / 2));
            _text->setText(_game->getName());
            _ipc->setScale(1);
            int x = _ipc->getWidth() / 8 - strlen(_textSecondary);
            _text->setPosX(x);
            _text->setPosY(_ipc->getHeight() - 10);
            _text->setText(_textSecondary);
            break;
    }
    _ipc->endUpdate();
    _ipc->setScale(scaleOrg);
}

void NGColorDotMatrixEffectGameIdle::setFont(NGCustomFont *font) {
    _text->setFont(font);
}

void NGColorDotMatrixEffectGameIdle::setTextSecondary(char* textsecondary) {
    _textSecondary = textsecondary;
}

void NGColorDotMatrixEffectGameIdle::setTextColor(colorRGB colortext) {
    _textColor = colortext;
}
