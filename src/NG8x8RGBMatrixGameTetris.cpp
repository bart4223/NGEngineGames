//
//  NG8x8RGBMatrixGameTetris.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 30.12.22.
//

#include "NG8x8RGBMatrixGameTetris.h"

NG8x8RGBMatrixGameTetris::NG8x8RGBMatrixGameTetris() {
    _create("Tetris");
    _scoreDigits = GAMETETRISSCOREDIGITS;
    _gameToggleMode = gtmBreakContinue;
    _autoRestartGame = true;
    _gameFinishedDelay = GAMETETRISFINISHDELAY;
    _gameNextStepDelay = GAMETETRISMOVEDELAY;
}

void NG8x8RGBMatrixGameTetris::_resetMaze() {
    for (int y = 0; y < GAMETETRISMAZESIZEY; y++) {
        for (int x = 0; x < GAMETETRISMAZESIZEX; x++) {
            _maze[y][x] = 0;
        }
    }
}

void NG8x8RGBMatrixGameTetris::_clearTetromino() {
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

void NG8x8RGBMatrixGameTetris::_persistTetromino() {
    for (int y = 0; y < GAMETETRISMAZESIZEY; y++) {
        for (int x = 0; x < GAMETETRISMAZESIZEX; x++) {
            if (_maze[y][x] <= 0) {
                _maze[y][x] = abs(_maze[y][x]);
            }
        }
    }
}

void NG8x8RGBMatrixGameTetris::_computeTetromino() {
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

void NG8x8RGBMatrixGameTetris::_computeMaze() {
    for (int i = 0; i < 2; i++) {
        byte complete = 0;
        for (int y = GAMETETRISMAZESIZEY - 1; y > 0; y--) {
            if (complete == 0) {
                for (int x = 0; x < GAMETETRISMAZESIZEX; x++) {
                    if (_maze[y][x] > 0) {
                        complete++;
                    }
                }
                if (complete == GAMETETRISMAZESIZEX) {
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
                for (int x = 0; x < GAMETETRISMAZESIZEX; x++) {
                    _maze[y][x] = _maze[y - 1][x];
                }
            }
        }
        if (complete > 0) {
            for (int x = 0; x < GAMETETRISMAZESIZEX; x++) {
                _maze[0][x] = 0;
            }
        }
    }
}

bool NG8x8RGBMatrixGameTetris::_checkTetromino(byte posX, byte posY, byte sequence) {
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

void NG8x8RGBMatrixGameTetris::_spawnTetromino() {
    _tetrominoColor = random(1, (sizeof(globalTetrominoColors) / sizeof(globalTetrominoColors[0])) + 1);
    _posYTetromino = 0;
    _posXTetromino = random(0, GAMETETRISMAZESIZEX - 1);
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

void NG8x8RGBMatrixGameTetris::_doInitialize() {
    _score->setColorOff(GAMETETRISCOLORSCOREOFF);
    _score->setColorOn(GAMETETRISCOLORSCOREON);
    if (_logging) {
        char log[100];
        sprintf(log, "%s.Initialize", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameTetris::_doStartUp() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartUp", _name);
        writeInfo(log);
    }
    _ownIntro();
}

void NG8x8RGBMatrixGameTetris::_doStartUpDone() {
    _cdm->clear();
    _score->setValue(_scoreCounter);
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartUp done", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameTetris::_doStartGame() {
    _resetMaze();
    _spawnTetromino();
    _computeTetromino();
    _ownRender();
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameTetris::_doBreakGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s.BreakGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameTetris::_doContinueGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s.ContinueGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameTetris::_doFinishGame() {
    _cdm->clear();
    if (_logging) {
        char log[100];
        sprintf(log, "%s.FinishGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameTetris::_doProcessingLoop() {
    if (_gameStarted) {
        _ownJoystickLoop();
        if ((millis() - _lastTetrominoMove) > _gameNextStepDelay) {
            bool spawnTetromino = false;
            if (_posYTetromino < GAMETETRISMAZESIZEY - 2) {
                spawnTetromino = !_checkTetromino(_posXTetromino, _posYTetromino + 1, _tetrominoSequence);
                if (!spawnTetromino) {
                    _clearTetromino();
                    _posYTetromino++;
                    _computeTetromino();
                    _lastTetrominoMove = millis();
                }
            } else if (_posYTetromino == GAMETETRISMAZESIZEY - 2 && _tetrominoKind == tkI && _tetrominoSequence == 0) {
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

void NG8x8RGBMatrixGameTetris::_ownIntro() {
    colorRGB c;
    c.red = globalTetrominoColors[0][0];
    c.green = globalTetrominoColors[0][1];
    c.blue = globalTetrominoColors[0][2];
    _cdm->clear();
    _cdm->drawPoint(0, 6, c);
    _cdm->drawPoint(0, 7, c);
    _cdm->drawPoint(1, 7, c);
    c.red = globalTetrominoColors[3][0];
    c.green = globalTetrominoColors[3][1];
    c.blue = globalTetrominoColors[3][2];
    _cdm->drawPoint(2, 6, c);
    _cdm->drawPoint(2, 7, c);
    c.red = globalTetrominoColors[5][0];
    c.green = globalTetrominoColors[5][1];
    c.blue = globalTetrominoColors[5][2];
    _cdm->drawPoint(4, 7, c);
    _cdm->drawPoint(5, 6, c);
    _cdm->drawPoint(5, 7, c);
    c.red = globalTetrominoColors[2][0];
    c.green = globalTetrominoColors[2][1];
    c.blue = globalTetrominoColors[2][2];
    _cdm->drawPoint(6, 7, c);
    _cdm->drawPoint(7, 7, c);
    for (int i = 0; i < GAMETETRISSPLASHTIMES; i++) {
        _cdm->beginUpdate();
        c.red = globalTetrominoColors[i%4][0];
        c.green = globalTetrominoColors[i%4][1];
        c.blue = globalTetrominoColors[i%4][2];
        switch(i%4) {
            case 0:
                _cdm->drawPoint(3, 2, c);
                _cdm->drawPoint(4, 2, COLOR_BLACK);
                _cdm->drawPoint(3, 3, c);
                _cdm->drawPoint(4, 3, c);
               break;
            case 1:
                _cdm->drawPoint(3, 2, c);
                _cdm->drawPoint(4, 2, c);
                _cdm->drawPoint(3, 3, c);
                _cdm->drawPoint(4, 3, COLOR_BLACK);
                break;
            case 2:
                _cdm->drawPoint(3, 2, c);
                _cdm->drawPoint(4, 2, c);
                _cdm->drawPoint(3, 3, COLOR_BLACK);
                _cdm->drawPoint(4, 3, c);
                break;
            case 3:
                _cdm->drawPoint(3, 2, COLOR_BLACK);
                _cdm->drawPoint(4, 2, c);
                _cdm->drawPoint(3, 3, c);
                _cdm->drawPoint(4, 3, c);
                break;
        }
        _cdm->endUpdate();
        delay(GAMETETRISSPLASHDELAY);
    }
}

void NG8x8RGBMatrixGameTetris::_ownOutro() {
    colorRGB c;
    for (int y = GAMETETRISMAZESIZEY - 1; y >= 0; y--) {
        _cdm->beginUpdate();
        for (int x = 0; x < GAMETETRISMAZESIZEX; x++) {
            if (_maze[y][x] == 0) {
                byte value = random(0, sizeof(globalTetrominoColors) / sizeof(globalTetrominoColors[0]));
                c.red = globalTetrominoColors[value][0];
                c.green = globalTetrominoColors[value][1];
                c.blue = globalTetrominoColors[value][2];
                _cdm->drawPoint(x, y, c);
            }
        }
        _cdm->endUpdate();
        delay(GAMETETRISOUTRODELAY);
    }
}

void NG8x8RGBMatrixGameTetris::_ownRender() {
    colorRGB c;
    int value;
    _cdm->beginUpdate();
    for (int y = 0; y < GAMETETRISMAZESIZEY; y++) {
        for (int x = 0; x < GAMETETRISMAZESIZEX; x++) {
            value = abs(_maze[y][x]);
            if (value > 0) {
                c.red = globalTetrominoColors[value - 1][0];
                c.green = globalTetrominoColors[value - 1][1];
                c.blue = globalTetrominoColors[value - 1][2];
                _cdm->drawPoint(x, y, c);
            } else {
                _cdm->drawPoint(x, y, COLOR_BLACK);
            }
        }
    }
    _score->setValue(_scoreCounter);
    _cdm->endUpdate();
}

void NG8x8RGBMatrixGameTetris::_ownJoystickLoop() {
    for (int i = 0; i < _joystickCount; i++) {
        if (_joysticks[i].joystick->hasLastMovement()) {
            switch(_joysticks[i].joystick->getLastMovement()) {
                case jmUp:
                    break;
                case jmDown:
                    break;
                case jmLeft:
                    if (_posXTetromino > 0) {
                        if (_checkTetromino(_posXTetromino - 1, _posYTetromino, _tetrominoSequence)) {
                            _clearTetromino();
                            _posXTetromino--;
                            _computeTetromino();
                        }
                    } else if (_tetrominoKind == tkI && _tetrominoSequence == 1) {
                        if (_checkTetromino(_posXTetromino, _posYTetromino, 3)) {
                            _clearTetromino();
                            _tetrominoSequence = 3;
                            _computeTetromino();
                        }
                    }
                    break;
                case jmRight:
                    if (_posXTetromino < GAMETETRISMAZESIZEX - 2) {
                        if (_checkTetromino(_posXTetromino + 1, _posYTetromino, _tetrominoSequence)) {
                            _clearTetromino();
                            _posXTetromino++;
                            _computeTetromino();
                        }
                    } else if (_tetrominoKind == tkI && _tetrominoSequence == 3) {
                        if (_checkTetromino(_posXTetromino, _posYTetromino, 1)) {
                            _clearTetromino();
                            _tetrominoSequence = 1;
                            _computeTetromino();
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
                    }
                    break;
            }
        }
    }
}

