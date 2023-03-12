//
//  NGCustomColorDotMatrixGame.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 12.03.23.
//

#include "NGCustomColorDotMatrixGame.h"

void NGCustomColorDotMatrixGame::registerColorDotMatrix(NGIPaintableComponent *ipc) {
    _ipc = ipc;
    _score = new NGColorDotMatrixBinaryDigit(_ipc, _scoreDigits, _scoreDirection, _scoreDigitPosX, _scoreDigitPosY);
}
