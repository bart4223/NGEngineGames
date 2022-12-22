//
//  NG8x8RGBMatrixGameSnake.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 22.12.22.
//

#include "NG8x8RGBMatrixGameSnake.h"

NG8x8RGBMatrixGameSnake::NG8x8RGBMatrixGameSnake() {
    _create("Snake");
    _scoreDigits = GAMESNAKESCOREDIGITS;
    _autoRestartGame = true;
    _gameFinishedDelay = GAMESNAKEFINISHDELAY;
}

void NG8x8RGBMatrixGameSnake::_rollSnakeColor() {
    _colorSnake.red = random(0, 256);
    _colorSnake.green = random(0, 256);
    _colorSnake.blue = random(0, 256);
}

void NG8x8RGBMatrixGameSnake::_calculateNewDiamondPosition() {
    bool ok = false;
    while (!ok) {
        int x = random(0, GAMESNAKEMAZESIZEX);
        int y = random(0, GAMESNAKEMAZESIZEY);
        ok = _posXSnake != x || _posYSnake != y;
        ok = ok && _maze[y][x] == 0;
        if (ok) {
            _posXDiamond = x;
            _posYDiamond = y;
        }
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Diamomd-X:%d Diamond-Y:%d", _posXDiamond, _posYDiamond);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameSnake::_resetMaze() {
    for (int y = 0; y < GAMESNAKEMAZESIZEY; y++) {
        for (int x = 0; x < GAMESNAKEMAZESIZEX; x++) {
            _maze[y][x] = 0;
        }
    }
}

void NG8x8RGBMatrixGameSnake::_computeMaze() {
    for (int y = 0; y < GAMESNAKEMAZESIZEY; y++) {
        for (int x = 0; x < GAMESNAKEMAZESIZEX; x++) {
            if (_maze[y][x] > 0) {
                if ((x != _posXSnake) || (y != _posYSnake)) {
                    _maze[y][x]--;
                }
            }
        }
    }
}

void NG8x8RGBMatrixGameSnake::_moveSnake() {
    _posXSnake = _posXSnake + _directionXSnake;
    _posYSnake = _posYSnake + _directionYSnake;
    _gameFinished = (_posXSnake < 0 || _posXSnake > (GAMESNAKEMAZESIZEX - 1) || _posYSnake < 0 || _posYSnake > (GAMESNAKEMAZESIZEY - 1) || _maze[_posYSnake][_posXSnake] > 0);
    if (!_gameFinished) {
        if ((_posXSnake == _posXDiamond) && (_posYSnake == _posYDiamond)) {
            _snakeThreshold++;
            _calculateNewDiamondPosition();
            _scoreCounter++;
        }
        _maze[_posYSnake][_posXSnake] = _snakeThreshold;
        _lastSnakeMove = millis();
    }
}

void NG8x8RGBMatrixGameSnake::_doInitialize() {
    _score->setColorOff(GAMDESNAKECOLORSCOREOFF);
    _score->setColorOn(GAMDESNAKECOLORSCOREON);
    if (_logging) {
        char log[100];
        sprintf(log, "%s.Initialize", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameSnake::_doStartGame() {
    _posXSnake = 3;
    _posYSnake = 3;
    _snakeThreshold = 1;
    _directionXSnake = 1;
    _directionYSnake = 0;
    _resetMaze();
    _maze[_posYSnake][_posXSnake] = _snakeThreshold;
    _lastSnakeMove = millis();
    _rollSnakeColor();
    _calculateNewDiamondPosition();
    _ownRender();
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameSnake::_doFinishGame() {
    _cdm->clear();
    if (_logging) {
        char log[100];
        sprintf(log, "%s.FinishGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameSnake::_doProcessingLoop() {
    if (_gameStarted) {
        _ownJoystickLoop();
        if ((millis() - _lastSnakeMove) > GAMESNAKEMOVEDELAY) {
            _moveSnake();
            _computeMaze();
            if (!_gameFinished) {
                _ownRender();
            }
        }
    }
}

void NG8x8RGBMatrixGameSnake::_ownRender() {
    _cdm->beginUpdate();
    for (int y = 0; y < GAMESNAKEMAZESIZEY; y++) {
        for (int x = 0; x < GAMESNAKEMAZESIZEX; x++) {
            if (_maze[y][x] > 0) {
                _cdm->drawPoint(x, y, _colorSnake);
            } else {
                _cdm->drawPoint(x, y, COLOR_BLACK);
            }
        }
    }
    _cdm->drawPoint(_posXDiamond, _posYDiamond, COLOR_YELLOW);
    _score->setValue(_scoreCounter);
    _cdm->endUpdate();
}

void NG8x8RGBMatrixGameSnake::_ownJoystickLoop() {
    for (int i = 0; i < _joystickCount; i++) {
        if (_joysticks[i].joystick->hasLastMovement()) {
            switch(_joysticks[i].joystick->getLastMovement()) {
                case jmUp:
                    _directionXSnake = 0;
                    _directionYSnake = -1;
                    break;
                case jmDown:
                    _directionXSnake = 0;
                    _directionYSnake = 1;
                    break;
                case jmLeft:
                    _directionXSnake = -1;
                    _directionYSnake = 0;
                    break;
                case jmRight:
                    _directionXSnake = 1;
                    _directionYSnake = 0;
                    break;
                case jmFire:
                    _rollSnakeColor();
                    break;
            }
        }
    }
}
