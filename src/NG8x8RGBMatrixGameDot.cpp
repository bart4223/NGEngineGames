//
//  NG8x8RGBMatrixGameDot.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.12.22.
//

#include "NG8x8RGBMatrixGameDot.h"

NG8x8RGBMatrixGameDot::NG8x8RGBMatrixGameDot() {
    _create("Dot");
    _scoreDigits = GAMEDOTSCOREDIGITS;
}

void NG8x8RGBMatrixGameDot::_rollPlayerColor() {
    _colorPlayer.red = random(0, 256);
    _colorPlayer.green = random(0, 256);
    _colorPlayer.blue = random(0, 256);
}

void NG8x8RGBMatrixGameDot::_calculateNewDotPosition() {
    bool ok = false;
    while (!ok) {
        if (_getYesOrNo()) {
            _posXDot = _posXDot - random(MINGAMEDOTDIFF, MAXGAMEDOTDIFF);
        } else {
            _posXDot = _posXDot + random(MINGAMEDOTDIFF, MAXGAMEDOTDIFF);
        }
        if (_getYesOrNo()) {
            _posYDot = _posYDot - random(MINGAMEDOTDIFF, MAXGAMEDOTDIFF);
        } else {
            _posYDot = _posYDot + random(MINGAMEDOTDIFF, MAXGAMEDOTDIFF);
        }
        _posXDot = _posXDot % (MAXGAMEDOTX + 1);
        _posYDot = _posYDot % (MAXGAMEDOTY + 1);
        ok = (_posXDot != _posXPlayer) && (_posYDot != _posYPlayer);
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Dot-X:%d Dot-Y:%d", _posXDot, _posYDot);
        writeInfo(log);
    }
    _dotSpawned = millis();
}

void NG8x8RGBMatrixGameDot::_doInitialize() {
    _score->setColorOff(GAMDEDOTCOLORSCOREOFF);
    _score->setColorOn(GAMDEDOTCOLORSCOREON);
    if (_logging) {
        char log[100];
        sprintf(log, "%s.Initialize", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameDot::_doStartGame() {
    _posXPlayer = 3;
    _posYPlayer = 4;
    _calculateNewDotPosition();
    _rollPlayerColor();
    _ownRender();
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameDot::_doFinishGame() {
    _cdm->clear();
    if (_logging) {
        char log[100];
        sprintf(log, "%s.FinishGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameDot::_doProcessingLoop() {
    if (_gameStarted) {
        _ownJoystickLoop();
        if (millis() - _dotSpawned > DOTMAXCATCHTIME) {
            if (_scoreCounter > 0) {
                _scoreCounter--;
            }
            _calculateNewDotPosition();
            _doRender = true;
        }
        if (_doRender) {
            _ownRender();
        }
    }
}

void NG8x8RGBMatrixGameDot::_ownRender() {
    _cdm->beginUpdate();
    _cdm->fillRect(0, 0, MAXGAMEDOTX, MAXGAMEDOTY, COLOR_BLACK);
    _cdm->drawPoint(_posXPlayer, _posYPlayer, _colorPlayer);
    _cdm->drawPoint(_posXDot, _posYDot, COLOR_RED);
    _score->setValue(_scoreCounter);
    _cdm->endUpdate();
}

void NG8x8RGBMatrixGameDot::_ownJoystickLoop() {
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
                    if (_posYPlayer < MAXGAMEDOTY) {
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
                    if (_posXPlayer < MAXGAMEDOTX) {
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
        _cdm->drawPoint(_posXDot, _posYDot, COLOR_GREEN);
        delay(DOTCATCHDELAY);
        _calculateNewDotPosition();
    }
}
