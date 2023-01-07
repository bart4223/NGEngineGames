//
//  NG8x8RGBMatrixGameAsteroids.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 07.01.23.
//

#include "NG8x8RGBMatrixGameAsteroids.h"

NG8x8RGBMatrixGameAsteroids::NG8x8RGBMatrixGameAsteroids() {
    _create("Asteroids");
    _scoreDigits = GAMEASTEROIDSSCOREDIGITS;
    _scoreDigitPosX = GAMEASTEROIDSSCOREDIGITXPOS;
    _scoreDirection = GAMEASTEROIDSSCOREDIRECTION;
    _gameToggleMode = gtmBreakContinue;
    _autoRestartGame = true;
    _gameFinishedDelay = GAMEASTEROIDSFINISHDELAY;
    _gameNextStepDelay = GAMEASTEROIDSMOVEDELAY;
}

void NG8x8RGBMatrixGameAsteroids::_resetMaze() {
    for (int y = 0; y < GAMEASTEROIDSMAZESIZEY; y++) {
        for (int x = 0; x < GAMEASTEROIDSMAZESIZEX; x++) {
            _maze[y][x] = 0;
        }
    }
}

void NG8x8RGBMatrixGameAsteroids::_computeAsteroids() {
    for (int y = 0; y < GAMEASTEROIDSMAZESIZEY; y++) {
        for (int x = 0; x < GAMEASTEROIDSMAZESIZEX; x++) {
            if (_maze[y][x] == GAMEASTEROIDSCOLORINDEXASTEROID) {
                _maze[y][x] = 0;
                if (x > 0) {
                    _gameFinished = _maze[y][x - 1] == GAMEASTEROIDSCOLORINDEXSPACECRAFT;
                    if (!_gameFinished) {
                        _maze[y][x - 1] = GAMEASTEROIDSCOLORINDEXASTEROID;
                    } else {
                        return;
                    }
                }
            }
        }
    }
}

bool NG8x8RGBMatrixGameAsteroids::_computeLaserbeam() {
    bool res = false;
    for (int y = 0; y < GAMEASTEROIDSMAZESIZEY; y++) {
        for (int x = 0; x < GAMEASTEROIDSMAZESIZEX; x++) {
            if (_maze[y][x] == GAMEASTEROIDSCOLORINDEXLASERBEAM) {
                _maze[y][x] = 0;
                if ((x + 1) < GAMEASTEROIDSMAZESIZEX) {
                    if (_maze[y][x + 1] == GAMEASTEROIDSCOLORINDEXASTEROID) {
                        _scoreCounter++;
                    }
                    _maze[y][x + 1] = -GAMEASTEROIDSCOLORINDEXLASERBEAM;
                }
                res = true;
            }
        }
    }
    if (res) {
        for (int y = 0; y < GAMEASTEROIDSMAZESIZEY; y++) {
            for (int x = 0; x < GAMEASTEROIDSMAZESIZEX; x++) {
                if (_maze[y][x] == -GAMEASTEROIDSCOLORINDEXLASERBEAM) {
                    _maze[y][x] = abs(_maze[y][x]);
                }
            }
        }
    }
    return res;
}

void NG8x8RGBMatrixGameAsteroids::_spawnLaserbeam() {
    _maze[_posYSpacecraft + 1][_posXSpacecraft + 3] = GAMEASTEROIDSCOLORINDEXLASERBEAM;
}

void NG8x8RGBMatrixGameAsteroids::_spawnAsteroid() {
    if ((random(0, 10) % 3) == 0) {
        _maze[random(0, GAMEASTEROIDSMAZESIZEY - 1)][GAMEASTEROIDSMAZESIZEX - 1] =  GAMEASTEROIDSCOLORINDEXASTEROID;
    }
}

void NG8x8RGBMatrixGameAsteroids::_clearSpacecraft() {
    _maze[_posYSpacecraft][_posXSpacecraft + 1] = 0;
    _maze[_posYSpacecraft + 1][_posXSpacecraft] = 0;
    _maze[_posYSpacecraft + 1][_posXSpacecraft + 1] = 0;
    _maze[_posYSpacecraft + 1][_posXSpacecraft + 2] = 0;
}

void NG8x8RGBMatrixGameAsteroids::_computeSpacecraft() {
    _maze[_posYSpacecraft][_posXSpacecraft + 1] = GAMEASTEROIDSCOLORINDEXSPACECRAFT;
    _maze[_posYSpacecraft + 1][_posXSpacecraft] = GAMEASTEROIDSCOLORINDEXSPACECRAFT;
    _maze[_posYSpacecraft + 1][_posXSpacecraft + 1] = GAMEASTEROIDSCOLORINDEXSPACECRAFT;
    _maze[_posYSpacecraft + 1][_posXSpacecraft + 2] = GAMEASTEROIDSCOLORINDEXSPACECRAFT;
}

bool NG8x8RGBMatrixGameAsteroids::_checkSpacecraft(byte posX, byte posY) {
    bool res = _maze[posY][posX + 1] == 0 || _maze[posY][posX + 1] == GAMEASTEROIDSCOLORINDEXSPACECRAFT;
    if (res) {
        res = _maze[posY + 1][posX] == 0 || _maze[posY + 1][posX] == GAMEASTEROIDSCOLORINDEXSPACECRAFT;
    }
    if (res) {
        res = _maze[posY + 1][posX + 1] == 0 || _maze[posY + 1][posX + 1] == GAMEASTEROIDSCOLORINDEXSPACECRAFT;
    }
    if (res) {
        res = _maze[posY + 1][posX + 2] == 0 || _maze[posY + 1][posX + 2] == GAMEASTEROIDSCOLORINDEXSPACECRAFT;
    }
    return res;
}

void NG8x8RGBMatrixGameAsteroids::_doInitialize() {
    _score->setColorOff(GAMEASTEROIDSCOLORSCOREOFF);
    _score->setColorOn(GAMEASTEROIDSCOLORSCOREON);
    if (_logging) {
        char log[100];
        sprintf(log, "%s.Initialize", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameAsteroids::_doStartUp() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartUp", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameAsteroids::_doStartUpDone() {
    _cdm->clear();
    _score->setValue(_scoreCounter);
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartUp done", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameAsteroids::_doStartGame() {
    _resetMaze();
    _posXSpacecraft = GAMEASTEROIDSSTARTPOSX;
    _posYSpacecraft = GAMEASTEROIDSSTARTPOSY;
    _computeSpacecraft();
    _ownRender();
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameAsteroids::_doBreakGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s.BreakGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameAsteroids::_doContinueGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s.ContinueGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameAsteroids::_doFinishGame() {
    _cdm->clear();
    if (_logging) {
        char log[100];
        sprintf(log, "%s.FinishGame", _name);
        writeInfo(log);
    }
}

void NG8x8RGBMatrixGameAsteroids::_doProcessingLoop() {
    if (_gameStarted) {
        _ownJoystickLoop();
        if (_computeLaserbeam()) {
            _ownRender();
        }
        if ((millis() - _lastAsteroidsMove) > _gameNextStepDelay) {
            _computeAsteroids();
            _spawnAsteroid();
            _lastAsteroidsMove = millis();
            _ownRender();
        }
        if (_gameFinished) {
            _ownOutro();
        }
    }
}

void NG8x8RGBMatrixGameAsteroids::_ownRender() {
    colorRGB c;
    int value;
    _cdm->beginUpdate();
    for (int y = 0; y < GAMEASTEROIDSMAZESIZEY; y++) {
        for (int x = 0; x < GAMEASTEROIDSMAZESIZEX; x++) {
            value = abs(_maze[y][x]);
            if (value > 0) {
                c.red = globalAsteroidsColors[value - 1][0];
                c.green = globalAsteroidsColors[value - 1][1];
                c.blue = globalAsteroidsColors[value - 1][2];
                _cdm->drawPoint(x, y, c);
            } else {
                _cdm->drawPoint(x, y, COLOR_BLACK);
            }
        }
    }
    _score->setValue(_scoreCounter);
    _cdm->endUpdate();
}

void NG8x8RGBMatrixGameAsteroids::_ownOutro() {
    for (int i = 1; i < GAMEASTEROIDSMAZESIZEX + 2; i++) {
        _cdm->beginUpdate();
        _cdm->drawCircle(_posXSpacecraft + 1, _posYSpacecraft + 1, i - 1, COLOR_BLACK);
        _cdm->drawCircle(_posXSpacecraft + 1, _posYSpacecraft + 1, i, COLOR_RED);
        _score->setValue(_scoreCounter);
        _cdm->endUpdate();
        delay(GAMEASTEROIDSOUTRODELAY);
    }
}

void NG8x8RGBMatrixGameAsteroids::_ownJoystickLoop() {
    for (int i = 0; i < _joystickCount; i++) {
        if (_joysticks[i].joystick->hasLastMovement()) {
            switch(_joysticks[i].joystick->getLastMovement()) {
                case jmUp:
                    if (_posYSpacecraft > 0) {
                        _gameFinished = !_checkSpacecraft(_posXSpacecraft, _posYSpacecraft - 1);
                        if (!_gameFinished) {
                            _clearSpacecraft();
                            _posYSpacecraft--;
                            _computeSpacecraft();
                            _ownRender();
                        }
                    }
                    break;
                case jmDown:
                    if (_posYSpacecraft < GAMEASTEROIDSMAZESIZEY - 2) {
                        _gameFinished = !_checkSpacecraft(_posXSpacecraft, _posYSpacecraft + 1);
                        if (!_gameFinished) {
                            _clearSpacecraft();
                            _posYSpacecraft++;
                            _computeSpacecraft();
                            _ownRender();
                        }
                    }
                    break;
                case jmLeft:
                    break;
                case jmRight:
                    break;
                case jmFire:
                    _spawnLaserbeam();
                    _ownRender();
                    break;
            }
        }
    }
}
