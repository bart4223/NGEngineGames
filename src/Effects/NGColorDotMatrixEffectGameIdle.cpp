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
    switch(_mode) {
        case giemSimple:
            scale = 16;
            _ipc->setScale(scale);
            _text->setPosX((_ipc->getWidth() - strlen(_game->getName())) / 2 - 1);
            _text->setPosY(_ipc->getHeight() + (scale / 2));
            _text->setText(_game->getName());
            _ipc->setScale(1);
            int x = _ipc->getWidth() / (scale / 2) - strlen(_textSecondary);
            _text->setPosX(x);
            _text->setPosY(_ipc->getHeight() - (scale / 2) - 2);
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
