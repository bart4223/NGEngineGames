//
//  NG8x8RGBMatrixGameDot.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.12.22.
//

#include "NG8x8RGBMatrixGameDot.h"

NG8x8RGBMatrixGameDot::NG8x8RGBMatrixGameDot() {
    _create("Dot");
}

void NG8x8RGBMatrixGameDot::_doInitialize() {
    if (_logging) {
        writeInfo("Dot.Initialize");
    }
}

void NG8x8RGBMatrixGameDot::_doStartGame() {
    _posX = random(0, 8);
    _posY = random(0, 8);
    _ownRender();
    if (_logging) {
        writeInfo("Dot.StartGame");
    }
}

void NG8x8RGBMatrixGameDot::_doFinishGame() {
    if (_logging) {
        writeInfo("Dot.FinishGame");
    }
}

void NG8x8RGBMatrixGameDot::_doProcessingLoop() {
    if (_gameStarted) {
        _ownJoystickLoop();
        if (_posChanged) {
            _ownRender();
        }
    }
}

void NG8x8RGBMatrixGameDot::_ownRender() {
    _cdm->beginUpdate();
    _cdm->clear();
    _cdm->drawPoint(_posX, _posY, COLOR_GREEN);
    _cdm->endUpdate();
}

void NG8x8RGBMatrixGameDot::_ownJoystickLoop() {
    _posChanged = false;
    for (int i = 0; i < _joystickCount; i++) {
        if (_joysticks[i].joystick->hasLastMovement()) {
            switch(_joysticks[i].joystick->getLastMovement()) {
                case jmUp:
                    if (_posY > 0) {
                        _posY--;
                        _posChanged = true;
                    }
                    break;
                case jmDown:
                    if (_posY < 7) {
                        _posY++;
                        _posChanged = true;
                    }
                    break;
                case jmLeft:
                    if (_posX > 0) {
                        _posX--;
                        _posChanged = true;
                    }
                    break;
                case jmRight:
                    if (_posX < 7) {
                        _posX++;
                        _posChanged = true;
                    }
                    break;
            }
        }
    }

}
