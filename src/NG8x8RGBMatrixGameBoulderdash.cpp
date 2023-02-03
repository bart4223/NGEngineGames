//
//  NG8x8RGBMatrixGameBoulderdash.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 09.01.23.
//

#include "NG8x8RGBMatrixGameBoulderdash.h"

NG8x8RGBMatrixGameBoulderdash::NG8x8RGBMatrixGameBoulderdash() {
    _create("Boulderdash");
    _scoreDigits = GAMEBOULDERDASHSCOREDIGITS;
    _scoreDigitPosX = GAMEBOULDERDASHSCOREDIGITXPOS;
    _scoreDigitPosY = GAMEBOULDERDASHSCOREDIGITYPOS;
    _scoreDirection = GAMEBOULDERDASHSCOREDIRECTION;
    _gameToggleMode = gtmBreakContinue;
    _autoRestartGame = true;
    _gameFinishedDelay = GAMEBOULDERDASHFINISHDELAY;
    _gameNextStepDelay = GAMEBOULDERDASHGRAVITYDELAY;
}

void NG8x8RGBMatrixGameBoulderdash::registerColorDotMatrix(NGColorDotMatrix *cdm) {
    NGCustom8x8RGBMatrixGame::registerColorDotMatrix(cdm);
    _lives = new NGColorDotMatrixBinaryDigit(_cdm, GAMEBOULDERDASHLIVESDIGITS, GAMEBOULDERDASHLIVESDIRECTION, GAMEBOULDERDASHLIVESDIGITXPOS, GAMEBOULDERDASHLIVESDIGITYPOS);
    _fuse = new NGColorDotMatrixFuse(_cdm, GAMEBOULDERDASHFUSEARITY);
}

void NG8x8RGBMatrixGameBoulderdash::_resetMaze() {
    for (int y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
        for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            _maze[y][x] = 0;
        }
    }
}

void NG8x8RGBMatrixGameBoulderdash::_computeGravity() {
    for (int y = GAMEBOULDERDASHMAZESIZEY - 2; y >= 0; y--) {
        for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            bool checkRocky = false;
            if (_maze[y][x] == GAMEBOULDERDASHCOLORINDEXBOULDER) {
                if (_maze[y + 1][x] == 0) {
                    _maze[y][x] = 0;
                    _maze[y + 1][x] = GAMEBOULDERDASHCOLORINDEXBOULDER;
                    checkRocky = true;
                } else if ((_maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXBOULDER || _maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXDIAMOND)) {
                    if (x - 1 >= 0) {
                        if (_maze[y + 1][x - 1] == 0 && _maze[y][x - 1] == 0) {
                            _maze[y][x] = 0;
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXBOULDER;
                            checkRocky = true;
                        }
                    }
                    if (x + 1 < GAMEBOULDERDASHMAZESIZEX) {
                        if (_maze[y + 1][x + 1] == 0 && _maze[y][x + 1] == 0) {
                            _maze[y][x] = 0;
                            _maze[y + 1][x + 1] = GAMEBOULDERDASHCOLORINDEXBOULDER;
                            checkRocky = true;
                        }
                    }
                }
            }
            if (_maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIAMOND) {
                if (_maze[y + 1][x] == 0) {
                    _maze[y][x] = 0;
                    _maze[y + 1][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND;
                    checkRocky = true;
                } else if ((_maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXBOULDER || _maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXDIAMOND)) {
                    if (x - 1 >= 0) {
                        if (_maze[y + 1][x - 1] == 0 && _maze[y][x - 1] == 0) {
                            _maze[y][x] = 0;
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND;
                            checkRocky = true;
                        }
                    }
                    if (x + 1 < GAMEBOULDERDASHMAZESIZEX) {
                        if (_maze[y + 1][x + 1] == 0 && _maze[y][x + 1] == 0) {
                            _maze[y][x] = 0;
                            _maze[y + 1][x + 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND;
                            checkRocky = true;
                        }
                    }
                }
            }
            if (checkRocky) {
                if ((y < (GAMEBOULDERDASHMAZESIZEY - 2)) && (_maze[y + 2][x] == GAMEBOULDERDASHCOLORINDEXROCKY)) {
                    _livesCounter--;
                    _gameFinished = _livesCounter == 0;
                    if (!_gameFinished) {
                        _levelRetry = true;
                    }
                }
            }
        }
    }
}

void NG8x8RGBMatrixGameBoulderdash::_initLevel() {
    _levelFinished = false;
    _levelRetry = false;
    switch(_level) {
        case 1:
            _posXRocky = random(0, 2);
            _posYRocky = random(0, 2);
            _calculateViewPos();
            _levelDiamonds = random(5, 10);
            _fuseStepDelay = GAMEBOULDERDASHLEVELONEFUSESTEPDELAY;
            _initLevelOneMaze();
            //_initLevelTestMaze();
            break;
    }
    _renderRocky();
}

void NG8x8RGBMatrixGameBoulderdash::_initLevelTestMaze() {
    int x, y;
    // Dirt
    for (y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
        for (x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDIRT;
        }
    }
    // Diamonds
    for (int i = 0; i < _levelDiamonds; i++) {
        bool ok;
        do {
            x = random(2, 7);
            y = random(2, 7);
            ok = _maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIRT;
        } while (!ok);
        _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND;
    }
    // Boulders
    int boulders = random(1, 4);
    for (int i = 0; i < boulders; i++) {
        bool ok;
        do {
            x = random(2, 7);
            y = random(2, 7);
            ok = _maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIRT;
        } while (!ok);
        _maze[y][x] = GAMEBOULDERDASHCOLORINDEXBOULDER;
    }
    // Rocky
    _computeRocky();
}

void NG8x8RGBMatrixGameBoulderdash::_initLevelOneMaze() {
    int x, y;
    // Dirt
    for (y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
        for (x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDIRT;
        }
    }
    // Diamonds
    for (int i = 0; i < _levelDiamonds; i++) {
        bool ok;
        do {
            x = random(2, GAMEBOULDERDASHMAZESIZEX);
            y = random(2, GAMEBOULDERDASHMAZESIZEY);
            ok = _maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIRT;
        } while (!ok);
        _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND;
    }
    // Boulders
    int boulders = random(1, 4);
    for (int i = 0; i < boulders; i++) {
        bool ok;
        do {
            x = random(2, GAMEBOULDERDASHMAZESIZEX);
            y = random(2, GAMEBOULDERDASHMAZESIZEY);
            ok = _maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIRT;
        } while (!ok);
        _maze[y][x] = GAMEBOULDERDASHCOLORINDEXBOULDER;
    }
    // Rocky
    _computeRocky();
}

void NG8x8RGBMatrixGameBoulderdash::_clearRocky() {
    _maze[_posYRocky][_posXRocky] = 0;
}

void NG8x8RGBMatrixGameBoulderdash::_computeRocky() {
    _maze[_posYRocky][_posXRocky] = GAMEBOULDERDASHCOLORINDEXROCKY;
}

bool NG8x8RGBMatrixGameBoulderdash::_checkRocky(rockyMoveDirection direction) {
    byte posX = _posXRocky;
    byte posY = _posYRocky;
    switch(direction) {
        case rmdUp:
            posY--;
            break;
        case rmdDown:
            posY++;
            break;
        case rmdLeft:
            posX--;
            break;
        case rmdRight:
            posX++;
            break;
    }
    bool res = _maze[posY][posX] == 0 || _maze[posY][posX] == GAMEBOULDERDASHCOLORINDEXDIRT;
    if (!res) {
        res = _maze[posY][posX] == GAMEBOULDERDASHCOLORINDEXDIAMOND;
        if (res) {
            _levelDiamonds--;
            _scoreCounter++;
            _levelFinished = _levelDiamonds == 0;
        } else {
            switch(direction) {
                case rmdLeft:
                    if (posX - 1 >= 0) {
                        res = (_maze[posY][posX] == GAMEBOULDERDASHCOLORINDEXBOULDER && _maze[posY][posX - 1] == 0);
                        if (res) {
                            _maze[posY][posX - 1] = GAMEBOULDERDASHCOLORINDEXBOULDER;
                        }
                    }
                    break;
                case rmdRight:
                    if (posX + 1 < GAMEBOULDERDASHMAZESIZEX) {
                        res = (_maze[posY][posX] == GAMEBOULDERDASHCOLORINDEXBOULDER && _maze[posY][posX + 1] == 0);
                        if (res) {
                            _maze[posY][posX + 1] = GAMEBOULDERDASHCOLORINDEXBOULDER;
                        }
                    }
                    break;
            }
        }
    }
    return res;
}

void NG8x8RGBMatrixGameBoulderdash::_renderRocky() {
    switch (_rockyBlinkIndex) {
        case 0:
            _cdm->drawPoint(_posXRocky - _viewPosX + 1, _posYRocky - _viewPosY + 1, COLOR_BLUE);
            break;
        case 1:
            _cdm->drawPoint(_posXRocky - _viewPosX + 1, _posYRocky - _viewPosY + 1, COLOR_BLUE_LOW);
            break;
    }
    _rockyBlinkIndex++;
    if (_rockyBlinkIndex > 1) {
        _rockyBlinkIndex = 0;
    }
}

void NG8x8RGBMatrixGameBoulderdash::_calculateViewPos() {
    if (_posXRocky - 4 < 0) {
        _viewPosX = 0;
    } else if (_posXRocky > (GAMEBOULDERDASHMAZESIZEX - 4)) {
        _viewPosX = GAMEBOULDERDASHMAZESIZEX - 7;
    } else {
        _viewPosX = _posXRocky - 4;
    }
    if (_posYRocky - 4 < 0) {
        _viewPosY = 0;
    } else if (_posYRocky > (GAMEBOULDERDASHMAZESIZEY - 4)) {
        _viewPosY = GAMEBOULDERDASHMAZESIZEY - 7;
    } else {
        _viewPosY = _posYRocky - 4;
    }
}

void NG8x8RGBMatrixGameBoulderdash::_ownIntro() {
    _cdm->beginUpdate();
    // Dirt
    _cdm->fillRect(0, 0, 7, 7, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIRT - 1]);
    // Diamonds
    _cdm->drawPoint(6, 3, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND - 1]);
    _cdm->drawPoint(5, 5, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND - 1]);
    _cdm->drawPoint(2, 6, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND - 1]);
    // Boulders
    _cdm->drawPoint(5, 1, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXBOULDER - 1]);
    _cdm->drawPoint(6, 1, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXBOULDER - 1]);
    _cdm->drawPoint(1, 5, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXBOULDER - 1]);
    _cdm->drawPoint(6, 7, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXBOULDER - 1]);
    _cdm->endUpdate();
    for (int i = 0; i < 6; i++) {
        if (i % 2 == 0) {
            _cdm->drawPoint(2, 2, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXROCKY - 1]);
        } else {
            _cdm->drawPoint(2, 2, COLOR_BLUE_LOW);
        }
        if (i < 5) {
            delay(GAMEBOULDERDASHROCKYBLINKDELAY);
        }
    }
}

void NG8x8RGBMatrixGameBoulderdash::_ownOutro() {
    for (int i = 0; i < 4; i++) {
        _cdm->beginUpdate();
        if (i < 3) {
            _cdm->fillRect(4 - i, 4 - i, 4 + i, 4 + i, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND - 1]);
        } else {
            _cdm->drawRect(4 - i, 4 - i, 4 + i, 4 + i, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIRT - 1]);
        }
        _cdm->endUpdate();
        delay(GAMEBOULDERDASHSOUTROANIMATIONDELAY);
    }
    _score->setValue(_scoreCounter);
    delay(GAMEBOULDERDASHSOUTRODELAY);
}

void NG8x8RGBMatrixGameBoulderdash::_ownLevelOutro() {
    _score->setValue(_scoreCounter);
    for (int i = 0; i < 4; i++) {
        _cdm->beginUpdate();
        _cdm->clearRect(_posXRocky - _viewPosX + 1 - i, _posYRocky - _viewPosY + 1 - i, _posXRocky - _viewPosX + 1 + i, _posYRocky - _viewPosY + 1 + i);
        _cdm->endUpdate();
        delay(GAMEBOULDERDASHSOUTROANIMATIONDELAY);
    }
}

void NG8x8RGBMatrixGameBoulderdash::_ownRender() {
    _cdm->beginUpdate();
    for (int y = 1; y < 8; y++) {
        for (int x = 1; x < 8; x++) {
            byte i = _maze[_viewPosY + y - 1][_viewPosX + x - 1];
            if (i > 0) {
                if (i != GAMEBOULDERDASHCOLORINDEXROCKY) {
                    colorRGB c = globalBoulderdashColors[i - 1];
                    _cdm->drawPoint(x, y, c);
                }
            } else {
                _cdm->clearPoint(x, y);
            }
        }
    }
    _score->setValue(_levelDiamonds);
    _lives->setValue(_livesCounter);
    _fuse->setValue(_fuseValue);
    _cdm->endUpdate();
}

void NG8x8RGBMatrixGameBoulderdash::_ownJoystickLoop() {
    for (int i = 0; i < _joystickCount; i++) {
        if (_joysticks[i].joystick->hasLastMovement()) {
            bool move = false;
            switch(_joysticks[i].joystick->getLastMovement()) {
                case jmUp:
                    if (_posYRocky > 0) {
                        move = _checkRocky(rmdUp);
                        if (move) {
                            _clearRocky();
                            _posYRocky--;
                            _computeRocky();
                        }
                    }
                    break;
                case jmDown:
                    if (_posYRocky < GAMEBOULDERDASHMAZESIZEY - 1) {
                        move = _checkRocky(rmdDown);
                        if (move) {
                            _clearRocky();
                            _posYRocky++;
                            _computeRocky();
                        }
                    }
                    break;
                case jmLeft:
                    if (_posXRocky > 0) {
                        move = _checkRocky(rmdLeft);
                        if (move) {
                            _clearRocky();
                            _posXRocky--;
                            _computeRocky();
                        }
                    }
                    break;
                case jmRight:
                    if (_posXRocky < GAMEBOULDERDASHMAZESIZEX - 1) {
                        move = _checkRocky(rmdRight);
                        if (move) {
                            _clearRocky();
                            _posXRocky++;
                            _computeRocky();
                        }
                    }
                    break;
                case jmFire:
                    break;
            }
            if (move) {
                _calculateViewPos();
                _renderRocky();
                _ownRender();
            }
        }
    }
}

void NG8x8RGBMatrixGameBoulderdash::_doInitialize() {
    _score->setColorOff(GAMEBOULDERDASHCOLORSCOREOFF);
    _score->setColorOn(GAMEBOULDERDASHCOLORSCOREON);
    _lives->setColorOff(GAMEBOULDERDASHCOLORLIVESOFF);
    _lives->setColorOn(GAMEBOULDERDASHCOLORLIVESON);
    _fuse->setColorOff(GAMEBOULDERDASHCOLORFUSEOFF);
    _fuse->setColorOn(GAMEBOULDERDASHCOLORFUSEON);
    if (_logging) {
        char log[100];
        sprintf(log, "%s.Initialize", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameBoulderdash::_doStartUp() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartUp", _name);
        writeInfo(log);
    }
    _ownIntro();
}

void NG8x8RGBMatrixGameBoulderdash::_doStartUpDone() {
    _cdm->clear();
    _score->setValue(0);
    _lives->setValue(GAMEBOULDERDASHLIVES);
    _fuse->setValue(GAMEBOULDERDASHMAXFUSE);
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartUp done", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameBoulderdash::_doStartGame() {
    _livesCounter = GAMEBOULDERDASHLIVES;
    _fuseValue = GAMEBOULDERDASHMAXFUSE;
    _level = GAMEBOULDERDASHSTARTLEVEL;
    _resetMaze();
    _initLevel();
    _ownRender();
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameBoulderdash::_doBreakGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s.BreakGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameBoulderdash::_doContinueGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s.ContinueGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameBoulderdash::_doFinishGame() {
    _cdm->clear();
    if (_logging) {
        char log[100];
        sprintf(log, "%s.FinishGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameBoulderdash::_doProcessingLoop() {
    if (_gameStarted) {
        _ownJoystickLoop();
        if (_levelFinished) {
            _level++;
            _gameFinished = _level > GAMEBOULDERDASHMAXLEVEL;
            if (!_gameFinished) {
                _initLevel();
            }
        }
        if (_levelRetry) {
            _ownLevelOutro();
            _initLevel();
        }
        if (!_gameFinished) {
            if ((millis() - _lastRockyBlinked) > GAMEBOULDERDASHROCKYBLINKDELAY) {
                _renderRocky();
                _lastRockyBlinked = millis();
            }
            if ((millis() - _lastGravityMove) > _gameNextStepDelay) {
                _computeGravity();
                _ownRender();
                _lastGravityMove = millis();
            }
            if ((millis() - _lastFuseStep) > _fuseStepDelay) {
                _fuseValue--;
                if (_fuseValue == 0) {
                    _livesCounter--;
                    _gameFinished = _livesCounter == 0;
                    if (!_gameFinished) {
                        _fuseValue = GAMEBOULDERDASHMAXFUSE;
                        _levelRetry = true;
                    }
                }
                _ownRender();
                _lastFuseStep = millis();
            }
        }
        if (_gameFinished) {
            _ownOutro();
        }
    }
}
