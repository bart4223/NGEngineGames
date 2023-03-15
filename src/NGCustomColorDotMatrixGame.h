//
//  NGCustomColorDotMatrixGame.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 12.03.23.
//

#ifndef NGCustomColorDotMatrixGame_h
#define NGCustomColorDotMatrixGame_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomGame.h>
#include <NGColorDotMatrixBinaryDigit.h>

#define DEFSCOREDIGITS        4
#define DEFSCOREDIGITPOSX     7
#define DEFSCOREDIGITPOSY     7
#define DEFSCOREDIRECTION bddUp

class NGCustomColorDotMatrixGame : public NGCustomGame {
       
protected:
    NGIPaintableComponent *_ipc;
    NGColorDotMatrixBinaryDigit *_score;
    byte _scoreDigits = DEFSCOREDIGITS;
    byte _scoreDigitPosX = DEFSCOREDIGITPOSX;
    byte _scoreDigitPosY = DEFSCOREDIGITPOSY;
    BinaryDigitDirection _scoreDirection = DEFSCOREDIRECTION;

public:
    void registerColorDotMatrix(NGIPaintableComponent *ipc);
};

#endif /* NGCustomColorDotMatrixGame_h */
