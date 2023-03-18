//
//  NGColorDotMatrixGameBoulderdash.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 09.01.23.
//

#include "NGColorDotMatrixGameBoulderdash.h"

NGColorDotMatrixGameBoulderdash::NGColorDotMatrixGameBoulderdash() {
    _create("Boulderdash");
    _scoreDigits = GAMEBOULDERDASHSCOREDIGITS;
    _scoreDigitPosX = GAMEBOULDERDASHSCOREDIGITXPOS;
    _scoreDigitPosY = GAMEBOULDERDASHSCOREDIGITYPOS;
    _scoreDirection = GAMEBOULDERDASHSCOREDIRECTION;
    _gameToggleMode = gtmBreakContinue;
    _autoRestartGame = true;
    _playStartUpSoundConcurrently = true;
    _gameFinishedDelay = GAMEBOULDERDASHFINISHDELAY;
    _gameNextStepDelay = GAMEBOULDERDASHGRAVITYDELAY;
}

void NGColorDotMatrixGameBoulderdash::registerColorDotMatrix(NGIPaintableComponent *ipc) {
    NGCustomColorDotMatrixGame::registerColorDotMatrix(ipc);
    _lives = new NGColorDotMatrixBinaryDigit(_ipc, GAMEBOULDERDASHLIVESDIGITS, GAMEBOULDERDASHLIVESDIRECTION, GAMEBOULDERDASHLIVESDIGITXPOS, GAMEBOULDERDASHLIVESDIGITYPOS);
    _fuse = new NGColorDotMatrixFuse(_ipc, GAMEBOULDERDASHFUSEARITY);
}

void NGColorDotMatrixGameBoulderdash::_resetMaze() {
    for (int y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
        for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            _maze[y][x] = 0;
        }
    }
}

bool NGColorDotMatrixGameBoulderdash::_isColorIndexBomb(int index) {
    return (index >= GAMEBOULDERDASHCOLORINDEXBOMBINACTIVE) && (index <= GAMEBOULDERDASHCOLORINDEXBOMBACTIVE09);
}

bool NGColorDotMatrixGameBoulderdash::_isColorIndexDiamond(int index) {
    return (index == GAMEBOULDERDASHCOLORINDEXDIAMOND01 || index == GAMEBOULDERDASHCOLORINDEXDIAMOND02);
}

bool NGColorDotMatrixGameBoulderdash::_isColorIndexNPC(int index) {
    return (index >= GAMEBOULDERDASHCOLORINDEXNPCUP) && (index <= GAMEBOULDERDASHCOLORINDEXNPCRIGHT);
}

void NGColorDotMatrixGameBoulderdash::_computeGravity() {
    for (int y = GAMEBOULDERDASHMAZESIZEY - 2; y >= 0; y--) {
        for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            bool checkRocky = false;
            int checkRockyOffset = 0;
            switch (_maze[y][x]) {
                case GAMEBOULDERDASHCOLORINDEXBOULDER:
                    if (_maze[y + 1][x] == 0) {
                        _maze[y][x] = 0;
                        _maze[y + 1][x] = GAMEBOULDERDASHCOLORINDEXBOULDER;
                        checkRocky = true;
                    } else if ((_maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXBOULDER || _isColorIndexDiamond(_maze[y + 1][x])) || _isColorIndexBomb(_maze[y + 1][x])) {
                        if (x - 1 >= 0) {
                            if (_maze[y + 1][x - 1] == 0 && _maze[y][x - 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXBOULDER;
                                checkRocky = true;
                                checkRockyOffset = -1;
                            }
                        }
                        if (!checkRocky && (x + 1 < GAMEBOULDERDASHMAZESIZEX)) {
                            if (_maze[y + 1][x + 1] == 0 && _maze[y][x + 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x + 1] = GAMEBOULDERDASHCOLORINDEXBOULDER;
                                checkRocky = true;
                                checkRockyOffset = 1;
                            }
                        }
                    } else if (_isColorIndexNPC(_maze[y + 1][x])) {
                        _maze[y + 1][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        if (x > 0 && _maze[y + 1][x - 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (x < GAMEBOULDERDASHMAZESIZEX - 1 && _maze[y + 1][x + 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (y < GAMEBOULDERDASHMAZESIZEY - 2 && _maze[y + 2][x] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        }
                    }
                    break;
                case GAMEBOULDERDASHCOLORINDEXDIAMOND01:
                case GAMEBOULDERDASHCOLORINDEXDIAMOND02:
                    if (_maze[y + 1][x] == 0) {
                        _maze[y][x] = 0;
                        _maze[y + 1][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        checkRocky = true;
                    } else if ((_maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXBOULDER || _isColorIndexDiamond(_maze[y + 1][x])) || _isColorIndexBomb(_maze[y + 1][x])) {
                        if (x - 1 >= 0) {
                            if (_maze[y + 1][x - 1] == 0 && _maze[y][x - 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                                checkRocky = true;
                                checkRockyOffset = -1;
                            }
                        }
                        if (!checkRocky && (x + 1 < GAMEBOULDERDASHMAZESIZEX)) {
                            if (_maze[y + 1][x + 1] == 0 && _maze[y][x + 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x + 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                                checkRocky = true;
                                checkRockyOffset = 1;
                            }
                        }
                    } else if (_isColorIndexNPC(_maze[y + 1][x])) {
                        _maze[y + 1][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        if (x > 0 && _maze[y + 1][x - 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (x < GAMEBOULDERDASHMAZESIZEX - 1 && _maze[y + 1][x + 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (y < GAMEBOULDERDASHMAZESIZEY - 2 && _maze[y + 2][x] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        }
                    }
                    break;
                case GAMEBOULDERDASHCOLORINDEXBOMBINACTIVE:
                case GAMEBOULDERDASHCOLORINDEXBOMBACTIVE01:
                case GAMEBOULDERDASHCOLORINDEXBOMBACTIVE02:
                case GAMEBOULDERDASHCOLORINDEXBOMBACTIVE03:
                case GAMEBOULDERDASHCOLORINDEXBOMBACTIVE04:
                case GAMEBOULDERDASHCOLORINDEXBOMBACTIVE05:
                case GAMEBOULDERDASHCOLORINDEXBOMBACTIVE06:
                case GAMEBOULDERDASHCOLORINDEXBOMBACTIVE07:
                case GAMEBOULDERDASHCOLORINDEXBOMBACTIVE08:
                case GAMEBOULDERDASHCOLORINDEXBOMBACTIVE09:
                    int index = _maze[y][x];
                    if (_maze[y + 1][x] == 0) {
                        _maze[y][x] = 0;
                        _maze[y + 1][x] = index;
                        checkRocky = true;
                    } else if ((_maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXBOULDER || _isColorIndexDiamond(_maze[y + 1][x])) || _isColorIndexBomb(_maze[y + 1][x])) {
                        if (x - 1 >= 0) {
                            if (_maze[y + 1][x - 1] == 0 && _maze[y][x - 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x - 1] = index;
                                checkRocky = true;
                                checkRockyOffset = -1;
                            }
                        }
                        if (!checkRocky && (x + 1 < GAMEBOULDERDASHMAZESIZEX)) {
                            if (_maze[y + 1][x + 1] == 0 && _maze[y][x + 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x + 1] = index;
                                checkRocky = true;
                                checkRockyOffset = 1;
                            }
                        }
                    }
                    break;
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

void NGColorDotMatrixGameBoulderdash::_computeNPC() {
    bool rockyCatched = false;
    for (int y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
        for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            bool moved = false;
            rockyCatched = false;
            switch(_maze[y][x]) {
                case GAMEBOULDERDASHCOLORINDEXNPCUP:
                    if (x < (GAMEBOULDERDASHMAZESIZEX - 1) && _maze[y][x + 1] == 0) {
                        _maze[y][x] = 0;
                        _maze[y][x + 1] = -GAMEBOULDERDASHCOLORINDEXNPCUP;
                        moved = true;
                    } else if (x < (GAMEBOULDERDASHMAZESIZEX - 1) && _maze[y][x + 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else if (y > 0 && _maze[y - 1][x] == 0) {
                        _maze[y][x] = 0;
                        _maze[y - 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCUP;
                        moved = true;
                    } else if (y > 0 && _maze[y - 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else {
                        if (_getYesOrNo() && x < (GAMEBOULDERDASHMAZESIZEX - 1)) {
                            if (_maze[y][x + 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x + 1] = -GAMEBOULDERDASHCOLORINDEXNPCRIGHT;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y][x + 1] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        } else if (x > 0) {
                            if (_maze[y][x - 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x - 1] = -GAMEBOULDERDASHCOLORINDEXNPCLEFT;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y][x - 1] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        }
                        if (!moved && y < (GAMEBOULDERDASHMAZESIZEY - 1)) {
                            if (_maze[y + 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCDOWN;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        }
                    }
                    break;
                case GAMEBOULDERDASHCOLORINDEXNPCDOWN:
                    if (x > 0 && _maze[y][x - 1] == 0) {
                        _maze[y][x] = 0;
                        _maze[y][x - 1] = -GAMEBOULDERDASHCOLORINDEXNPCDOWN;
                        moved = true;
                    } else if (x > 0 && _maze[y][x - 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else if (y < (GAMEBOULDERDASHMAZESIZEY - 1) && _maze[y + 1][x] == 0) {
                        _maze[y][x] = 0;
                        _maze[y + 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCDOWN;
                        moved = true;
                    } else if (y < (GAMEBOULDERDASHMAZESIZEY - 1) && _maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else {
                        if (_getYesOrNo() && x < (GAMEBOULDERDASHMAZESIZEX - 1)) {
                            if (_maze[y][x + 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x + 1] = -GAMEBOULDERDASHCOLORINDEXNPCRIGHT;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y][x + 1] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        } else if (x > 0) {
                            if (_maze[y][x - 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x - 1] = -GAMEBOULDERDASHCOLORINDEXNPCLEFT;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y][x - 1] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        }
                        if (!moved && y > 0) {
                            if (_maze[y - 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y - 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCUP;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y - 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        }
                    }
                    break;
                case GAMEBOULDERDASHCOLORINDEXNPCLEFT:
                    if (y > 0 && _maze[y - 1][x] == 0) {
                        _maze[y][x] = 0;
                        _maze[y - 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCLEFT;
                        moved = true;
                    } else if (y > 0 && _maze[y - 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else if (x > 0 && _maze[y][x - 1] == 0) {
                        _maze[y][x] = 0;
                        _maze[y][x - 1] = -GAMEBOULDERDASHCOLORINDEXNPCLEFT;
                        moved = true;
                    } else if (x > 0 && _maze[y][x - 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else {
                        if (_getYesOrNo() && y < (GAMEBOULDERDASHMAZESIZEY - 1)) {
                            if (_maze[y + 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCDOWN;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        } else if (y > 0) {
                            if (_maze[y - 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y - 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCUP;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y - 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        }
                        if (!moved && x < (GAMEBOULDERDASHMAZESIZEX - 1)) {
                            if (_maze[y][x + 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x + 1] = -GAMEBOULDERDASHCOLORINDEXNPCRIGHT;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y][x + 1] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        }
                    }
                    break;
                case GAMEBOULDERDASHCOLORINDEXNPCRIGHT:
                    if (y < (GAMEBOULDERDASHMAZESIZEY - 1) && _maze[y + 1][x] == 0) {
                        _maze[y][x] = 0;
                        _maze[y + 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCRIGHT;
                        moved = true;
                    } else if (y < (GAMEBOULDERDASHMAZESIZEY - 1) && _maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else if (x < (GAMEBOULDERDASHMAZESIZEX - 1) && _maze[y][x + 1] == 0) {
                        _maze[y][x] = 0;
                        _maze[y][x + 1] = -GAMEBOULDERDASHCOLORINDEXNPCRIGHT;
                        moved = true;
                    } else if (x < (GAMEBOULDERDASHMAZESIZEX - 1) && _maze[y][x + 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else {
                        if (_getYesOrNo() && y < (GAMEBOULDERDASHMAZESIZEY - 1)) {
                            if (_maze[y + 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y + 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCDOWN;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        } else if (y > 0) {
                            if (_maze[y - 1][x] == 0) {
                                _maze[y][x] = 0;
                                _maze[y - 1][x] = -GAMEBOULDERDASHCOLORINDEXNPCUP;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y - 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        }
                        if (!moved && x > 0) {
                            if (_maze[y][x - 1] == 0) {
                                _maze[y][x] = 0;
                                _maze[y][x - 1] = -GAMEBOULDERDASHCOLORINDEXNPCLEFT;
                                moved = true;
                            } else {
                                rockyCatched = _maze[y][x - 1] == GAMEBOULDERDASHCOLORINDEXROCKY;
                            }
                        }
                    }
                    break;
            }
            if (rockyCatched) {
                _livesCounter--;
                _gameFinished = _livesCounter == 0;
                if (!_gameFinished) {
                    _levelRetry = true;
                }
                return;
            }
        }
    }
    if (!rockyCatched) {
        for (int y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
            for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
                if (_maze[y][x] < 0) {
                    if (y > 0 && _maze[y - 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else if (y < GAMEBOULDERDASHMAZESIZEY - 1 && _maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else if (x > 0 && _maze[y][x - 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else if (x < GAMEBOULDERDASHMAZESIZEX - 1 && _maze[y][x + 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    }
                }
                if (rockyCatched) {
                    _livesCounter--;
                    _gameFinished = _livesCounter == 0;
                    if (!_gameFinished) {
                        _levelRetry = true;
                    }
                    return;
                }
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

void NGColorDotMatrixGameBoulderdash::_computeLava() {
    for (int y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
        for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            bool rockyCatched = false;
            switch(_maze[y][x]) {
                case GAMEBOULDERDASHCOLORINDEXLAVA:
                    if (x > 0 && (_maze[y][x - 1] == 0 || _isColorIndexDiamond(_maze[y][x - 1]))) {
                        _maze[y][x - 1] = -GAMEBOULDERDASHCOLORINDEXLAVA;
                    } else if (x > 0 && _maze[y][x - 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else if (x > 0 && (_maze[y][x - 1] == 0 || _isColorIndexNPC(_maze[y][x - 1]))) {
                        _maze[y][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        if (x > 0 && _maze[y + 1][x - 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (x < GAMEBOULDERDASHMAZESIZEX - 1 && _maze[y + 1][x + 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (y < GAMEBOULDERDASHMAZESIZEY - 2 && _maze[y + 2][x] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        }
                    }
                    if (x < (GAMEBOULDERDASHMAZESIZEX - 1) && (_maze[y][x + 1] == 0 || _isColorIndexDiamond(_maze[y][x + 1]))) {
                        _maze[y][x + 1] = -GAMEBOULDERDASHCOLORINDEXLAVA;
                    } else if (x < (GAMEBOULDERDASHMAZESIZEX - 1) && _maze[y][x + 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else if (x < (GAMEBOULDERDASHMAZESIZEX - 1) && (_maze[y][x + 1] == 0 || _isColorIndexNPC(_maze[y][x + 1]))) {
                        _maze[y][x + 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        if (x > 0 && _maze[y + 1][x - 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (x < GAMEBOULDERDASHMAZESIZEX - 1 && _maze[y + 1][x + 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (y < GAMEBOULDERDASHMAZESIZEY - 2 && _maze[y + 2][x] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        }
                    }
                    if (y > 0 && (_maze[y - 1][x] == 0 || _isColorIndexDiamond(_maze[y - 1][x]))) {
                        _maze[y - 1][x] = -GAMEBOULDERDASHCOLORINDEXLAVA;
                    } else if (y > 0 && _maze[y - 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else if (y > 0 && (_maze[y - 1][x] == 0 || _isColorIndexNPC(_maze[y - 1][x]))) {
                        _maze[y - 1][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        if (x > 0 && _maze[y + 1][x - 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (x < GAMEBOULDERDASHMAZESIZEX - 1 && _maze[y + 1][x + 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (y < GAMEBOULDERDASHMAZESIZEY - 2 && _maze[y + 2][x] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        }
                    }
                    if (y < (GAMEBOULDERDASHMAZESIZEY - 1) && (_maze[y + 1][x] == 0 || _isColorIndexDiamond(_maze[y + 1][x]))) {
                        _maze[y + 1][x] = -GAMEBOULDERDASHCOLORINDEXLAVA;
                    } else if (y < (GAMEBOULDERDASHMAZESIZEY - 1) && _maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockyCatched = true;
                    } else if (y < (GAMEBOULDERDASHMAZESIZEY - 1) && (_maze[y + 1][x] == 0 || _isColorIndexNPC(_maze[y + 1][x]))) {
                        _maze[y + 1][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        if (x > 0 && _maze[y + 1][x - 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (x < GAMEBOULDERDASHMAZESIZEX - 1 && _maze[y + 1][x + 1] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else if (y < GAMEBOULDERDASHMAZESIZEY - 2 && _maze[y + 2][x] == 0 && _getYesOrNo()) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        }
                    }
                    break;
            }
            if (rockyCatched) {
                _livesCounter--;
                _gameFinished = _livesCounter == 0;
                if (!_gameFinished) {
                    _levelRetry = true;
                }
                return;
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

void NGColorDotMatrixGameBoulderdash::_initLevel() {
    _levelFinished = false;
    _doorEntered = false;
    _levelRetry = false;
    _fuseValue = GAMEBOULDERDASHMAXFUSE;
    switch(_level) {
        case GAMEBOULDERDASHLEVELONE:
            _posXRocky = random(0, 2);
            _posYRocky = random(0, 2);
            _calculateViewPos();
            _levelDiamonds = random(5, 10);
            _fuseStepDelay = GAMEBOULDERDASHLEVELONEFUSESTEPDELAY;
            if (!_testMode) {
                _initLevelOneMaze();
            } else {
                _initLevelTestMaze();
            }
            break;
        case GAMEBOULDERDASHLEVELTWO:
            _posXRocky = 9;
            _posYRocky = 15;
            _calculateViewPos();
            _levelDiamonds = 9;
            _fuseStepDelay = GAMEBOULDERDASHLEVELTWOFUSESTEPDELAY;
            _initLevelTwoMaze();
            break;
        case GAMEBOULDERDASHLEVELTHREE:
            _posXRocky = 3;
            _posYRocky = 0;
            _calculateViewPos();
            _levelDiamonds = 11;
            _fuseStepDelay = GAMEBOULDERDASHLEVELTHREEFUSESTEPDELAY;
            _initLevelThreeMaze();
            break;
        case GAMEBOULDERDASHLEVELFOUR:
            _posXRocky = 0;
            _posYRocky = 0;
            _calculateViewPos();
            _levelDiamonds = 9;
            _fuseStepDelay = GAMEBOULDERDASHLEVELFOURFUSESTEPDELAY;
            _initLevelFourMaze();
            break;
        case GAMEBOULDERDASHLEVELFIVE:
            _posXRocky = 21;
            _posYRocky = 20;
            _calculateViewPos();
            _levelDiamonds = 6;
            _fuseStepDelay = GAMEBOULDERDASHLEVELFIVEFUSESTEPDELAY;
            _initLevelFiveMaze();
            break;
    }
    _renderRocky();
}

void NGColorDotMatrixGameBoulderdash::_initLevelTestMaze() {
    int x, y;
    // Dirt
    _generateDirtRect(0, 0, GAMEBOULDERDASHMAZESIZEX - 1, GAMEBOULDERDASHMAZESIZEY - 1);
    // Void
    _generateVoidRect(15, 10, 19, 11);
    _generateVoidRect(2, 15, 5, 18);
    // Wall
    _generateWallRectWithVoid(8, 3, 12, 6);
    // Boulders
    int boulders = random(1, 4);
    for (int i = 0; i < boulders; i++) {
        bool ok;
        do {
            x = random(2, 7);
            y = random(2, 7);
            ok = _maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIRT;
        } while (!ok);
        _generateBoulder(x, y);
    }
    // Diamonds
    for (int i = 0; i < _levelDiamonds; i++) {
        bool ok;
        do {
            x = random(2, 7);
            y = random(2, 7);
            ok = _maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIRT;
        } while (!ok);
        _generateDiamond(x, y);
    }
    _generateDiamond(11, 5);
    // Lava
    _generateLava(5, 15);
    // Bomb
    _generateBomb(5, 1);
    _generateBomb(20, 9);
    // NPC
    _generateNPC(19, 10);
    _generateNPC(3, 16);
    // Door
    _generateDoor(8, 1);
    // Rocky
    _computeRocky();
}

void NGColorDotMatrixGameBoulderdash::_initLevelOneMaze() {
    int x, y;
    // Dirt
    _generateDirtRect(0, 0, GAMEBOULDERDASHMAZESIZEX - 1, GAMEBOULDERDASHMAZESIZEY - 1);
    // Boulders
    int boulders = random(1, 4);
    for (int i = 0; i < boulders; i++) {
        bool ok;
        do {
            x = random(2, GAMEBOULDERDASHMAZESIZEX - 1);
            y = random(2, GAMEBOULDERDASHMAZESIZEY - 1);
            ok = _maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIRT;
        } while (!ok);
        _maze[y][x] = GAMEBOULDERDASHCOLORINDEXBOULDER;
    }
    // Diamonds
    for (int i = 0; i < _levelDiamonds; i++) {
        bool ok;
        do {
            x = random(2, GAMEBOULDERDASHMAZESIZEX - 1);
            y = random(2, GAMEBOULDERDASHMAZESIZEY - 1);
            ok = _maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIRT;
        } while (!ok);
        _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
    }
    // Door
    _generateDoor(23, 23);
    // Rocky
    _computeRocky();
}

void NGColorDotMatrixGameBoulderdash::_initLevelTwoMaze() {
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
    // Door
    _generateDoor(23, 15);
    // Rocky
    _computeRocky();
}

void NGColorDotMatrixGameBoulderdash::_initLevelThreeMaze() {
    // Dirt
    _generateDirtRect(0, 0, GAMEBOULDERDASHMAZESIZEX - 1, GAMEBOULDERDASHMAZESIZEY - 1);
    // Void
    _generateVoidRect(21, 19, 23, 23);
    _generateVoidRect(12, 19, 13, 23);
    _generateVoidLine(12, 8, 13, 8);
    _generateVoid(13, 7);
    _generateVoid(13, 10);
    _generateVoid(15, 12);
    _generateVoid(5, 13);
    // Wall
    _generateWallLine(0, 4, 3, 7);
    _generateWallLine(0, 8, 2, 8);
    _generateWallLine(7, 0, 9, 2);
    _generateWallLine(5, 7, 8, 3);
    _generateWallLine(11, 8, 15, 4);
    _generateWallLine(16, 4, 19, 7);
    _generateWallLine(20, 8, 20, 10);
    _generateWall(19, 10);
    _generateWallLine(11, 9, 15, 13);
    _generateWallLine(16, 13, 19, 13);
    _generateWallRectWithNone(4, 12, 8, 15);
    _generateWallLine(0, 22, 9, 22);
    _generateWallLine(9, 18, 9, 22);
    _generateWallLine(11, 18, 11, 23);
    _generateWallLine(14, 18, 14, 23);
    _generateWallLine(12, 18, 13, 18);
    _generateWallLine(20, 18, 20, 23);
    _generateWallLine(21, 18, 23, 18);
    // Boulders
    _generateBoulderLine(6, 1, 6, 2);
    _generateBoulderLine(4, 4, 4, 5);
    _generateBoulder(2, 3);
    _generateBoulderLine(12, 0, 12, 1);
    _generateBoulderLine(18, 1, 19, 0);
    _generateBoulderLine(17, 2, 19, 4);
    _generateBoulder(20, 3);
    _generateBoulderLine(11, 4, 12, 4);
    _generateBoulder(10, 6);
    _generateBoulder(23, 6);
    _generateBoulder(15, 8);
    _generateBoulder(17, 8);
    _generateBoulder(16, 9);
    _generateBoulder(12, 9);
    _generateBoulder(4, 9);
    _generateBoulderLine(0, 11, 1, 11);
    _generateBoulder(22, 12);
    _generateBoulderLine(0, 14, 1, 14);
    _generateBoulder(1, 15);
    _generateBoulderLine(0, 16, 1, 16);
    _generateBoulderLine(11, 14, 11, 15);
    _generateBoulderLine(12, 15, 13, 16);
    _generateBoulder(21, 15);
    _generateBoulderLine(2, 18, 7, 18);
    _generateBoulderLine(2, 19, 2, 21);
    _generateBoulder(4, 21);
    _generateBoulderLine(3, 18, 7, 18);
    _generateBoulder(5, 19);
    _generateBoulderLine(16, 18, 17, 17);
    _generateBoulder(16, 19);
    _generateBoulderLine(18, 21, 18, 23);
    _generateBoulder(19, 21);
    // Diamonds
    _generateDiamond(5, 2);
    _generateDiamond(17, 1);
    _generateDiamond(23, 7);
    _generateDiamond(12, 5);
    _generateDiamond(16, 8);
    _generateDiamond(7, 14);
    _generateDiamond(0, 15);
    _generateDiamond(12, 16);
    _generateDiamond(3, 21);
    _generateDiamond(2, 23);
    _generateDiamond(19, 23);
    // Bombs
    _generateBomb(21, 2);
    _generateBomb(7, 7);
    _generateBomb(17, 14);
    // Door
    _generateDoor(0, 23);
    // Rocky
    _computeRocky();
}

void NGColorDotMatrixGameBoulderdash::_initLevelFourMaze() {
    // Dirt
    _generateDirtRect(0, 0, GAMEBOULDERDASHMAZESIZEX - 1, GAMEBOULDERDASHMAZESIZEY - 1);
    // Void
    _generateVoidLine(6, 16, 6, 18);
    _generateVoidRect(5, 19, 7, 21);
    _generateVoidLine(7, 10, 10, 10);
    _generateVoidLine(8, 11, 9, 11);
    _generateVoidLine(15, 10, 15, 12);
    _generateVoidLine(19, 10, 21, 10);
    _generateVoidLine(20, 11, 21, 11);
    _generateVoid(21, 12);
    _generateVoidLine(14, 17, 14, 18);
    _generateVoidLine(21, 16, 21, 17);
    _generateVoid(22, 17);
    _generateVoid(14, 20);
    _generateVoidLine(12, 22, 12, 23);
    // Wall
    _generateWallLine(16, 2, 21, 2);
    _generateWallLine(16, 5, 21, 5);
    _generateWallLine(7, 5, 11, 9);
    _generateWallLine(12, 9, 20, 9);
    _generateWallLine(11, 13, 20, 13);
    _generateWallLine(11, 16, 18, 16);
    _generateWallLine(11, 19, 18, 19);
    _generateWallLine(11, 21, 18, 21);
    _generateWallLine(4, 9, 4, 13);
    _generateWallLine(0, 15, 4, 15);
    _generateWallLine(0, 18, 4, 18);
    // Boulders
    _generateBoulderRectWithDiamonds(2, 2, 4, 4);
    _generateBoulderLine(8, 3, 10, 1);
    _generateBoulderLine(11, 2, 12, 3);
    _generateBoulderRectWithVoid(12, 4, 13, 6);
    _generateBoulderLine(8, 5, 9, 6);
    _generateBoulderRectWithVoid(10, 6, 12, 7);
    _generateBoulder(13, 6);
    _generateBoulder(11, 8);
    _generateBoulder(22, 0);
    _generateBoulderLine(16, 3, 16, 4);
    _generateBoulder(18, 3);
    _generateBoulderLine(16, 7, 17, 6);
    _generateBoulderLine(18, 6, 18, 7);
    _generateBoulderLine(20, 6, 21, 6);
    _generateBoulderLine(20, 8, 21, 8);
    _generateBoulder(12, 11);
    _generateBoulderLine(16, 10, 16, 12);
    _generateBoulder(23, 10);
    _generateBoulder(12, 14);
    _generateBoulderLine(15, 14, 18, 14);
    _generateBoulderLine(15, 17, 15, 18);
    _generateBoulder(21, 18);
    _generateBoulder(15, 20);
    _generateBoulderLine(13, 22, 13, 23);
    _generateBoulder(0, 9);
    _generateBoulder(3, 11);
    _generateBoulder(1, 12);
    _generateBoulder(1, 16);
    _generateBoulder(3, 17);
    // Diamonds
    _generateDiamond(10, 4);
    _generateDiamond(17, 11);
    _generateDiamond(0, 17);
    _generateDiamond(15, 23);
    // Bombs
    _generateBomb(6, 9);
    _generateBomb(22, 15);
    // NPC
    _generateNPCLeft(9, 10);
    _generateNPCRight(20, 10);
    _generateNPCUp(7, 21);
    _generateNPCRight(20, 17);
    // Door
    _generateDoor(14, 14);
    // Rocky
    _computeRocky();
}

void NGColorDotMatrixGameBoulderdash::_initLevelFiveMaze() {
    // Dirt
    _generateDirtRect(0, 0, GAMEBOULDERDASHMAZESIZEX - 1, GAMEBOULDERDASHMAZESIZEY - 1);
    // Void
    _generateVoidRect(16, 1, 18, 3);
    _generateVoidRect(21, 1, 22, 2);
    _generateVoidRect(12, 4, 14, 6);
    _generateVoidRect(21, 5, 23, 6);
    _generateVoidRect(7, 7, 10, 8);
    _generateVoidRect(15, 8, 17, 9);
    _generateVoidRect(5, 10, 7, 12);
    _generateVoidRect(4, 13, 7, 14);
    _generateVoidRect(9, 10, 13, 11);
    _generateVoidRect(12, 12, 13, 17);
    _generateVoidRect(15, 11, 18, 13);
    _generateVoidRect(20, 9, 21, 13);
    _generateVoidRect(4, 16, 6, 18);
    _generateVoidRect(4, 20, 7, 21);
    _generateVoidRect(9, 21, 12, 23);
    _generateVoidLine(0, 23, 6, 23);
    _generateVoidRect(15, 22, 23, 23);
    // Wall
    _generateWallRectWithVoid(4, 2, 6, 4);
    _generateWallLine(0, 22, 6, 22);
    _generateWallLine(7, 22, 7, 23);
    _generateWallLine(15, 21, 23, 21);
    _generateWallLine(14, 21, 14, 23);
    // Boulders
    _generateBoulder(1, 3);
    _generateBoulder(4, 6);
    _generateBoulder(10, 5);
    _generateBoulderLine(14, 1, 14, 2);
    _generateBoulderLine(23, 8, 23, 9);
    _generateBoulderLine(1, 12, 1, 13);
    _generateBoulder(9, 13);
    _generateBoulderLine(15, 15, 16, 16);
    // Diamonds
    _generateDiamond(10, 2);
    _generateDiamond(19, 18);
    _generateDiamond(7, 21);
    // Bombs
    _generateBomb(3, 0);
    // Lava
    _generateLava(16, 1);
    _generateLava(22, 1);
    _generateLava(7, 8);
    _generateLava(17, 8);
    _generateLava(4, 18);
    // NPC
    _generateNPCRight(12, 4);
    _generateNPCRight(20, 6);
    _generateNPCUp(7, 14);
    _generateNPCUp(13, 17);
    _generateNPCDown(18, 11);
    _generateNPCLeft(21, 13);
    _generateNPCRight(4, 21);
    _generateNPCLeft(12, 23);
    // Door
    _generateDoor(5, 3);
    // Rocky
    _computeRocky();
}

void NGColorDotMatrixGameBoulderdash::_generateNPC(byte x, byte y) {
    _generateNPC(x, y, random(6, 10));
}

void NGColorDotMatrixGameBoulderdash::_generateNPCUp(byte x, byte y) {
    _generateNPC(x, y, GAMEBOULDERDASHCOLORINDEXNPCUP);
}

void NGColorDotMatrixGameBoulderdash::_generateNPCDown(byte x, byte y) {
    _generateNPC(x, y, GAMEBOULDERDASHCOLORINDEXNPCDOWN);
}

void NGColorDotMatrixGameBoulderdash::_generateNPCLeft(byte x, byte y) {
    _generateNPC(x, y, GAMEBOULDERDASHCOLORINDEXNPCLEFT);
}

void NGColorDotMatrixGameBoulderdash::_generateNPCRight(byte x, byte y) {
    _generateNPC(x, y, GAMEBOULDERDASHCOLORINDEXNPCRIGHT);
}

void NGColorDotMatrixGameBoulderdash::_generateNPC(byte x, byte y, byte kind) {
    _maze[y][x] = kind;
}

void NGColorDotMatrixGameBoulderdash::_generateVoid(byte x, byte y) {
    _maze[y][x] = GAMEBOULDERDASHCOLORINDEXVOID;
}

void NGColorDotMatrixGameBoulderdash::_generateDirt(byte x, byte y) {
    _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDIRT;
}

void NGColorDotMatrixGameBoulderdash::_generateDiamond(byte x, byte y) {
    _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
}

void NGColorDotMatrixGameBoulderdash::_generateDoor(byte x, byte y) {
    _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDOORINACTIVE;
}

void NGColorDotMatrixGameBoulderdash::_generateBomb(byte x, byte y) {
    _maze[y][x] = GAMEBOULDERDASHCOLORINDEXBOMBINACTIVE;
}

void NGColorDotMatrixGameBoulderdash::_generateLava(byte x, byte y) {
    _maze[y][x] = GAMEBOULDERDASHCOLORINDEXLAVA;
}


void NGColorDotMatrixGameBoulderdash::_generateBoulder(byte x, byte y) {
    _maze[y][x] = GAMEBOULDERDASHCOLORINDEXBOULDER;
}

void NGColorDotMatrixGameBoulderdash::_generateBoulderLine(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateLine(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXBOULDER);
}

void NGColorDotMatrixGameBoulderdash::_generateWall(byte x, byte y) {
    _maze[y][x] = GAMEBOULDERDASHCOLORINDEXWALL;
}

void NGColorDotMatrixGameBoulderdash::_generateWallLine(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateLine(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXWALL);
}

void NGColorDotMatrixGameBoulderdash::_generateLine(byte topX, byte topY, byte bottomX, byte bottomY, byte solid) {
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

void NGColorDotMatrixGameBoulderdash::_generateVoidLine(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateLine(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXVOID);
}

void NGColorDotMatrixGameBoulderdash::_generateVoidRect(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateSolidRect(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXVOID);
}

void NGColorDotMatrixGameBoulderdash::_generateDirtRect(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateSolidRect(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXDIRT);
}

void NGColorDotMatrixGameBoulderdash::_generateSolidRect(byte topX, byte topY, byte bottomX, byte bottomY, byte solid) {
    for (int y = topY; y <= bottomY; y++) {
        for (int x = topX; x <= bottomX; x++) {
            _maze[y][x] = solid;
        }
    }
}

void NGColorDotMatrixGameBoulderdash::_generateBoulderRectWithVoid(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateBoulderRect(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXVOID);
}

void NGColorDotMatrixGameBoulderdash::_generateBoulderRectWithDiamonds(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateBoulderRect(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXDIAMOND01);
}

void NGColorDotMatrixGameBoulderdash::_generateBoulderRect(byte topX, byte topY, byte bottomX, byte bottomY, byte filler) {
    for (int y = topY; y <= bottomY; y++) {
        for (int x = topX; x <= bottomX; x++) {
            if (y == topY || y == bottomY || x == topX || x == bottomX) {
                _generateBoulder(x, y);
            } else {
                _maze[y][x] = filler;
            }
        }
    }
}

void NGColorDotMatrixGameBoulderdash::_generateWallRectWithVoid(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateWallRect(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXVOID);
}

void NGColorDotMatrixGameBoulderdash::_generateWallRectWithNone(byte topX, byte topY, byte bottomX, byte bottomY) {
    _generateWallRect(topX, topY, bottomX, bottomY, GAMEBOULDERDASHCOLORINDEXNONE);
}

void NGColorDotMatrixGameBoulderdash::_generateWallRect(byte topX, byte topY, byte bottomX, byte bottomY, int filler) {
    for (int y = topY; y <= bottomY; y++) {
        for (int x = topX; x <= bottomX; x++) {
            if (y == topY || y == bottomY || x == topX || x == bottomX) {
                _generateWall(x, y);
            } else if (filler >= 0) {
                _maze[y][x] = filler;
            }
        }
    }
}

bool NGColorDotMatrixGameBoulderdash::_checkBomb() {
    bool res = false;
    res = _posXRocky > 0 && _maze[_posYRocky][_posXRocky - 1] == GAMEBOULDERDASHCOLORINDEXBOMBINACTIVE;
    if (res) {
        _maze[_posYRocky][_posXRocky - 1] = GAMEBOULDERDASHCOLORINDEXBOMBACTIVE01;
    } else {
        res = _posXRocky < GAMEBOULDERDASHMAZESIZEX - 1 && _maze[_posYRocky][_posXRocky + 1] == GAMEBOULDERDASHCOLORINDEXBOMBINACTIVE;
        if (res) {
            _maze[_posYRocky][_posXRocky + 1] = GAMEBOULDERDASHCOLORINDEXBOMBACTIVE01;
        } else {
            res = _posYRocky > 0 && _maze[_posYRocky - 1][_posXRocky] == GAMEBOULDERDASHCOLORINDEXBOMBINACTIVE;
            if (res) {
                _maze[_posYRocky - 1][_posXRocky] = GAMEBOULDERDASHCOLORINDEXBOMBACTIVE01;
            } else {
                res = _posYRocky < GAMEBOULDERDASHMAZESIZEY - 1 && _maze[_posYRocky + 1][_posXRocky] == GAMEBOULDERDASHCOLORINDEXBOMBINACTIVE;
                if (res) {
                    _maze[_posYRocky + 1][_posXRocky] = GAMEBOULDERDASHCOLORINDEXBOMBACTIVE01;
                }
            }
        }
    }
    return res;
}

void NGColorDotMatrixGameBoulderdash::_computeBomb() {
    bool rockykilled = false;
    for (int y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
        for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            if (_maze[y][x] >= GAMEBOULDERDASHCOLORINDEXBOMBACTIVE01 && _maze[y][x] < GAMEBOULDERDASHCOLORINDEXBOMBACTIVE09) {
                _maze[y][x]++;
            } else if (_maze[y][x] == GAMEBOULDERDASHCOLORINDEXBOMBACTIVE09) {
                _maze[y][x] = -GAMEBOULDERDASHCOLORINDEXBOMBDESTROYED;
                if (x > 0) {
                    if (_maze[y][x - 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockykilled = true;
                    } else if (_isColorIndexNPC(_maze[y][x - 1])) {
                        _maze[y][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                    } else {
                        _maze[y][x - 1] = -GAMEBOULDERDASHCOLORINDEXBOMBDESTROYED;
                    }
                    if (y > 0) {
                        if (_maze[y - 1][x - 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                            rockykilled = true;
                        } else if (_isColorIndexNPC(_maze[y - 1][x - 1])) {
                            _maze[y - 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else {
                            _maze[y - 1][x - 1] = -GAMEBOULDERDASHCOLORINDEXBOMBDESTROYED;
                        }
                    }
                    if (y < GAMEBOULDERDASHMAZESIZEY - 1) {
                        if (_maze[y + 1][x - 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                            rockykilled = true;
                        } else if (_isColorIndexNPC(_maze[y + 1][x - 1])) {
                            _maze[y + 1][x - 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else {
                            _maze[y + 1][x - 1] = -GAMEBOULDERDASHCOLORINDEXBOMBDESTROYED;
                        }
                    }
                }
                if (x < GAMEBOULDERDASHMAZESIZEX - 1) {
                    if (_maze[y][x + 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockykilled = true;
                    } else if (_isColorIndexNPC(_maze[y][x + 1])) {
                        _maze[y][x + 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                    } else {
                        _maze[y][x + 1] = -GAMEBOULDERDASHCOLORINDEXBOMBDESTROYED;
                    }
                    if (y > 0) {
                        if (_maze[y - 1][x + 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                            rockykilled = true;
                        } else if (_isColorIndexNPC(_maze[y - 1][x + 1])) {
                            _maze[y - 1][x + 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else {
                            _maze[y - 1][x + 1] = -GAMEBOULDERDASHCOLORINDEXBOMBDESTROYED;
                        }
                    }
                    if (y < GAMEBOULDERDASHMAZESIZEY - 1) {
                        if (_maze[y + 1][x + 1] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                            rockykilled = true;
                        } else if (_isColorIndexNPC(_maze[y + 1][x + 1])) {
                            _maze[y + 1][x + 1] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                        } else {
                            _maze[y + 1][x + 1] = -GAMEBOULDERDASHCOLORINDEXBOMBDESTROYED;
                        }
                    }
                }
                if (y > 0) {
                    if (_maze[y - 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockykilled = true;
                    } else if (_isColorIndexNPC(_maze[y - 1][x])) {
                        _maze[y - 1][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                    } else {
                        _maze[y - 1][x] = -GAMEBOULDERDASHCOLORINDEXBOMBDESTROYED;
                    }
                }
                if (y < GAMEBOULDERDASHMAZESIZEY - 1) {
                    if (_maze[y + 1][x] == GAMEBOULDERDASHCOLORINDEXROCKY) {
                        rockykilled = true;
                    } else if (_isColorIndexNPC(_maze[y + 1][x])) {
                        _maze[y + 1][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
                    } else {
                        _maze[y + 1][x] = -GAMEBOULDERDASHCOLORINDEXBOMBDESTROYED;
                    }
                }
            } else if (_maze[y][x] == GAMEBOULDERDASHCOLORINDEXBOMBDESTROYED) {
                _maze[y][x] = 0;
            }
            if (rockykilled) {
                _livesCounter--;
                _gameFinished = _livesCounter == 0;
                if (!_gameFinished) {
                    _levelRetry = true;
                }
                return;
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

void NGColorDotMatrixGameBoulderdash::_computeDoor() {
    for (int y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
        for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            if (_maze[y][x] == GAMEBOULDERDASHCOLORINDEXDOORINACTIVE && _levelFinished) {
                _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDOORACTIVE;
            }
        }
    }
}

void NGColorDotMatrixGameBoulderdash::_computeDiamond() {
    for (int y = 0; y < GAMEBOULDERDASHMAZESIZEY; y++) {
        for (int x = 0; x < GAMEBOULDERDASHMAZESIZEX; x++) {
            if (_maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIAMOND01) {
                _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND02;
            } else if (_maze[y][x] == GAMEBOULDERDASHCOLORINDEXDIAMOND02) {
                _maze[y][x] = GAMEBOULDERDASHCOLORINDEXDIAMOND01;
            }
        }
    }
}

void NGColorDotMatrixGameBoulderdash::_clearRocky() {
    _maze[_posYRocky][_posXRocky] = GAMEBOULDERDASHCOLORINDEXVOID;
}

void NGColorDotMatrixGameBoulderdash::_computeRocky() {
    _maze[_posYRocky][_posXRocky] = GAMEBOULDERDASHCOLORINDEXROCKY;
}

bool NGColorDotMatrixGameBoulderdash::_checkRocky(rockyMoveDirection direction) {
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
        res = _maze[posY][posX] == GAMEBOULDERDASHCOLORINDEXDOORACTIVE;
        if (res) {
            _doorEntered = true;
        } else {
            res = _isColorIndexDiamond(_maze[posY][posX]);
            if (res) {
                if (_levelDiamonds > 0) {
                    _levelDiamonds--;
                }
                _scoreCounter++;
                _levelFinished = _levelDiamonds == 0;
            } else {
                switch(direction) {
                    case rmdLeft:
                        if (posX - 1 >= 0) {
                            res = ((_maze[posY][posX] == GAMEBOULDERDASHCOLORINDEXBOULDER || _isColorIndexBomb(_maze[posY][posX])) && _maze[posY][posX - 1] == 0);
                            if (res) {
                                _maze[posY][posX - 1] = _maze[posY][posX];
                            }
                        }
                        break;
                    case rmdRight:
                        if (posX + 1 < GAMEBOULDERDASHMAZESIZEX) {
                            res = ((_maze[posY][posX] == GAMEBOULDERDASHCOLORINDEXBOULDER || _isColorIndexBomb(_maze[posY][posX])) && _maze[posY][posX + 1] == 0);
                            if (res) {
                                _maze[posY][posX + 1] = _maze[posY][posX];
                            }
                        }
                        break;
                }
            }
        }
    }
    return res;
}

void NGColorDotMatrixGameBoulderdash::_renderRocky() {
    switch (_rockyBlinkIndex) {
        case 0:
            _ipc->drawPoint(_posXRocky - _viewPosX + 1, _posYRocky - _viewPosY + 1, COLOR_BLUE);
            break;
        case 1:
            _ipc->drawPoint(_posXRocky - _viewPosX + 1, _posYRocky - _viewPosY + 1, COLOR_BLUE_LOW);
            break;
    }
    _rockyBlinkIndex++;
    if (_rockyBlinkIndex > 1) {
        _rockyBlinkIndex = 0;
    }
}

void NGColorDotMatrixGameBoulderdash::_calculateViewPos() {
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

void NGColorDotMatrixGameBoulderdash::_ownIntro() {
    _ipc->beginUpdate();
    // Dirt
    if (_hasSprite(GAMEBOULDERDASHCOLORINDEXDIRT)) {
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                _renderSprite(GAMEBOULDERDASHCOLORINDEXDIRT, x, y);
            }
        }
    } else {
        _ipc->fillRect(0, 0, 7, 7, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIRT - 1]);
    }
    // Diamonds
    _ipc->drawPoint(6, 3, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND01 - 1]);
    _ipc->drawPoint(5, 5, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND01 - 1]);
    _ipc->drawPoint(2, 6, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND01 - 1]);
    // Boulders
    _ipc->drawPoint(5, 1, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXBOULDER - 1]);
    _ipc->drawPoint(6, 1, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXBOULDER - 1]);
    _ipc->drawPoint(1, 5, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXBOULDER - 1]);
    _ipc->drawPoint(6, 7, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXBOULDER - 1]);
    _ipc->endUpdate();
}

void NGColorDotMatrixGameBoulderdash::_ownIntroAnimation() {
    if (_startUpAnimationStep == -1 || millis() - _lastStartUpAnimationStep >= GAMEBOULDERDASHROCKYBLINKDELAY) {
        _startUpAnimationStep++;
        if (_startUpAnimationStep % 2 == 0) {
            _ipc->drawPoint(2, 2, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXROCKY - 1]);
            _ipc->drawPoint(6, 3, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND01 - 1]);
            _ipc->drawPoint(5, 5, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND01 - 1]);
            _ipc->drawPoint(2, 6, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND01 - 1]);
        } else {
            _ipc->drawPoint(2, 2, COLOR_BLUE_LOW);
            _ipc->drawPoint(6, 3, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND02 - 1]);
            _ipc->drawPoint(5, 5, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND02 - 1]);
            _ipc->drawPoint(2, 6, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND02 - 1]);
        }
        _lastStartUpAnimationStep = millis();
        _startUpDone = _startUpAnimationStep == 4;
        if (_startUpDone) {
            _inStartUpAnimation = false;
        }
    }
}

void NGColorDotMatrixGameBoulderdash::_ownOutro() {
    for (int i = 0; i < 4; i++) {
        _ipc->beginUpdate();
        if (i < 3) {
            _ipc->fillRect(4 - i, 4 - i, 4 + i, 4 + i, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND01 - 1]);
        } else {
            _ipc->drawRect(4 - i, 4 - i, 4 + i, 4 + i, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIRT - 1]);
        }
        _ipc->endUpdate();
        delay(GAMEBOULDERDASHSOUTROANIMATIONSUCCESSDELAY);
    }
    _score->setValue(_scoreCounter);
    delay(GAMEBOULDERDASHSOUTRODELAY);
}

void NGColorDotMatrixGameBoulderdash::_ownLevelOutroSuccess() {
    for (int y = 7; y > 0; y--) {
        _ipc->beginUpdate();
        _ipc->drawLine(1, y, 7, y, globalBoulderdashColors[GAMEBOULDERDASHCOLORINDEXDIAMOND01 - 1]);
        _ipc->endUpdate();
        delay(GAMEBOULDERDASHSOUTROANIMATIONSUCCESSDELAY);
    }
}

void NGColorDotMatrixGameBoulderdash::_ownLevelOutroFail() {
    _score->setValue(_scoreCounter);
    for (int i = 0; i < 4; i++) {
        _ipc->beginUpdate();
        _ipc->clearRect(_posXRocky - _viewPosX + 1 - i, _posYRocky - _viewPosY + 1 - i, _posXRocky - _viewPosX + 1 + i, _posYRocky - _viewPosY + 1 + i);
        _ipc->endUpdate();
        delay(GAMEBOULDERDASHSOUTROANIMATIONFAILDELAY);
    }
}

void NGColorDotMatrixGameBoulderdash::_ownRender() {
    _ipc->beginUpdate();
    for (int y = 1; y < 8; y++) {
        for (int x = 1; x < 8; x++) {
            byte i = _maze[_viewPosY + y - 1][_viewPosX + x - 1];
            if (i > 0) {
                if (i != GAMEBOULDERDASHCOLORINDEXROCKY) {
                    if (_hasSprite(i)) {
                        _renderSprite(i, x, y);
                    } else {
                        colorRGB c = globalBoulderdashColors[i - 1];
                        _ipc->drawPoint(x, y, c);
                    }
                }
            } else {
                _ipc->clearPoint(x, y);
            }
        }
    }
    _score->setValue(_levelDiamonds);
    _lives->setValue(_livesCounter);
    _fuse->setValue(_fuseValue);
    _ipc->endUpdate();
}

void NGColorDotMatrixGameBoulderdash::_ownJoystickLoop() {
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
                    _checkBomb();
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

void NGColorDotMatrixGameBoulderdash::_doInitialize() {
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

void NGColorDotMatrixGameBoulderdash::_doStartUp() {
    if (!_inStartUpAnimation) {
        if (_logging) {
            char log[100];
            sprintf(log, "%s.StartUp", _name);
            writeInfo(log);
        }
        _ownIntro();
        _inStartUpAnimation = true;
        _startUpAnimationStep = -1;
    } else {
        _ownIntroAnimation();
    }
}

void NGColorDotMatrixGameBoulderdash::_doStartUpDone() {
    _ipc->clear();
    _score->setValue(0);
    _lives->setValue(GAMEBOULDERDASHLIVES);
    _fuse->setValue(GAMEBOULDERDASHMAXFUSE);
    if (_logging) {
        char log[100];
        sprintf(log, "%s.StartUp done", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameBoulderdash::_doStartGame() {
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

void NGColorDotMatrixGameBoulderdash::_doBreakGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s.BreakGame", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameBoulderdash::_doContinueGame() {
    if (_logging) {
        char log[100];
        sprintf(log, "%s.ContinueGame", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameBoulderdash::_doFinishGame() {
    _ipc->clear();
    if (_logging) {
        char log[100];
        sprintf(log, "%s.FinishGame", _name);
        writeInfo(log);
    }
}

void NGColorDotMatrixGameBoulderdash::_doProcessingLoop() {
    if (_gameStarted) {
        _ownJoystickLoop();
        if (_levelFinished && _doorEntered) {
            _ownLevelOutroSuccess();
            _level++;
            _gameFinished = _level > GAMEBOULDERDASHMAXLEVEL;
            if (!_gameFinished) {
                _initLevel();
            }
        }
        if (_levelRetry) {
            _ownLevelOutroFail();
            _initLevel();
        }
        if (!_gameFinished) {
            _computeDoor();
            if ((millis() - _lastRockyBlinked) > GAMEBOULDERDASHROCKYBLINKDELAY) {
                _renderRocky();
                _lastRockyBlinked = millis();
            }
            if ((millis() - _lastDiamondSparkle) > GAMEBOULDERDASHDIAMONDSPARKLEDELAY) {
                _computeDiamond();
                _lastDiamondSparkle = millis();
            }
            if ((millis() - _lastGravityMove) > _gameNextStepDelay) {
                _computeGravity();
                _ownRender();
                _lastGravityMove = millis();
            }
            if ((millis() - _lastNPCMove) > GAMEBOULDERDASHSNPCDELAY) {
                if (!_testMode) {
                    _computeNPC();
                }
                _ownRender();
                _lastNPCMove = millis();
            }
            if ((millis() - _lastBombIgnition) > GAMEBOULDERDASHSBOMBDELAY) {
                _computeBomb();
                _ownRender();
                _lastBombIgnition = millis();
            }
            if ((millis() - _lastLavaFlow) > GAMEBOULDERDASHSLAVADELAY) {
                if (!_testMode) {
                    _computeLava();
                }
                _ownRender();
                _lastLavaFlow = millis();
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
