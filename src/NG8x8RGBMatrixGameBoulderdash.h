//
//  NG8x8RGBMatrixGameBoulderdash.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 09.01.23.
//

#ifndef NG8x8RGBMatrixGameBoulderdash_h
#define NG8x8RGBMatrixGameBoulderdash_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustom8x8RGBMatrixGame.h>
#include <NGColorDotMatrixFuse.h>

#define GAMEBOULDERDASHCOLORSCOREOFF  COLOR_BLACK
#define GAMEBOULDERDASHCOLORSCOREON   COLOR_TEAL
#define GAMEBOULDERDASHCOLORLIVESOFF  COLOR_BLACK
#define GAMEBOULDERDASHCOLORLIVESON   { .red = 0xCC, .green = 0x33, .blue = 0x33 }
#define GAMEBOULDERDASHCOLORFUSEOFF   COLOR_BLACK
#define GAMEBOULDERDASHCOLORFUSEON    COLOR_ORANGE

#define GAMEBOULDERDASHMAZESIZEX         24
#define GAMEBOULDERDASHMAZESIZEY         24

#define GAMEBOULDERDASHSCOREDIGITS        5
#define GAMEBOULDERDASHSCOREDIGITXPOS     0
#define GAMEBOULDERDASHSCOREDIGITYPOS     5
#define GAMEBOULDERDASHSCOREDIRECTION bddUp

#define GAMEBOULDERDASHFUSEARITY 8

#define GAMEBOULDERDASHLIVESDIGITS        2
#define GAMEBOULDERDASHLIVESDIGITXPOS     0
#define GAMEBOULDERDASHLIVESDIGITYPOS     7
#define GAMEBOULDERDASHLIVESDIRECTION bddUp

#define GAMEBOULDERDASHGRAVITYDELAY      50
#define GAMEBOULDERDASHROCKYBLINKDELAY  500
#define GAMEBOULDERDASHFINISHDELAY     1000

#define GAMEBOULDERDASHLIVES    3
#define GAMEBOULDERDASHMAXFUSE  8

#define GAMEBOULDERDASHCOLORINDEXDIRT    1
#define GAMEBOULDERDASHCOLORINDEXROCKY   2
#define GAMEBOULDERDASHCOLORINDEXBOULDER 3
#define GAMEBOULDERDASHCOLORINDEXDIAMOND 4

#define GAMEBOULDERDASHSTARTLEVEL   1
#define GAMEBOULDERDASHMAXLEVEL     1

#define GAMEBOULDERDASHLEVELONEFUSESTEPDELAY    5000
#define GAMEBOULDERDASHSOUTROANIMATIONDELAY      100
#define GAMEBOULDERDASHSOUTRODELAY              3000

static colorRGB globalBoulderdashColors[4] = {
  COLOR_BROWN,  // Dirt
  COLOR_BLUE,   // Rocky
  COLOR_WHITE,  // Boulder
  COLOR_TEAL    // Diamond
};

class NG8x8RGBMatrixGameBoulderdash : public NGCustom8x8RGBMatrixGame {
    
private:
    NGColorDotMatrixBinaryDigit *_lives;
    NGColorDotMatrixFuse *_fuse;
    byte _maze[GAMEBOULDERDASHMAZESIZEY][GAMEBOULDERDASHMAZESIZEX];
    long _lastGravityMove = 0;
    long _lastFuseStep = 0;
    int  _fuseStepDelay = 0;
    long _lastRockyBlinked = 0;
    byte _rockyBlinkIndex = 0;
    byte _livesCounter = GAMEBOULDERDASHLIVES;
    byte _fuseValue = GAMEBOULDERDASHMAXFUSE;
    byte _viewPosX = 0;
    byte _viewPosY = 0;
    byte _level = GAMEBOULDERDASHSTARTLEVEL;
    byte _levelDiamonds = 0;
    bool _levelFinished = false;
    bool _levelRetry = false;
    byte _posXRocky = 0;
    byte _posYRocky = 0;
    
    void _resetMaze();
    
    void _computeGravity();
    
    void _initLevel();
    
    void _initLevelOneMaze();
    
    void _clearRocky();
    
    void _computeRocky();
    
    bool _checkRocky(byte posX, byte posY);
    
    void _renderRocky();
    
    void _calculateViewPos();
    
    void _ownJoystickLoop();
    
    void _ownRender();
    
    void _ownIntro();
    
    void _ownOutro();
    
    void _ownLevelOutro();
    
protected:
    void _doInitialize();
    
    void _doStartUp();
    
    void _doStartUpDone();
    
    void _doStartGame();
    
    void _doBreakGame();
    
    void _doContinueGame();
    
    void _doFinishGame();
    
    void _doProcessingLoop();
       
public:
    void registerColorDotMatrix(NGColorDotMatrix *cdm);
    
    NG8x8RGBMatrixGameBoulderdash();
};

#endif /* NG8x8RGBMatrixGameBoulderdash_h */
