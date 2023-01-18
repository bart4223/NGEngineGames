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

void NG8x8RGBMatrixGameBoulderdash::_computeMaze() {
    
}

void NG8x8RGBMatrixGameBoulderdash::_initLevel() {
    _levelFinished = false;
    switch(_level) {
        case 1:
            _posXRocky = random(0, 2);
            _posYRocky = random(0, 2);
            _calculateViewPos();
            _levelDiamonds = random(5, 10);
            _fuseStepDelay = GAMEBOULDERDASHLEVELONEFUSESTEPDELAY;
            _initLevelOneMaze();
            break;
    }
    _renderRocky();
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
            x = random(2, 7); // ToDo random(2, GAMEBOULDERDASHMAZESIZEX);
            y = random(2, 7); // ToDo random(2, GAMEBOULDERDASHMAZESIZEY);
            ok = _maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIRT;
        } while (!ok);
        _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND;
    }
    // Boulders
    int boulders = random(1, 4);
    for (int i = 0; i < boulders; i++) {
        bool ok;
        do {
            x = random(2, 7); // ToDo random(2, GAMEBOULDERDASHMAZESIZEX);
            y = random(2, 7); // ToDo random(2, GAMEBOULDERDASHMAZESIZEY);
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

bool NG8x8RGBMatrixGameBoulderdash::_checkRocky(byte posX, byte posY) {
    bool res = _maze[posY][posX] == 0 || _maze[posY][posX] == GAMEBOULDERDASHCOLORINDEXDIRT;
    if (!res) {
        res = _maze[posY][posX] == GAMEBOULDERDASHCOLORINDEXDIAMOND;
        if (res) {
            _levelDiamonds--;
            _scoreCounter++;
            _levelFinished = _levelDiamonds == 0;
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
    
}

void NG8x8RGBMatrixGameBoulderdash::_ownOutro() {
    
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
                        move = _checkRocky(_posXRocky, _posYRocky - 1);
                        if (move) {
                            _clearRocky();
                            _posYRocky--;
                            _computeRocky();
                        }
                    }
                    break;
                case jmDown:
                    if (_posYRocky < GAMEBOULDERDASHMAZESIZEY - 1) {
                        move = _checkRocky(_posXRocky, _posYRocky + 1);
                        if (move) {
                            _clearRocky();
                            _posYRocky++;
                            _computeRocky();
                        }
                    }
                    break;
                case jmLeft:
                    if (_posXRocky > 0) {
                        move = _checkRocky(_posXRocky - 1, _posYRocky);
                        if (move) {
                            _clearRocky();
                            _posXRocky--;
                            _computeRocky();
                        }
                    }
                    break;
                case jmRight:
                    if (_posXRocky < GAMEBOULDERDASHMAZESIZEX - 1) {
                        move = _checkRocky(_posXRocky + 1, _posYRocky);
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
    _score->setValue(_scoreCounter);
    _lives->setValue(_livesCounter);
    _fuse->setValue(_fuseValue);
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
        if (!_gameFinished) {
            if ((millis() - _lastRockyBlinked) > GAMEBOULDERDASHROCKYBLINKDELAY) {
                _renderRocky();
                _lastRockyBlinked = millis();
            }
            if ((millis() - _lastGravityMove) > _gameNextStepDelay) {
                _computeMaze();
                _ownRender();
                _lastGravityMove = millis();
            }
            if ((millis() - _lastFuseStep) > _fuseStepDelay) {
                _fuseValue--;
                _gameFinished = _fuseValue == 0;
                _lastFuseStep = millis();
                _ownRender();
            }
        } else {
            _ownOutro();
        }
    }
}
