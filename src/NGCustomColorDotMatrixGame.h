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
#include <NGCustomSprite.h>
#include <NGColorDotMatrixBinaryDigit.h>

#define DEFSCOREDIGITS        4
#define DEFSCOREDIGITPOSX     7
#define DEFSCOREDIGITPOSY     7
#define DEFSCOREDIRECTION bddUp

#define MAXSPRITECOUNT 10
#define NOSPRITE -1

struct gameSpriteStruct
{
    byte id;
    NGCustomSprite *sprite;
};
typedef struct gameSpriteStruct gameSprite;

class NGCustomColorDotMatrixGame : public NGCustomGame {
       
protected:
    NGIPaintableComponent *_ipc;
    NGColorDotMatrixBinaryDigit *_score;
    byte _scoreDigits = DEFSCOREDIGITS;
    byte _scoreDigitPosX = DEFSCOREDIGITPOSX;
    byte _scoreDigitPosY = DEFSCOREDIGITPOSY;
    BinaryDigitDirection _scoreDirection = DEFSCOREDIRECTION;
    gameSprite _sprites[MAXSPRITECOUNT];
    byte _spriteCount = 0;
    
    bool _hasSprite(int id);
    int _getSpriteIndex(int id);
    void _renderSprite(int id, int x, int y);
    
public:
    void registerColorDotMatrix(NGIPaintableComponent *ipc);
    
    void registerSprite(byte id, NGCustomSprite *sprite);
};

#endif /* NGCustomColorDotMatrixGame_h */
