//
//  NGCustomColorDotMatrixGame.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 12.03.23.
//

#ifndef NGCustomColorDotMatrixGame_h
#define NGCustomColorDotMatrixGame_h

#include <Arduino.h>
#include <Games/NGCustomGame.h>
#include <Sprites/NGCustomSprite.h>
#include <NGColorDotMatrixBinaryDigit.h>
#include <Visuals/NGDecimalPointCounter.h>

#define DEFSCOREDIGITS        4
#define DEFSCOREDIGITPOSX     7
#define DEFSCOREDIGITPOSY     7
#define DEFSCOREDIRECTION bddUp

#define DEFPOINTCOUNTERCOLOR     COLOR_BLUE
#define DEFPOINTCOUNTERMAXDIGITS 5

#define MAXSPRITECOUNT 10
#define NOSPRITE -1

#define GAMEDOTCOLORSCOREOFF { .red = 5, .green = 5, .blue = 5 }
#define GAMEDOTCOLORSCOREON COLOR_BLUE

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
    NGDecimalPointCounter *_pointCounter = nullptr;
    colorRGB _pointCounterColor = DEFPOINTCOUNTERCOLOR;
    byte _pointCounterMaxDigits = DEFPOINTCOUNTERMAXDIGITS;
    bool _pointCounterShowMaxDigits = false;
    int _pointCounterAnimationDelay = 0;
    int _pointCounterPosX = 0;
    int _pointCounterPosY = 0;
    colorRGB _colorScoreOff = GAMEDOTCOLORSCOREOFF;
    colorRGB _colorScoreOn = GAMEDOTCOLORSCOREON;
    
    bool _hasSprite(int id);
    int _getSpriteIndex(int id);
    void _renderSprite(int id);
    void _renderSprite(int id, int x, int y);
    void _setSpriteColor(int id, colorRGB color);
    void _doStartUpDone();

public:
    void registerColorDotMatrix(NGIPaintableComponent *ipc);
    
    void registerSprite(byte id, NGCustomSprite *sprite);
    
    void registerScoreSprite(NGCustomSprite *sprite);

    void setScoreColorOff(colorRGB color);

    void setScoreColorOn(colorRGB color);
};

#endif /* NGCustomColorDotMatrixGame_h */
