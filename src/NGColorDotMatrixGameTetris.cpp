//
//  NGColorDotMatrixGameTetris.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 30.12.22.
//

#include "NGColorDotMatrixGameTetris.h"

NGColorDotMatrixGameTetris::NGColorDotMatrixGameTetris() {
    _create("Tetris");
    _gameToggleMode = gtmBreakContinue;
    _autoRestartGame = true;
    _playStartUpSoundConcurrently = true;
    _gameFinishedDelay = GAMETETRISFINISHDELAY;
    _pointCounterAnimationDelay = GAMETETRISOUTRODELAY;
}

void NGColorDotMatrixGameTetris::_resetMaze() {
    for (int y = 0; y < _maxGameTetrisY; y++) {
        for (int x = 0; x < _maxGameTetrisX; x++) {
            _maze[y][x] = 0;
        }
    }
}

void NGColorDotMatrixGameTetris::_clearTetromino() {
    switch(_tetrominoKind) {
        case tkI:
            switch(_tetrominoSequence) {
                case 0:
                    _maze[_posYTetromino][_posXTetromino] = 0;
                    _maze[_posYTetromino][_posXTetromino + 1] = 0;
                    break;
                case 1:
                    _maze[_posYTetromino][_posXTetromino + 1] = 0;
                    _maze[_posYTetromino + 1][_posXTetromino + 1] = 0;
                    break;
                case 2:
                    _maze[_posYTetromino + 1][_posXTetromino] = 0;
                    _maze[_posYTetromino + 1][_posXTetromino + 1] = 0;
                    break;
                case 3:
                    _maze[_posYTetromino][_posXTetromino] = 0;
                    _maze[_posYTetromino + 1][_posXTetromino] = 0;
                    break;
            }
            break;
        case tkL:
            switch(_tetrominoSequence) {
                case 0:
                    _maze[_posYTetromino][_posXTetromino] = 0;
                    _maze[_posYTetromino + 1][_posXTetromino] = 0;
                    _maze[_posYTetromino + 1][_posXTetromino + 1] = 0;
                    break;
                case 1:
                    _maze[_posYTetromino][_posXTetromino] = 0;
                    _maze[_posYTetromino][_posXTetromino + 1] = 0;
                    _maze[_posYTetromino + 1][_posXTetromino] = 0;
                    break;
                case 2:
                    _maze[_posYTetromino][_posXTetromino] = 0;
                    _maze[_posYTetromino][_posXTetromino + 1] = 0;
                    _maze[_posYTetromino + 1][_posXTetromino + 1] = 0;
                    break;
                case 3:
                    _maze[_posYTetromino][_posXTetromino + 1] = 0;
                    _maze[_posYTetromino + 1][_posXTetromino] = 0;
                    _maze[_posYTetromino + 1][_posXTetromino + 1] = 0;
                    break;
            }
            break;
    }
}

void NGColorDotMatrixGameTetris::_persistTetromino() {
    for (int y = 0; y < _maxGameTetrisY; y++) {
        for (int x = 0; x < _maxGameTetrisX; x++) {
            if (_maze[y][x] <= 0) {
                _maze[y][x] = abs(_maze[y][x]);
            }
        }
    }
}

void NGColorDotMatrixGameTetris::_computeTetromino() {
    switch(_tetrominoKind) {
        case tkI:
            switch(_tetrominoSequence) {
                case 0:
                    _maze[_posYTetromino][_posXTetromino] = -_tetrominoColor;
                    _maze[_posYTetromino][_posXTetromino + 1] = -_tetrominoColor;
                    break;
                case 1:
                    _maze[_posYTetromino][_posXTetromino + 1] = -_tetrominoColor;
                    _maze[_posYTetromino + 1][_posXTetromino + 1] = -_tetrominoColor;
                    break;
                case 2:
                    _maze[_posYTetromino + 1][_posXTetromino] = -_tetrominoColor;
                    _maze[_posYTetromino + 1][_posXTetromino + 1] = -_tetrominoColor;
                    break;
                case 3:
                    _maze[_posYTetromino][_posXTetromino] = -_tetrominoColor;
                    _maze[_posYTetromino + 1][_posXTetromino] = -_tetrominoColor;
                    break;
            }
            break;
        case tkL:
            switch(_tetrominoSequence) {
                case 0:
                    _maze[_posYTetromino][_posXTetromino] = -_tetrominoColor;
                    _maze[_posYTetromino + 1][_posXTetromino] = -_tetrominoColor;
                    _maze[_posYTetromino + 1][_posXTetromino + 1] = -_tetrominoColor;
                    break;
                case 1:
                    _maze[_posYTetromino][_posXTetromino] = -_tetrominoColor;
                    _maze[_posYTetromino][_posXTetromino + 1] = -_tetrominoColor;
                    _maze[_posYTetromino + 1][_posXTetromino] = -_tetrominoColor;
                    break;
                case 2:
                    _maze[_posYTetromino][_posXTetromino] = -_tetrominoColor;
                    _maze[_posYTetromino][_posXTetromino + 1] = -_tetrominoColor;
                    _maze[_posYTetromino + 1][_posXTetromino + 1] = -_tetrominoColor;
                    break;
                case 3:
                    _maze[_posYTetromino][_posXTetromino + 1] = -_tetrominoColor;
                    _maze[_posYTetromino + 1][_posXTetromino] = -_tetrominoColor;
                    _maze[_posYTetromino + 1][_posXTetromino + 1] = -_tetrominoColor;
                    break;
            }
            break;
    }
}

void NGColorDotMatrixGameTetris::_computeMaze() {
    for (int i = 0; i < 2; i++) {
        byte complete = 0;
        for (int y = _maxGameTetrisY - 1; y > 0; y--) {
            if (complete == 0) {
                for (int x = 0; x < _maxGameTetrisX; x++) {
                    if (_maze[y][x] > 0) {
                        complete++;
                    }
                }
                if (complete == _maxGameTetrisX) {
                    _scoreCounter++;
                    if (_scoreCounter % 10 == 0) {
                        _gameNextStepDelay = _gameNextStepDelay - (GAMETETRISMOVEDELAY / 10);
                        if (_gameNextStepDelay < 0) {
                            _gameNextStepDelay = 0;
                        }
                    }
                } else {
                    complete = 0;
                }
            }
            if (complete > 0) {
                for (int x = 0; x < _maxGameTetrisX; x++) {
                    _maze[y][x] = _maze[y - 1][x];
                }
            }
        }
        if (complete > 0) {
            for (int x = 0; x < _maxGameTetrisX; x++) {
                _maze[0][x] = 0;
            }
        }
    }
}

bool NGColorDotMatrixGameTetris::_checkTetromino(byte posX, byte posY, byte sequence) {
    bool res = true;
    switch(_tetrominoKind) {
        case tkI:
            switch(sequence) {
                case 0:
                    res = _maze[posY][posX] <= 0;
                    if (res) {
                        res = _maze[posY][posX + 1] <= 0;
                    }
                    break;
                case 1:
                    res = _maze[posY][posX + 1] <= 0;
                    if (res) {
                        res = _maze[posY + 1][posX + 1] <= 0;
                    }
                    break;
                case 2:
                    res = _maze[posY + 1][posX] <= 0;
                    if (res) {
                        res = _maze[posY + 1][posX + 1] <= 0;
                    }
                    break;
                case 3:
                    res = _maze[posY][posX] <= 0;
                    if (res) {
                        res = _maze[posY + 1][posX] <= 0;
                    }
                    break;
            }
            break;
        case tkL:
            switch(sequence) {
                case 0:
                    res = _maze[posY][posX] <= 0;
                    if (res) {
                        res = _maze[posY + 1][posX] <= 0;
                    }
                    if (res) {
                        res = _maze[posY + 1][posX + 1] <= 0;
                    }
                    break;
                case 1:
                    res = _maze[posY][posX] <= 0;
                    if (res) {
                        res = _maze[posY + 1][posX] <= 0;
                    }
                    if (res) {
                        res = _maze[posY][posX + 1] <= 0;
                    }
                    break;
                case 2:
                    res = _maze[posY][posX] <= 0;
                    if (res) {
                        res = _maze[posY + 1][posX + 1] <= 0;
                    }
                    if (res) {
                        res = _maze[posY][posX] <= 0;
                    }
                    break;
                case 3:
                    res = _maze[posY][posX + 1] <= 0;
                    if (res) {
                        res = _maze[posY + 1][posX] <= 0;
                    }
                    if (res) {
                        res = _maze[posY + 1][posX + 1] <= 0;
                    }
                    break;
            }
            break;
    }
    return res;
}

void NGColorDotMatrixGameTetris::_spawnTetromino() {
    _tetrominoColor = random(1, (sizeof(globalTetrominoColors) / sizeof(globalTetrominoColors[0])) + 1);
    _posYTetromino = 0;
    _posXTetromino = random(0, _maxGameTetrisX - 1);
    switch(random(0, 2)) {
        case 0:
            _tetrominoKind = tkI;
            if (_getYesOrNo()) {
                _tetrominoSequence = 3;
            } else {
                _tetrominoSequence = random(0, 2);
            }
            break;
        case 1:
            _tetrominoKind = tkL;
            _tetrominoSequence = random(0, 4);
            break;
    }
}

void NGColorDotMatrixGameTetris::_doInitialize() {
    _score->setColorOff(GAMETETRISCOLORSCOREOFF);
    _score->setColorOn(GAMETETRISCOLORSCOREON);
    if (_logging) {
        char log[100];
        sprintf(log, "%s Initialize...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameTetris::_doStartUp() {
    if (!_inStartUpAnimation) {
        if (_logging) {
            char log[100];
            sprintf(log, "%s StartUp...", _name);
            writeInfo(log);
        }
        _ownIntro();
        _inStartUpAnimation = true;
        _startUpAnimationStep = -1;
    } else {
        _ownIntroAnimation();
    }
}

void NGColorDotMatrixGameTetris::_doStartUpDone() {
    _ipc->clear();
    _score->setValue(_scoreCounter);
    _gameNextStepDelay = GAMETETRISMOVEDELAY;
    switch(_gameMode) {
        case gmNormal:
            _gameNextStepDelay = _gameNextStepDelay * 0.75;
            break;
        case gmBig:
            _gameNextStepDelay = _gameNextStepDelay * 0.5;
            break;
    }
    if (_logging) {
        char log[100];
        sprintf(log, "%s StartUp done", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameTetris::_doStartGame() {
    _resetMaze();
    _spawnTetromino();
    _computeTetromino();
    _ownRender();
    if (_logging) {
        char log[100];
        sprintf(log, "%s Start...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameTetris::_doBreakGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s Break...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameTetris::_doContinueGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s Continue...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameTetris::_doFinishGame() {
    _ipc->clear();
    if (_logging) {
        char log[100];
        sprintf(log, "%s Finish...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameTetris::_doProcessingLoop() {
    if (_gameStarted) {
        _ownJoystickLoop();
        if ((millis() - _lastTetrominoMove) > _gameNextStepDelay) {
            bool spawnTetromino = false;
            if (_posYTetromino < _maxGameTetrisY - 2) {
                spawnTetromino = !_checkTetromino(_posXTetromino, _posYTetromino + 1, _tetrominoSequence);
                if (!spawnTetromino) {
                    _clearTetromino();
                    _posYTetromino++;
                    _computeTetromino();
                    _lastTetrominoMove = millis();
                }
            } else if (_posYTetromino == _maxGameTetrisY - 2 && _tetrominoKind == tkI && _tetrominoSequence == 0) {
                spawnTetromino = !_checkTetromino(_posXTetromino, _posYTetromino, 2);
                if (!spawnTetromino) {
                    _clearTetromino();
                    _tetrominoSequence = 2;
                    _computeTetromino();
                    _lastTetrominoMove = millis();
                }
            } else {
                spawnTetromino = true;
            }
            if (spawnTetromino) {
                _gameFinished = _posYTetromino == 0;
                spawnTetromino = !_gameFinished;
            }
            if (spawnTetromino) {
                _persistTetromino();
                _computeMaze();
                _spawnTetromino();
                _gameFinished = !_checkTetromino(_posXTetromino, _posYTetromino, _tetrominoSequence);
                if (!_gameFinished) {
                    _computeTetromino();
                    _lastTetrominoMove = millis();
                } else {
                    _maze[0][_posXTetromino] = _tetrominoColor;
                    _maze[0][_posXTetromino + 1] = _tetrominoColor;
                    
                }
            }
            _ownRender();
        }
        if (_gameFinished) {
            _ownOutro();
        }
    }
}

void NGColorDotMatrixGameTetris::_ownIntro() {
    int x = 0;
    colorRGB c;
    c.red = globalTetrominoColors[0][0];
    c.green = globalTetrominoColors[0][1];
    c.blue = globalTetrominoColors[0][2];
    _ipc->clear();
    while (x < _maxGameTetrisX - 2) {
        _ipc->drawPoint(x, _maxGameTetrisY - 2, c);
        _ipc->drawPoint(x, _maxGameTetrisY - 1, c);
        x++;
        _ipc->drawPoint(x, _maxGameTetrisY - 1, c);
        c.red = globalTetrominoColors[3][0];
        c.green = globalTetrominoColors[3][1];
        c.blue = globalTetrominoColors[3][2];
        x++;
        _ipc->drawPoint(x, _maxGameTetrisY - 2, c);
        _ipc->drawPoint(x, _maxGameTetrisY - 1, c);
        c.red = globalTetrominoColors[5][0];
        c.green = globalTetrominoColors[5][1];
        c.blue = globalTetrominoColors[5][2];
        x = x + 2;
        _ipc->drawPoint(x, _maxGameTetrisY - 1, c);
        x++;
        _ipc->drawPoint(x, _maxGameTetrisY - 2, c);
        _ipc->drawPoint(x, _maxGameTetrisY - 1, c);
        c.red = globalTetrominoColors[2][0];
        c.green = globalTetrominoColors[2][1];
        c.blue = globalTetrominoColors[2][2];
        x++;
        _ipc->drawPoint(x, _maxGameTetrisY - 1, c);
        x++;
        _ipc->drawPoint(x, _maxGameTetrisY - 1, c);
        x++;
    }
}

void NGColorDotMatrixGameTetris::_ownIntroAnimation() {
    byte x = _maxGameTetrisX / 2;
    byte y = _maxGameTetrisY / 2;
    if (_startUpAnimationStep == -1 || millis() - _lastStartUpAnimationStep >= GAMETETRISSPLASHDELAY) {
        _startUpAnimationStep++;
        _ipc->beginUpdate();
        colorRGB c;
        c.red = globalTetrominoColors[_startUpAnimationStep%4][0];
        c.green = globalTetrominoColors[_startUpAnimationStep%4][1];
        c.blue = globalTetrominoColors[_startUpAnimationStep%4][2];
        switch(_startUpAnimationStep%4) {
            case 0:
                _ipc->drawPoint(x, y - 2, c);
                _ipc->drawPoint(x + 1, y - 2, COLOR_BLACK);
                _ipc->drawPoint(x, y - 1, c);
                _ipc->drawPoint(x + 1, y - 1, c);
               break;
            case 1:
                _ipc->drawPoint(x, y - 2, c);
                _ipc->drawPoint(x + 1, y - 2, c);
                _ipc->drawPoint(x, y - 1, c);
                _ipc->drawPoint(x + 1, y - 1, COLOR_BLACK);
                break;
            case 2:
                _ipc->drawPoint(x, y - 2, c);
                _ipc->drawPoint(x + 1, y - 2, c);
                _ipc->drawPoint(x, y - 1, COLOR_BLACK);
                _ipc->drawPoint(x + 1, y - 1, c);
                break;
            case 3:
                _ipc->drawPoint(x, y - 2, COLOR_BLACK);
                _ipc->drawPoint(x + 1, y - 2, c);
                _ipc->drawPoint(x, y - 1, c);
                _ipc->drawPoint(x + 1, y - 1, c);
                break;
        }
        _ipc->endUpdate();
        _lastStartUpAnimationStep = millis();
        _startUpDone = _startUpAnimationStep == GAMETETRISSPLASHTIMES;
        if (_startUpDone) {
            _inStartUpAnimation = false;
        }
    }
}

void NGColorDotMatrixGameTetris::_ownOutro() {
    colorRGB c;
    for (int y = _maxGameTetrisY - 1; y >= 0; y--) {
        _ipc->beginUpdate();
        for (int x = 0; x < _maxGameTetrisX; x++) {
            if (_maze[y][x] == 0) {
                byte value = random(0, sizeof(globalTetrominoColors) / sizeof(globalTetrominoColors[0]));
                c.red = globalTetrominoColors[value][0];
                c.green = globalTetrominoColors[value][1];
                c.blue = globalTetrominoColors[value][2];
                _ipc->drawPoint(x, y, c);
            }
        }
        _ipc->endUpdate();
        delay(GAMETETRISOUTRODELAY);
    }
    _ipc->clear();
    byte value = random(0, sizeof(globalTetrominoColors) / sizeof(globalTetrominoColors[0]));
    c.red = globalTetrominoColors[value][0];
    c.green = globalTetrominoColors[value][1];
    c.blue = globalTetrominoColors[value][2];
    _pointCounter->setColor(c);
    _pointCounter->setCounter(_scoreCounter, true);
    long start = millis();
    while (millis() - start < GAMETETRISOUTRODPOINTCOUNTERDELAY * _pointCounter->getCurrentMaxDigits()) {
        _pointCounter->processingLoop();
    }
}

void NGColorDotMatrixGameTetris::_ownRender() {
    colorRGB c;
    int value;
    _ipc->beginUpdate();
    for (int y = 0; y < _maxGameTetrisY; y++) {
        for (int x = 0; x < _maxGameTetrisX; x++) {
            value = abs(_maze[y][x]);
            if (value > 0) {
                c.red = globalTetrominoColors[value - 1][0];
                c.green = globalTetrominoColors[value - 1][1];
                c.blue = globalTetrominoColors[value - 1][2];
                _ipc->drawPoint(x, y, c);
            } else {
                _ipc->drawPoint(x, y, COLOR_BLACK);
            }
        }
    }
    _score->setValue(_scoreCounter);
    _ipc->endUpdate();
}

void NGColorDotMatrixGameTetris::_ownJoystickLoop() {
    for (int i = 0; i < _joystickCount; i++) {
        if (_joysticks[i].joystick->hasLastMovement()) {
            switch(_joysticks[i].joystick->getLastMovement()) {
                case jmUp:
                    break;
                case jmDown:
                    if (_posYTetromino < _maxGameTetrisY - 2) {
                        if (_checkTetromino(_posXTetromino, _posYTetromino + 1, _tetrominoSequence)) {
                            _clearTetromino();
                            _posYTetromino++;
                            _computeTetromino();
                            _ownRender();
                        }
                    }
                    break;
                case jmLeft:
                    if (_posXTetromino > 0) {
                        if (_checkTetromino(_posXTetromino - 1, _posYTetromino, _tetrominoSequence)) {
                            _clearTetromino();
                            _posXTetromino--;
                            _computeTetromino();
                            _ownRender();
                        }
                    } else if (_tetrominoKind == tkI && _tetrominoSequence == 1) {
                        if (_checkTetromino(_posXTetromino, _posYTetromino, 3)) {
                            _clearTetromino();
                            _tetrominoSequence = 3;
                            _computeTetromino();
                            _ownRender();
                        }
                    }
                    break;
                case jmRight:
                    if (_posXTetromino < _maxGameTetrisX - 2) {
                        if (_checkTetromino(_posXTetromino + 1, _posYTetromino, _tetrominoSequence)) {
                            _clearTetromino();
                            _posXTetromino++;
                            _computeTetromino();
                            _ownRender();
                        }
                    } else if (_tetrominoKind == tkI && _tetrominoSequence == 3) {
                        if (_checkTetromino(_posXTetromino, _posYTetromino, 1)) {
                            _clearTetromino();
                            _tetrominoSequence = 1;
                            _computeTetromino();
                            _ownRender();
                        }
                    }
                    break;
                case jmFire:
                    int sequence = _tetrominoSequence + 1;
                    if (sequence > 3) {
                        sequence = 0;
                    }
                    if (_checkTetromino(_posXTetromino, _posYTetromino, sequence)) {
                        _clearTetromino();
                        _tetrominoSequence = sequence;
                        _computeTetromino();
                        _ownRender();
                    }
                    break;
            }
        }
    }
}

void NGColorDotMatrixGameTetris::registerColorDotMatrix(NGIPaintableComponent *ipc) {
    _scoreDigitPosX = ipc->getWidth() - 1;
    _scoreDigitPosY = ipc->getHeight() - 1;
    _scoreDigits = ipc->getHeight();
    NGCustomColorDotMatrixGame::registerColorDotMatrix(ipc);
    _maxGameTetrisX = ipc->getWidth() - 1;
    _maxGameTetrisY = ipc->getHeight();
}

