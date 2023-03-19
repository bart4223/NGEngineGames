//
//  NGCustomColorDotMatrixGame.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 12.03.23.
//

#include "NGGameExceptions.h"
#include "NGCustomColorDotMatrixGame.h"

bool NGCustomColorDotMatrixGame::_hasSprite(int id) {
    return _getSpriteIndex(id) != NOSPRITE;
}

int NGCustomColorDotMatrixGame::_getSpriteIndex(int id) {
    int res = NOSPRITE;
    for (int i = 0; i < _spriteCount; i++) {
        if (_sprites[i].id == id) {
            res = i;
            break;
        }
    }
    return res;
}

void NGCustomColorDotMatrixGame::_renderSprite(int id, int x, int y) {
    int i = _getSpriteIndex(id);
    if (i != NOSPRITE) {
        _sprites[i].sprite->setPosition(x, y);
        _sprites[i].sprite->render();
    }
}

void NGCustomColorDotMatrixGame::registerColorDotMatrix(NGIPaintableComponent *ipc) {
    _ipc = ipc;
    _score = new NGColorDotMatrixBinaryDigit(_ipc, _scoreDigits, _scoreDirection, _scoreDigitPosX, _scoreDigitPosY);
}

void NGCustomColorDotMatrixGame::registerSprite(byte id, NGCustomSprite *sprite) {
    if (_spriteCount < MAXSPRITECOUNT) {
        char log[100];
        gameSprite gs;
        gs.id = id;
        gs.sprite = sprite;
        _sprites[_spriteCount] = gs;
        _spriteCount++;
        sprintf(log, "Sprite \"%s\" registered", _sprites[_spriteCount - 1].sprite->getName());
        writeInfo(log);
    } else {
        _raiseException(ExceptionGameTooMuchSpriteCount);
    }
}

void NGCustomColorDotMatrixGame::registerScoreSprite(NGCustomSprite *sprite) {
    _score->registerPaintableObjectOn(sprite);
}
