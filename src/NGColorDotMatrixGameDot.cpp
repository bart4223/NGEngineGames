//
//  NGColorDotMatrixGameDot.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.12.22.
//

#include "NGColorDotMatrixGameDot.h"

NGColorDotMatrixGameDot::NGColorDotMatrixGameDot() {
    _create("Dot");
}

void NGColorDotMatrixGameDot::_rollPlayerColor() {
    _colorPlayer.red = random(0, 256);
    _colorPlayer.green = random(0, 256);
    _colorPlayer.blue = random(0, 256);
}

void NGColorDotMatrixGameDot::_calculateNewDotPosition() {
    bool ok = false;
    while (!ok) {
        if (_getYesOrNo()) {
            _posXDot = _posXDot - random(_minGameDotDiff, _maxGameDotDiff);
        } else {
            _posXDot = _posXDot + random(_minGameDotDiff, _maxGameDotDiff);
        }
        if (_getYesOrNo()) {
            _posYDot = _posYDot - random(_minGameDotDiff, _maxGameDotDiff);
        } else {
            _posYDot = _posYDot + random(_minGameDotDiff, _maxGameDotDiff);
        }
        _posXDot = _posXDot % (_maxGameDotX + 1);
        _posYDot = _posYDot % (_maxGameDotY + 1);
        ok = (_posXDot != _posXPlayer) && (_posYDot != _posYPlayer);
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Dot-X:%d Dot-Y:%d", _posXDot, _posYDot);
        writeInfo(log);
    }
    _dotSpawned = millis();
}

void NGColorDotMatrixGameDot::_doInitialize() {
    _score->setColorOff(GAMEDOTCOLORSCOREOFF);
    _score->setColorOn(GAMEDOTCOLORSCOREON);
    if (_logging) {
        char log[100];
        sprintf(log, "%s Initialize...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameDot::_doStartUp() {
    if (!_inStartUpAnimation) {
        if (_logging) {
            char log[100];
            sprintf(log, "%s StartUp...", _name);
            writeInfo(log);
        }
        _ownIntro();
        _inStartUpAnimation = true;
        _startUpAnimationStep = 0;
    } else {
        _ownIntroAnimation();
    }
}

void NGColorDotMatrixGameDot::_doStartUpDone() {
    _ipc->clear();
    _score->setValue(0);
    if (_logging) {
        char log[100];
        sprintf(log, "%s StartUp Done", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameDot::_doStartGame() {
    _posXPlayer = _maxGameDotX / 2;
    _posYPlayer = _maxGameDotY / 2 + 1;
    _calculateNewDotPosition();
    _rollPlayerColor();
    _ownRender();
    if (_logging) {
        char log[100];
        sprintf(log, "%s Start...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameDot::_doBreakGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s Break...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameDot::_doContinueGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s Continue...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameDot::_doFinishGame() {
    _ipc->clear();
    if (_logging) {
        char log[100];
        sprintf(log, "%s Finish...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameDot::_doProcessingLoop() {
    if (_gameStarted) {
        _ownJoystickLoop();
        if (millis() - _dotSpawned > _dotMaxCatchTime) {
            if (_scoreCounter > 0) {
                _scoreCounter--;
            }
            _calculateNewDotPosition();
            _doRender = true;
        }
        if (_doRender) {
            _ownRender();
        } else if (_hasSprite(GAMESPRITEPLAYERID)) {
            _renderSprite(GAMESPRITEPLAYERID, _posXPlayer, _posYPlayer);
        }
    }
}

void NGColorDotMatrixGameDot::_ownIntro() {
    _ipc->clear();
    byte dotX = random(5, _maxGameDotX - 5);
    byte dotY = random(5, _maxGameDotY - 5);
    if (_hasSprite(GAMESPRITEDOTID)) {
        _setSpriteColor(GAMESPRITEDOTID, COLOR_RED);
        _renderSprite(GAMESPRITEDOTID, dotX, dotY);
    } else {
        _ipc->drawPoint(dotX, dotY, COLOR_RED);
    }
    _rollPlayerColor();
    _ipc->drawPoint(_introPlayerX, _introPlayerY, COLOR_BLACK);
}

void NGColorDotMatrixGameDot::_ownIntroAnimation() {
    _startUpDone = _startUpAnimationStep > _maxGameDotX / 2 + _maxGameDotY / 2;
    if (!_startUpDone) {
        if (millis() - _lastStartUpAnimationStep > GAMEDOTINTRODELAY) {
            _ipc->drawPoint(_introPlayerX, _introPlayerY, COLOR_BLACK);
            if (_getYesOrNo()) {
                _introPlayerX++;
            } else {
                _introPlayerY++;
            }
            if (_hasSprite(GAMESPRITEPLAYERID)) {
                _renderSprite(GAMESPRITEPLAYERID, _introPlayerX, _introPlayerY);
            } else {
                _ipc->drawPoint(_introPlayerX, _introPlayerY, _colorPlayer);
            }
            _startUpAnimationStep++;
            _lastStartUpAnimationStep = millis();
        }
    }
}

void NGColorDotMatrixGameDot::_ownRender() {
    _ipc->beginUpdate();
    _ipc->clear();
    if (_hasSprite(GAMESPRITEPLAYERID)) {
        _setSpriteColor(GAMESPRITEPLAYERID, _colorPlayer);
        _renderSprite(GAMESPRITEPLAYERID, _posXPlayer, _posYPlayer);
    } else {
        _ipc->drawPoint(_posXPlayer, _posYPlayer, _colorPlayer);
    }
    if (_hasSprite(GAMESPRITEDOTID)) {
        _setSpriteColor(GAMESPRITEDOTID, COLOR_RED);
        _renderSprite(GAMESPRITEDOTID, _posXDot, _posYDot);
    } else {
        _ipc->drawPoint(_posXDot, _posYDot, COLOR_RED);
    }
    _score->setValue(_scoreCounter);
    _ipc->endUpdate();
}

void NGColorDotMatrixGameDot::_ownJoystickLoop() {
    _doRender = false;
    for (int i = 0; i < _joystickCount; i++) {
        if (_joysticks[i].joystick->hasLastMovement()) {
            switch(_joysticks[i].joystick->getLastMovement()) {
                case jmUp:
                    if (_posYPlayer > 0) {
                        _posYPlayer--;
                        _doRender = true;
                    }
                    break;
                case jmDown:
                    if (_posYPlayer < _maxGameDotY) {
                        _posYPlayer++;
                        _doRender = true;
                    }
                    break;
                case jmLeft:
                    if (_posXPlayer > 0) {
                        _posXPlayer--;
                        _doRender = true;
                    }
                    break;
                case jmRight:
                    if (_posXPlayer < _maxGameDotX) {
                        _posXPlayer++;
                        _doRender = true;
                    }
                    break;
                case jmFire:
                    _rollPlayerColor();
                    _doRender = true;
                    break;
            }
        }
    }
    if ((_posXPlayer == _posXDot) && (_posYPlayer == _posYDot)) {
        _scoreCounter++;
        _score->setValue(_scoreCounter);
        if (_hasSprite(GAMESPRITEDOTID)) {
            _setSpriteColor(GAMESPRITEDOTID, COLOR_GREEN);
            _renderSprite(GAMESPRITEDOTID, _posXDot, _posYDot);
        } else {
            _ipc->drawPoint(_posXDot, _posYDot, COLOR_GREEN);
        }
        delay(DOTCATCHDELAY);
        _calculateNewDotPosition();
    }
}

void NGColorDotMatrixGameDot::registerColorDotMatrix(NGIPaintableComponent *ipc) {
    _scoreDigitPosX = ipc->getWidth() - 1;
    _scoreDigitPosY = ipc->getHeight() - 1;
    _scoreDigits = ipc->getHeight();
    _dotMaxCatchTime = DEFDOTMAXCATCHTIME + ((ipc->getWidth() - DEFSCOREDIGITPOSX) * (ipc->getHeight() - DEFSCOREDIGITPOSY) * ((DEFSCOREDIGITPOSX + 1) * (DEFSCOREDIGITPOSY + 1) / DEFDOTMAXCATCHTIME));
    switch(_gameMode) {
        case gmNormal:
            _dotMaxCatchTime = _dotMaxCatchTime * 1.5;
            break;
        case gmBig:
            _dotMaxCatchTime = _dotMaxCatchTime * 2;
            break;
    }
    NGCustomColorDotMatrixGame::registerColorDotMatrix(ipc);
    _maxGameDotX = ipc->getWidth() - 2;
    _maxGameDotY = ipc->getHeight() - 1;
    _minGameDotDiff = 1;
    _maxGameDotDiff = (ipc->getWidth() / 2 + ipc->getHeight() / 2) / 2;
}
