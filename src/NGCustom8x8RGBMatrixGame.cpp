//
//  NGCustom8x8RGBMatrixGame.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.12.22.
//

#include "NGCustom8x8RGBMatrixGame.h"

void NGCustom8x8RGBMatrixGame::registerColorDotMatrix(NGColorDotMatrix *cdm) {
    _cdm = cdm;
    _score = new NGColorDotMatrixBinaryDigit(_cdm, _scoreDigits, _scoreDirection, _scoreDigitPosX, _scoreDigitPosY);
}
