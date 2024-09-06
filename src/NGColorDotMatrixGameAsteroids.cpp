//
//  NGColorDotMatrixGameAsteroids.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 07.01.23.
//

#include "NGColorDotMatrixGameAsteroids.h"

NGColorDotMatrixGameAsteroids::NGColorDotMatrixGameAsteroids() {
    _create("Asteroids");
    _scoreDigitPosX = GAMEASTEROIDSSCOREDIGITXPOS;
    _scoreDirection = GAMEASTEROIDSSCOREDIRECTION;
    _gameToggleMode = gtmBreakContinue;
    _autoRestartGame = true;
    _gameFinishedDelay = GAMEASTEROIDSFINISHDELAY;
    _pointCounterAnimationDelay = GAMEASTEROIDSOUTRODELAY;
}

void NGColorDotMatrixGameAsteroids::_resetMaze() {
    for (int y = 0; y < _maxGameAsteroidsY; y++) {
        for (int x = 0; x < _maxGameAsteroidsX; x++) {
            _maze[y][x] = 0;
        }
    }
}

bool NGColorDotMatrixGameAsteroids::_isColorIndexSpacecraft(int index) {
    return (index == GAMEASTEROIDSCOLORINDEXSPACECRAFT01 || index == GAMEASTEROIDSCOLORINDEXSPACECRAFT02);
}

void NGColorDotMatrixGameAsteroids::_computeAsteroids() {
    for (int y = 0; y < _maxGameAsteroidsY; y++) {
        for (int x = 0; x < _maxGameAsteroidsX; x++) {
            if (_maze[y][x] == GAMEASTEROIDSCOLORINDEXASTEROID) {
                _maze[y][x] = 0;
                if (x > 0) {
                    _gameFinished = _isColorIndexSpacecraft(_maze[y][x - 1]);
                    if (!_gameFinished) {
                        _maze[y][x - 1] = GAMEASTEROIDSCOLORINDEXASTEROID;
                    } else {
                        return;
                    }
                } else {
                    _asteroidsLost++;
                    if (_asteroidsLost > GAMEASTEROIDSMAXLOST) {
                        _asteroidsLost = 0;
                        if (_scoreCounter > 0) {
                            _scoreCounter--;
                        }
                    }
                }
            }
        }
    }
}

bool NGColorDotMatrixGameAsteroids::_computeLaserbeam() {
    bool res = false;
    for (int y = 0; y < _maxGameAsteroidsY; y++) {
        for (int x = 0; x < _maxGameAsteroidsX; x++) {
            if (_maze[y][x] == GAMEASTEROIDSCOLORINDEXLASERBEAM) {
                _maze[y][x] = 0;
                if ((x + 1) < _maxGameAsteroidsX) {
                    if (_maze[y][x + 1] == GAMEASTEROIDSCOLORINDEXASTEROID) {
                        _scoreCounter++;
                        _asteroidsLost = 0;
                        if (_scoreCounter % 10 == 0) {
                            _gameNextStepDelay = _gameNextStepDelay - (GAMEASTEROIDSMOVEDELAY / 10);
                            if (_gameNextStepDelay < 0) {
                                _gameNextStepDelay = 0;
                            }
                        }
                        _maze[y][x + 1] = 0;
                    } else {
                        _maze[y][x + 1] = -GAMEASTEROIDSCOLORINDEXLASERBEAM;
                    }
                }
                res = true;
            }
        }
    }
    if (res) {
        for (int y = 0; y < _maxGameAsteroidsY; y++) {
            for (int x = 0; x < _maxGameAsteroidsX; x++) {
                if (_maze[y][x] == -GAMEASTEROIDSCOLORINDEXLASERBEAM) {
                    _maze[y][x] = abs(_maze[y][x]);
                }
            }
        }
    }
    return res;
}

void NGColorDotMatrixGameAsteroids::_spawnLaserbeam() {
    if (millis() - _lastSpawnLaserbeam > GAMEASTEROIDSLASERBEAMSPAWNDELAY) {
        _maze[_posYSpacecraft + 1][_posXSpacecraft + 3] = GAMEASTEROIDSCOLORINDEXLASERBEAM;
        _lastSpawnLaserbeam = millis();
    }
}

void NGColorDotMatrixGameAsteroids::_spawnAsteroid() {
    byte base = 3;
    switch(_gameMode) {
        case gmBig:
            base = 2;
            break;
    }
    if ((random(0, 10) % base) == 0) {
        _maze[random(0, _maxGameAsteroidsY - 1)][_maxGameAsteroidsX - 1] = GAMEASTEROIDSCOLORINDEXASTEROID;
    }
}

void NGColorDotMatrixGameAsteroids::_clearSpacecraft() {
    _maze[_posYSpacecraft][_posXSpacecraft + 1] = 0;
    if (_hasSprite(GAMEASTEROIDSCOLORINDEXSPACECRAFT01)) {
        _maze[_posYSpacecraft][_posXSpacecraft] = 0;
        _maze[_posYSpacecraft][_posXSpacecraft + 2] = 0;
    }
    _maze[_posYSpacecraft + 1][_posXSpacecraft] = 0;
    _maze[_posYSpacecraft + 1][_posXSpacecraft + 1] = 0;
    _maze[_posYSpacecraft + 1][_posXSpacecraft + 2] = 0;
}

void NGColorDotMatrixGameAsteroids::_computeSpacecraft() {
    _maze[_posYSpacecraft][_posXSpacecraft + 1] = GAMEASTEROIDSCOLORINDEXSPACECRAFT01;
    if (_hasSprite(GAMEASTEROIDSCOLORINDEXSPACECRAFT01)) {
        _maze[_posYSpacecraft][_posXSpacecraft] = GAMEASTEROIDSCOLORINDEXSPACECRAFT02;
        _maze[_posYSpacecraft][_posXSpacecraft + 2] = GAMEASTEROIDSCOLORINDEXSPACECRAFT02;
    }
    _maze[_posYSpacecraft + 1][_posXSpacecraft] = GAMEASTEROIDSCOLORINDEXSPACECRAFT02;
    _maze[_posYSpacecraft + 1][_posXSpacecraft + 1] = GAMEASTEROIDSCOLORINDEXSPACECRAFT02;
    _maze[_posYSpacecraft + 1][_posXSpacecraft + 2] = GAMEASTEROIDSCOLORINDEXSPACECRAFT02;
}

bool NGColorDotMatrixGameAsteroids::_checkSpacecraft(byte posX, byte posY) {
    bool res = _maze[posY][posX + 1] == 0 || _isColorIndexSpacecraft(_maze[posY][posX + 1]);
    if (res) {
        res = _maze[posY + 1][posX] == 0 || _isColorIndexSpacecraft(_maze[posY + 1][posX]);
    }
    if (res) {
        res = _maze[posY + 1][posX + 1] == 0 || _isColorIndexSpacecraft(_maze[posY + 1][posX + 1]);
    }
    if (res) {
        res = _maze[posY + 1][posX + 2] == 0 || _isColorIndexSpacecraft(_maze[posY + 1][posX + 2]);
    }
    return res;
}

void NGColorDotMatrixGameAsteroids::_doInitialize() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s Initialize...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameAsteroids::_doStartUp() {
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

void NGColorDotMatrixGameAsteroids::_doStartUpDone() {
    _ipc->clear();
    _score->setColorOff(GAMEASTEROIDSCOLORSCOREOFF);
    _score->setColorOn(GAMEASTEROIDSCOLORSCOREON);
    _score->setValue(_scoreCounter);
    if (_logging) {
        char log[100];
        sprintf(log, "%s StartUp done", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameAsteroids::_doStartGame() {
    _resetMaze();
    _gameNextStepDelay = GAMEASTEROIDSMOVEDELAY;
    switch(_gameMode) {
        case gmNormal:
            _gameNextStepDelay = _gameNextStepDelay * 0.75;
            break;
        case gmBig:
            _gameNextStepDelay = _gameNextStepDelay * 0.5;
            break;
    }
    _posXSpacecraft = (_maxGameAsteroidsX - 8) * 0.25;
    _posYSpacecraft = random(3, _maxGameAsteroidsY - 3);
    _computeSpacecraft();
    _ownRender();
    if (_logging) {
        char log[100];
        sprintf(log, "%s Start...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameAsteroids::_doBreakGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s Break...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameAsteroids::_doContinueGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s Continue...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameAsteroids::_doFinishGame() {
    _ipc->clear();
    if (_logging) {
        char log[100];
        sprintf(log, "%s Finish...", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameAsteroids::_doProcessingLoop() {
    bool doRender = false;
    byte res;
    if (_gameStarted) {
        res = _ownJoystickLoop();
        doRender = res > 0;
        if (res < 2 && _computeLaserbeam()) {
            doRender = true;
        }
        if ((millis() - _lastAsteroidsMove) > _gameNextStepDelay) {
            _computeAsteroids();
            _spawnAsteroid();
            _lastAsteroidsMove = millis();
            doRender = true;
        }
        if (doRender) {
            _ownRender();
        }
        if (_gameFinished) {
            _ownOutro();
        }
    }
}

void NGColorDotMatrixGameAsteroids::_ownRender() {
    colorRGB c;
    int value;
    _ipc->beginUpdate();
    for (int y = 0; y < _maxGameAsteroidsY; y++) {
        for (int x = 0; x < _maxGameAsteroidsX; x++) {
            value = abs(_maze[y][x]);
            if (value > 0) {
                c.red = globalAsteroidsColors[value - 1][0];
                c.green = globalAsteroidsColors[value - 1][1];
                c.blue = globalAsteroidsColors[value - 1][2];
                if (_hasSprite(value)) {
                    _setSpriteColor(value, c);
                    _renderSprite(value, x, y);
                } else {
                    _ipc->drawPoint(x, y, c);
                }
            } else {
                _ipc->clearPoint(x, y);
            }
        }
    }
    _score->setValue(_scoreCounter);
    _ipc->endUpdate();
}

void NGColorDotMatrixGameAsteroids::_ownIntro() {
    int asteroids = 5;
    byte offsetX = (_maxGameAsteroidsX - 8) * 0.25;
    byte offsetY = (_maxGameAsteroidsY - 8) * 0.5;
    switch(_gameMode) {
        case gmNormal:
            asteroids = asteroids * 2;
            break;
        case gmBig:
            asteroids = asteroids * 3;
            break;
    }
    _ipc->beginUpdate();
    _ipc->clear();
    colorRGB c;
    c.red = globalAsteroidsColors[GAMEASTEROIDSCOLORINDEXASTEROID - 1][0];
    c.green = globalAsteroidsColors[GAMEASTEROIDSCOLORINDEXASTEROID - 1][1];
    c.blue = globalAsteroidsColors[GAMEASTEROIDSCOLORINDEXASTEROID - 1][2];
    if (_hasSprite(GAMEASTEROIDSCOLORINDEXASTEROID)) {
        _setSpriteColor(GAMEASTEROIDSCOLORINDEXASTEROID, c);
        for (int i = 0; i < asteroids; i++) {
            _renderSprite(GAMEASTEROIDSCOLORINDEXASTEROID, random(2, _maxGameAsteroidsX), random(0, _maxGameAsteroidsY));
        }
    } else {
        for (int i = 0; i < asteroids; i++) {
            _ipc->drawPoint(random(2, _maxGameAsteroidsX), random(0, _maxGameAsteroidsY), c);
        }
    }
    c.red = globalAsteroidsColors[GAMEASTEROIDSCOLORINDEXSPACECRAFT01 - 1][0];
    c.green = globalAsteroidsColors[GAMEASTEROIDSCOLORINDEXSPACECRAFT01 - 1][1];
    c.blue = globalAsteroidsColors[GAMEASTEROIDSCOLORINDEXSPACECRAFT01 - 1][2];
    if (_hasSprite(GAMEASTEROIDSCOLORINDEXSPACECRAFT01)) {
        _setSpriteColor(GAMEASTEROIDSCOLORINDEXSPACECRAFT01, c);
        _renderSprite(GAMEASTEROIDSCOLORINDEXSPACECRAFT01, 2 + offsetX, 2);
        _beamOffset = 1;
    } else {
        _ipc->drawPoint(1 + offsetX, 2 + offsetY, c);
        _ipc->drawPoint(0 + offsetX, 3 + offsetY, c);
        _ipc->drawPoint(1 + offsetX, 3 + offsetY, c);
        _ipc->drawPoint(2 + offsetX, 3 + offsetY, c);
    }
    _ipc->endUpdate();
    _lastStartUpAnimationStep = millis();
}

void NGColorDotMatrixGameAsteroids::_ownIntroAnimation() {
    _startUpDone = _startUpAnimationStep >= GAMEASTEROIDSINTROLASERBEAMTIMES;
    if (!_startUpDone) {
        if (millis() - _lastStartUpAnimationStep > GAMEASTEROIDSINTRODELAY) {
            long lastStartUpAnimationStep;
            byte offsetX = (_maxGameAsteroidsX - 8) * 0.25;
            byte offsetY = (_maxGameAsteroidsY - 8) * 0.5;
            colorRGB c;
            c.red = globalAsteroidsColors[GAMEASTEROIDSCOLORINDEXLASERBEAM - 1][0];
            c.green = globalAsteroidsColors[GAMEASTEROIDSCOLORINDEXLASERBEAM - 1][1];
            c.blue = globalAsteroidsColors[GAMEASTEROIDSCOLORINDEXLASERBEAM - 1][2];
            for (int x = 3 + _beamOffset; x < _maxGameAsteroidsX; x++) {
                _ipc->drawPoint(x + offsetX, 3 + offsetY, c);
                if (_introShotDelay > 0) {
                    lastStartUpAnimationStep = millis();
                    while (millis() - lastStartUpAnimationStep < _introShotDelay) {
                        if (_soundMachine != nullptr) {
                            _soundMachine->processingLoop();
                        }
                    }
                }
                _ipc->clearPoint(x + offsetX, 3 + offsetY);
            }
            _startUpAnimationStep++;
            _lastStartUpAnimationStep = millis();
        }
    }
}

void NGColorDotMatrixGameAsteroids::_ownOutro() {
    for (int i = 1; i < _maxGameAsteroidsX + 2; i++) {
        _ipc->beginUpdate();
        _ipc->clearCircle(_posXSpacecraft + 1, _posYSpacecraft + 1, i - 1);
        _ipc->drawCircle(_posXSpacecraft + 1, _posYSpacecraft + 1, i, GAMEASTEROIDSCOLOROUTRO);
        _score->setValue(_scoreCounter);
        _ipc->endUpdate();
        delay(GAMEASTEROIDSOUTRODELAY);
    }
    _ipc->clear();
    _pointCounter->setColor(GAMEASTEROIDSCOLOROUTRO);
    _pointCounter->setCounter(_scoreCounter, true);
    long start = millis();
    while (millis() - start < GAMEASTEROIDSOUTRODPOINTCOUNTERDELAY * _pointCounter->getCurrentMaxDigits()) {
        _pointCounter->processingLoop();
    }
}

byte NGColorDotMatrixGameAsteroids::_ownJoystickLoop() {
    byte res = 0;
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
                            res = 1;
                        }
                    }
                    break;
                case jmDown:
                    if (_posYSpacecraft < _maxGameAsteroidsY - 2) {
                        _gameFinished = !_checkSpacecraft(_posXSpacecraft, _posYSpacecraft + 1);
                        if (!_gameFinished) {
                            _clearSpacecraft();
                            _posYSpacecraft++;
                            _computeSpacecraft();
                            res = 1;
                        }
                    }
                    break;
                case jmLeft:
                    if (_posXSpacecraft > 0) {
                        _gameFinished = !_checkSpacecraft(_posXSpacecraft - 1, _posYSpacecraft);
                        if (!_gameFinished) {
                            _clearSpacecraft();
                            _posXSpacecraft--;
                            _computeSpacecraft();
                            res = 1;
                        }
                    }
                    break;
                case jmRight:
                    if (_posXSpacecraft < _maxGameAsteroidsX - 3) {
                        _gameFinished = !_checkSpacecraft(_posXSpacecraft + 1, _posYSpacecraft);
                        if (!_gameFinished) {
                            _clearSpacecraft();
                            _posXSpacecraft++;
                            _computeSpacecraft();
                            res = 1;
                        }
                    }
                    break;
                case jmFire:
                    _spawnLaserbeam();
                    res = 2;
                    break;
            }
        }
    }
    return res;
}

void NGColorDotMatrixGameAsteroids::setIntroShotDelay(int shotdelay) {
    _introShotDelay = shotdelay;
}

void NGColorDotMatrixGameAsteroids::registerColorDotMatrix(NGIPaintableComponent *ipc) {
    _scoreDigitPosY = ipc->getWidth() - 1;
    _scoreDigits = ipc->getWidth();
    NGCustomColorDotMatrixGame::registerColorDotMatrix(ipc);
    _maxGameAsteroidsX = ipc->getWidth();
    _maxGameAsteroidsY = ipc->getHeight() - 1;
}
