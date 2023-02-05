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
            int checkRockyOffset = 0;
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
                            checkRockyOffset = -1;
                        }
                    }
                    if (x + 1 < GAMEBOULDERDASHMAZESIZEX) {
                        if (_maze[y + 1][x + 1] == 0 && _maze[y][x + 1] == 0) {
                            _maze[y][x] = 0;
                            _maze[y + 1][x + 1] = GAMEBOULDERDASHCOLORINDEXBOULDER;
                            checkRocky = true;
                            checkRockyOffset = 1;
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
                            checkRockyOffset = -1;
                        }
                    }
                    if (x + 1 < GAMEBOULDERDASHMAZESIZEX) {
                        if (_maze[y + 1][x + 1] == 0 && _maze[y][x + 1] == 0) {
                            _maze[y][x] = 0;
                            _maze[y + 1][x + 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND;
                            checkRocky = true;
                            checkRockyOffset = 1;
                        }
                    }
                }
            }
            if (checkRocky) {
                if ((y < (GAMEBOULDERDASHMAZESIZEY - 2)) && (_maze[y + 2][x + checkRockyOffset] == GAMEBOULDERDASHCOLORINDEXROCKY)) {
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

void NG8x8RGBMatrixGameBoulderdash::_computeNPC() {
    for (int y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
        for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            bool moved = false;
            switch(_maze[y][x]) {
                case GAMEBOULDERDASHCOLORINDEXNPCUP:
                    if (y > 0 && _maze[y - 1][x] == 0) {
                        _maze[y][x] = 0;
                        _maze[y - 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCUP;
                        moved = true;
                    } else {
                        if (_getYesOrNo() && x < (GAMEBOULDERDASHMAZESIZEX - 1)) {
                            if (_maze[y][x + 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x + 1] = -GAMEBOULDERDASHCOLORINDEXNPCRIGHT;
                                moved = true;
                            }
                        } else if (x > 0) {
                            if (_maze[y][x - 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x - 1] = -GAMEBOULDERDASHCOLORINDEXNPCLEFT;
                                moved = true;
                            }
                        }
                        if (!moved && y < (GAMEBOULDERDASHMAZESIZEY - 1)) {
                            if (_maze[y + 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCDOWN;
                                moved = true;
                            }
                        }
                    }
                    break;
                case GAMEBOULDERDASHCOLORINDEXNPCDOWN:
                    if (y < (GAMEBOULDERDASHMAZESIZEY - 1) && _maze[y + 1][x] == 0) {
                        _maze[y][x] = 0;
                        _maze[y + 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCDOWN;
                        moved = true;
                    } else {
                        if (_getYesOrNo() && x < (GAMEBOULDERDASHMAZESIZEX - 1)) {
                            if (_maze[y][x + 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x + 1] = -GAMEBOULDERDASHCOLORINDEXNPCRIGHT;
                                moved = true;
                            }
                        } else if (x > 0) {
                            if (_maze[y][x - 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x - 1] = -GAMEBOULDERDASHCOLORINDEXNPCLEFT;
                                moved = true;
                            }
                        }
                        if (!moved && y > 0) {
                            if (_maze[y - 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y - 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCUP;
                                moved = true;
                            }
                        }
                    }
                    break;
                case GAMEBOULDERDASHCOLORINDEXNPCLEFT:
                    if (x > 0 && _maze[y][x - 1] == 0) {
                        _maze[y][x] = 0;
                        _maze[y][x - 1] = -GAMEBOULDERDASHCOLORINDEXNPCLEFT;
                        moved = true;
                    } else {
                        if (_getYesOrNo() && y < (GAMEBOULDERDASHMAZESIZEY - 1)) {
                            if (_maze[y + 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCDOWN;
                                moved = true;
                            }
                        } else if (y > 0) {
                            if (_maze[y - 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y - 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCUP;
                                moved = true;
                            }
                        }
                        if (!moved && x < (GAMEBOULDERDASHMAZESIZEX - 1)) {
                            if (_maze[y][x + 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x + 1] = -GAMEBOULDERDASHCOLORINDEXNPCRIGHT;
                                moved = true;
                            }
                        }
                    }
                    break;
                case GAMEBOULDERDASHCOLORINDEXNPCRIGHT:
                    if (x < (GAMEBOULDERDASHMAZESIZEX - 1) && _maze[y][x + 1] == 0) {
                        _maze[y][x] = 0;
                        _maze[y][x + 1] = -GAMEBOULDERDASHCOLORINDEXNPCRIGHT;
                        moved = true;
                    } else {
                        if (_getYesOrNo() && y < (GAMEBOULDERDASHMAZESIZEY - 1)) {
                            if (_maze[y + 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCDOWN;
                                moved = true;
                            }
                        } else if (y > 0) {
                            if (_maze[y - 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y - 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCUP;
                                moved = true;
                            }
                        }
                        if (!moved && x > 0) {
                            if (_maze[y][x - 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x - 1] = -GAMEBOULDERDASHCOLORINDEXNPCLEFT;
                                moved = true;
                            }
                        }
                    }
                    break;
            }
        }
    }
    for (int y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
        for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            if (_maze[y][x] < 0) {
                _maze[y][x] = abs(_maze[y][x]);
            }
        }
    }
}

void NG8x8RGBMatrixGameBoulderdash::_initLevel() {
    _levelFinished = false;
    _levelRetry = false;
    switch(_level) {
        case GAMEBOULDERDASHLEVELONE:
            _posXRocky = random(0, 2);
            _posYRocky = random(0, 2);
            _calculateViewPos();
            _levelDiamonds = random(5, 10);
            _fuseStepDelay = GAMEBOULDERDASHLEVELONEFUSESTEPDELAY;
            _initLevelOneMaze();
            //_initLevelTestMaze();
            break;
        case GAMEBOULDERDASHLEVELTWO:
            _posXRocky = 9;
            _posYRocky = 15;
            _calculateViewPos();
            _levelDiamonds = 9;
            _fuseStepDelay = GAMEBOULDERDASHLEVELONEFUSESTEPDELAY;
            _initLevelTwoMaze();
            break;
        case GAMEBOULDERDASHLEVELTHREE:
            _posXRocky = 0;
            _posYRocky = 0;
            _calculateViewPos();
            _levelDiamonds = 0;
            _fuseStepDelay = GAMEBOULDERDASHLEVELONEFUSESTEPDELAY;
            _initLevelThreeMaze();
            break;
    }
    _renderRocky();
}

void NG8x8RGBMatrixGameBoulderdash::_initLevelTestMaze() {
    int x, y;
    // Dirt
    _generateDirtRect(0, 0, GAMEBOULDERDASHMAZESIZEX, GAMEBOULDERDASHMAZESIZEY);
    // Wall
    _generateWallRect(8, 3, 12, 6, GAMEBOULDERDASHCOLORINDEXVOID);
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
    // Rocky
    _computeRocky();
}

void NG8x8RGBMatrixGameBoulderdash::_initLevelOneMaze() {
    int x, y;
    // Dirt
    _generateDirtRect(0, 0, GAMEBOULDERDASHMAZESIZEX, GAMEBOULDERDASHMAZESIZEY);
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
    // Rocky
    _computeRocky();
}

void NG8x8RGBMatrixGameBoulderdash::_initLevelTwoMaze() {
    // Dirt
    _generateDirtRect(0, 0, GAMEBOULDERDASHMAZESIZEX - 1, GAMEBOULDERDASHMAZESIZEY - 1);
    // Void
    _generateVoidRect(10, 20, 17, 23);
    _generateVoidRect(21, 17, 23, 23);
    // Wall
    _generateWallLine(9, 20, 17, 20);
    _generateWallLine(9, 21, 9, 23);
    _generateWallLine(18, 16, 18, 23);
    _generateWallLine(20, 16, 20, 23);
    _generateWallLine(21, 16, 23, 16);
    _generateWallLine(16, 7, 20, 11);
    _generateWallLine(21, 11, 23, 9);
    _generateWall(23, 8);
    // Boulders
    _generateBoulderLine(3, 3, 4, 3);
    _generateBoulder(5, 2);
    _generateBoulderLine(6, 2, 6, 5);
    _generateBoulder(7, 5);
    _generateBoulderLine(8, 5, 8, 2);
    _generateBoulderLine(9, 2, 14, 2);
    _generateBoulderLine(15, 1, 15, 3);
    _generateBoulderLine(18, 3, 18, 5);
    _generateBoulder(19, 5);
    _generateBoulderLine(20, 5, 20, 2);
    _generateBoulderLine(18, 8, 20, 8);
    _generateBoulderLine(3, 8, 5, 8);
    _generateBoulderLine(3, 9, 3, 12);
    _generateBoulderLine(4, 12, 9, 12);
    _generateBoulderLine(4, 13, 4, 15);
    _generateBoulderLine(2, 18, 4, 16);
    _generateBoulderLine(8, 11, 8, 9);
    _generateBoulderLine(9, 9, 12, 9);
    _generateBoulderLine(12, 10, 12, 14);
    _generateBoulderLine(2, 22, 6, 18);
    _generateBoulder(2, 23);
    _generateBoulder(7, 18);
    _generateBoulderLine(11, 18, 11, 19);
    _generateBoulderLine(13, 17, 14, 17);
    _generateBoulderLine(15, 16, 17, 16);
    _generateBoulderLine(17, 17, 17, 19);
    _generateBoulder(19, 15);
    // Diamonds
    _generateDiamond(5, 3);
    _generateDiamond(7, 4);
    _generateDiamond(19, 4);
    _generateDiamond(14, 5);
    _generateDiamond(17, 7);
    _generateDiamond(10, 11);
    _generateDiamond(16, 19);
    _generateDiamond(6, 21);
    _generateDiamond(19, 23);
    // Rocky
    _computeRocky();
}

void NG8x8RGBMatrixGameBoulderdash::_initLevelThreeMaze() {
    // Dirt
    _generateDirtRect(0, 0, GAMEBOULDERDASHMAZESIZEX - 1, GAMEBOULDERDASHMAZESIZEY - 1);
    // Void
    // Wall
    _generateWallRect(2, 2, 6, 7, GAMEBOULDERDASHCOLORINDEXVOID);
    // NPC
    _generateNPC(5, 6);
    // Rocky
    _computeRocky();
}

void NG8x8RGBMatrixGameBoulderdash::_generateNPC(byte x, byte y) {
    _generateNPC(x, y, random(6, 10));
}

void NG8x8RGBMatrixGameBoulderdash::_generateNPC(byte x, byte y, byte kind) {
    _maze[y][x] = kind;
}

void NG8x8RGBMatrixGameBoulderdash::_generateDiamond(byte x, byte y) {
    _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND;
}

void NG8x8RGBMatrixGameBoulderdash::_generateBoulder(byte x, byte y) {
    _maze[y][x] = GAMEBOULDERDASHCOLORINDEXBOULDER;
}

void NG8x8RGBMatrixGameBoulderdash::_generateBoulderLine(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateLine(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXBOULDER);
}

void NG8x8RGBMatrixGameBoulderdash::_generateWall(byte x, byte y) {
    _maze[y][x] = GAMEBOULDERDASHCOLORINDEXWALL;
}

void NG8x8RGBMatrixGameBoulderdash::_generateWallLine(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateLine(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXWALL);
}

void NG8x8RGBMatrixGameBoulderdash::_generateLine(byte topX, byte topY, byte bottomX, byte bottomY, byte solid) {
    int dx =  abs(bottomX - topX);
    int sx = topX < bottomX ? 1 : -1;
    int dy = -abs(bottomY - topY);
    int sy = topY < bottomY ? 1 : -1;
    int err = dx + dy;
    int e2;
    for (;;) {
        _maze[topY][topX] = solid;
        if (topX == bottomX && topY == bottomY)
            break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; topX += sx; }
        if (e2 < dx) { err += dx; topY += sy; }
    }
}

void NG8x8RGBMatrixGameBoulderdash::_generateVoidRect(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateSolidRect(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXVOID);
}

void NG8x8RGBMatrixGameBoulderdash::_generateDirtRect(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateSolidRect(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXDIRT);
}

void NG8x8RGBMatrixGameBoulderdash::_generateSolidRect(byte topX, byte topY, byte bottomX, byte bottomY, byte solid) {
    for (int y = topY; y <= bottomY; y++) {
        for (int x = topX; x <= bottomX; x++) {
            _maze[y][x] = solid;
        }
    }
}

void NG8x8RGBMatrixGameBoulderdash::_generateWallRect(byte topX, byte topY, byte bottomX, byte bottomY, byte filler) {
    for (int y = topY; y <= bottomY; y++) {
        for (int x = topX; x <= bottomX; x++) {
            if (y == topY || y == bottomY || x == topX || x == bottomX) {
                _generateWall(x, y);
            } else {
                _maze[y][x] = filler;
            }
        }
    }
}

void NG8x8RGBMatrixGameBoulderdash::_clearRocky() {
    _maze[_posYRocky][_posXRocky] = GAMEBOULDERDASHCOLORINDEXVOID;
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
            if ((millis() - _lastNPCMove) > GAMEBOULDERDASHSNPCDELAY) {
                _computeNPC();
                _ownRender();
                _lastNPCMove = millis();
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
