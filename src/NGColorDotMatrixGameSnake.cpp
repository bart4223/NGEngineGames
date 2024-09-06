//
//  NGColorDotMatrixGameSnake.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 22.12.22.
//

#include "NGColorDotMatrixGameSnake.h"

NGColorDotMatrixGameSnake::NGColorDotMatrixGameSnake() {
    _create("Snake");
    _gameToggleMode = gtmBreakContinue;
    _autoRestartGame = true;
    _gameNextStepDelay = GAMESNAKEMOVEDELAY;
    _pointCounterAnimationDelay = GAMESNAKEOUTRODELAY;
    _startUpDoneDelay = GAMESNAKEINTRODONEDELAY;
}

void NGColorDotMatrixGameSnake::_rollSnakeColor() {
    _colorSnake.red = random(0, 256);
    _colorSnake.green = random(0, 256);
    _colorSnake.blue = random(0, 256);
}

void NGColorDotMatrixGameSnake::_calculateNewDiamondPosition() {
    bool ok = false;
    while (!ok) {
        int x = random(0, _maxGameSnakeX);
        int y = random(0, _maxGameSnakeY);
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

void NGColorDotMatrixGameSnake::_resetMaze() {
    for (int y = 0; y < _maxGameSnakeY; y++) {
        for (int x = 0; x < _maxGameSnakeX; x++) {
            _maze[y][x] = 0;
        }
    }
}

void NGColorDotMatrixGameSnake::_computeMaze() {
    for (int y = 0; y < _maxGameSnakeY; y++) {
        for (int x = 0; x < _maxGameSnakeX; x++) {
            if (_maze[y][x] > 0) {
                _maze[y][x]--;
            }
        }
    }
}

bool NGColorDotMatrixGameSnake::_moveSnake() {
    bool res = false;
    _posXSnake = _posXSnake + _directionXSnake;
    _posYSnake = _posYSnake + _directionYSnake;
    _gameFinished = (_posXSnake < 0 || _posXSnake > (_maxGameSnakeX - 1) || _posYSnake < 0 || _posYSnake > (_maxGameSnakeY - 1) || _maze[_posYSnake][_posXSnake] > 0);
    if (!_gameFinished) {
        res = (_posXSnake == _posXDiamond) && (_posYSnake == _posYDiamond);
        if (res) {
            _snakeThreshold++;
            _calculateNewDiamondPosition();
            _scoreCounter++;
        }
        _maze[_posYSnake][_posXSnake] = _snakeThreshold;
        if (!res) {
            _maze[_posYSnake][_posXSnake]++;
        }
        _lastSnakeMove = millis();
    }
    return res;
}

void NGColorDotMatrixGameSnake::_doInitialize() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s Initialize...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameSnake::_doStartUp() {
    _score->setColorOff(GAMESNAKECOLORSCOREOFF);
    _score->setColorOn(GAMESNAKECOLORSCOREON);
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

void NGColorDotMatrixGameSnake::_doStartUpDone() {
    _ipc->clear();
    _score->setValue(0);
    if (_logging) {
        char log[100];
        sprintf(log, "%s StartUp done", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameSnake::_doStartGame() {
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
        sprintf(log, "%s Start...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameSnake::_doBreakGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s Break...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameSnake::_doContinueGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s Continue...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameSnake::_doFinishGame() {
    _ipc->clear();
    _ownOutro();
    if (_logging) {
        char log[100];
        sprintf(log, "%s Finish...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameSnake::_ownOutro() {
    _pointCounter->setColor(_colorSnake);
    _pointCounter->setCounter(_scoreCounter, true);
    long start = millis();
    while (millis() - start < GAMESNAKEFINISHDELAY * _pointCounter->getCurrentMaxDigits()) {
        _pointCounter->processingLoop();
    }
}

void NGColorDotMatrixGameSnake::_doProcessingLoop() {
    if (_gameStarted) {
        _ownJoystickLoop();
        if ((millis() - _lastSnakeMove) > _gameNextStepDelay) {
            if (!_moveSnake()) {
                _computeMaze();
            }
            if (!_gameFinished) {
                _ownRender();
            }
        }
    }
}

void NGColorDotMatrixGameSnake::_ownIntro() {
    byte offsetX = (_ipc->getWidth() - 8) / 2;
    byte offsetY = (_ipc->getHeight() - 8) / 2;
    _ipc->clear();
    _rollSnakeColor();
    _ipc->drawPoint(4 + offsetX, 3 + offsetY, _colorSnake);
}

void NGColorDotMatrixGameSnake::_ownIntroAnimation() {
    _startUpDone = _startUpAnimationStep >= GAMESNAKEINTROANIMATIONSTEPS;
    if (!_startUpDone) {
        if (millis() - _lastStartUpAnimationStep > GAMESNAKEINTRODELAY) {
            byte offsetX = (_ipc->getWidth() - 8) / 2;
            byte offsetY = (_ipc->getHeight() - 8) / 2;
            _rollSnakeColor();
            switch (_startUpAnimationStep) {
                case 0:
                    _ipc->drawPoint(4 + offsetX, 4 + offsetY, _colorSnake);
                    _startUpAnimationStep++;
                    break;
                case 1:
                    _ipc->drawPoint(3 + offsetX, 4 + offsetY, _colorSnake);
                    _startUpAnimationStep++;
                    break;
                case 2:
                    _ipc->drawPoint(2 + offsetX, 4 + offsetY, _colorSnake);
                    _startUpAnimationStep++;
                    break;
                case 3:
                    _ipc->drawPoint(2 + offsetX, 3 + offsetY, _colorSnake);
                    _startUpAnimationStep++;
                    break;
                case 4:
                    _ipc->drawPoint(2 + offsetX, 2 + offsetY, _colorSnake);
                    _startUpAnimationStep++;
                    _introAnimationIndex = 2;
                    break;
                case 5:
                    if (_introAnimationIndex < 7) {
                        _ipc->drawPoint(_introAnimationIndex + offsetX, 1 + offsetY, _colorSnake);
                        _introAnimationIndex++;
                    } else {
                        _startUpAnimationStep++;
                        _introAnimationIndex = 2;
                    }
                    break;
                case 6:
                    if (_introAnimationIndex < 7) {
                        _ipc->drawPoint(6 + offsetX, _introAnimationIndex + offsetY, _colorSnake);
                        _introAnimationIndex++;
                    } else {
                        _startUpAnimationStep++;
                        _introAnimationIndex = 5;
                    }
                    break;
                case 7:
                    if (_introAnimationIndex > 0) {
                        _ipc->drawPoint(_introAnimationIndex + offsetX, 6 + offsetY, _colorSnake);
                        _introAnimationIndex--;
                    } else {
                        _startUpAnimationStep++;
                    }
                    break;
            }
            _lastStartUpAnimationStep = millis();
        }
    }
}

void NGColorDotMatrixGameSnake::_ownRender() {
    _ipc->beginUpdate();
    for (int y = 0; y < _maxGameSnakeY; y++) {
        for (int x = 0; x < _maxGameSnakeX; x++) {
            if (_maze[y][x] > 0) {
                _ipc->drawPoint(x, y, _colorSnake);
            } else {
                _ipc->drawPoint(x, y, _ipc->getBackground());
            }
        }
    }
    _ipc->drawPoint(_posXDiamond, _posYDiamond, COLOR_YELLOW);
    _score->setValue(_scoreCounter);
    _ipc->endUpdate();
}

void NGColorDotMatrixGameSnake::_ownJoystickLoop() {
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
                    _ownRender();
                    break;
            }
        }
    }
}

void NGColorDotMatrixGameSnake::registerColorDotMatrix(NGIPaintableComponent *ipc) {
    _scoreDigitPosX = ipc->getWidth() - 1;
    _scoreDigitPosY = ipc->getHeight() - 1;
    _scoreDigits = ipc->getHeight();
    NGCustomColorDotMatrixGame::registerColorDotMatrix(ipc);
    _maxGameSnakeX = ipc->getWidth() - 1;
    _maxGameSnakeY = ipc->getHeight();
    switch(_gameMode) {
        case gmNormal:
            _gameNextStepDelay = _gameNextStepDelay * 0.75;
            break;
        case gmBig:
            _gameNextStepDelay = _gameNextStepDelay * 0.5;
            break;
    }
}
