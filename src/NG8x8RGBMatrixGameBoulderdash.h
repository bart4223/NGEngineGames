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
#define GAMEBOULDERDASHCOLORSCOREON   COLOR_TEAL_LOW
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
#define GAMEBOULDERDASHSNPCDELAY        300
#define GAMEBOULDERDASHSBOMBDELAY       400
#define GAMEBOULDERDASHROCKYBLINKDELAY  500
#define GAMEBOULDERDASHFINISHDELAY     1000

#define GAMEBOULDERDASHLIVES    3
#define GAMEBOULDERDASHMAXFUSE  8

#define GAMEBOULDERDASHCOLORINDEXVOID            0
#define GAMEBOULDERDASHCOLORINDEXDIRT            1
#define GAMEBOULDERDASHCOLORINDEXROCKY           2
#define GAMEBOULDERDASHCOLORINDEXBOULDER         3
#define GAMEBOULDERDASHCOLORINDEXDIAMOND         4
#define GAMEBOULDERDASHCOLORINDEXWALL            5
#define GAMEBOULDERDASHCOLORINDEXNPCUP           6
#define GAMEBOULDERDASHCOLORINDEXNPCDOWN         7
#define GAMEBOULDERDASHCOLORINDEXNPCLEFT         8
#define GAMEBOULDERDASHCOLORINDEXNPCRIGHT        9
#define GAMEBOULDERDASHCOLORINDEXBOMBINACTIVE   10
#define GAMEBOULDERDASHCOLORINDEXBOMBACTIVE01   11
#define GAMEBOULDERDASHCOLORINDEXBOMBACTIVE02   12
#define GAMEBOULDERDASHCOLORINDEXBOMBACTIVE03   13
#define GAMEBOULDERDASHCOLORINDEXBOMBACTIVE04   14
#define GAMEBOULDERDASHCOLORINDEXBOMBACTIVE05   15
#define GAMEBOULDERDASHCOLORINDEXBOMBACTIVE06   16
#define GAMEBOULDERDASHCOLORINDEXBOMBACTIVE07   17
#define GAMEBOULDERDASHCOLORINDEXBOMBACTIVE08   18
#define GAMEBOULDERDASHCOLORINDEXBOMBACTIVE09   19
#define GAMEBOULDERDASHCOLORINDEXBOMBDESTROYED  20
#define GAMEBOULDERDASHCOLORINDEXDOORINACTIVE   21
#define GAMEBOULDERDASHCOLORINDEXDOORACTIVE     22

#define GAMEBOULDERDASHLEVELONE     1
#define GAMEBOULDERDASHLEVELTWO     2
#define GAMEBOULDERDASHLEVELTHREE   3
#define GAMEBOULDERDASHLEVELFOUR    4
#define GAMEBOULDERDASHSTARTLEVEL   1
#define GAMEBOULDERDASHMAXLEVEL     4

#define GAMEBOULDERDASHLEVELONEFUSESTEPDELAY     5000
#define GAMEBOULDERDASHLEVELTWOFUSESTEPDELAY    10000
#define GAMEBOULDERDASHLEVELTHREEFUSESTEPDELAY  20000
#define GAMEBOULDERDASHLEVELFOURFUSESTEPDELAY   20000

#define GAMEBOULDERDASHSOUTROANIMATIONFAILDELAY     75
#define GAMEBOULDERDASHSOUTROANIMATIONSUCCESSDELAY 100
#define GAMEBOULDERDASHSOUTRODELAY                3000

enum rockyMoveDirection { rmdUp, rmdDown, rmdLeft, rmdRight };

static colorRGB globalBoulderdashColors[22] = {
  COLOR_BROWN,      // Dirt
  COLOR_BLUE,       // Rocky
  COLOR_WHITE,      // Boulder
  COLOR_TEAL,       // Diamond
  COLOR_PURPLE,     // Wall
  COLOR_GREEN,      // NPC Up
  COLOR_GREEN,      // NPC Down
  COLOR_GREEN,      // NPC Left
  COLOR_GREEN,      // NPC Right
  COLOR_RED_LOW,    // Bomb inactive
  COLOR_RED,        // Bomb active 1
  COLOR_RED_LOW,    // Bomb active 2
  COLOR_RED,        // Bomb active 3
  COLOR_RED_LOW,    // Bomb active 4
  COLOR_RED,        // Bomb active 5
  COLOR_RED_LOW,    // Bomb active 6
  COLOR_RED,        // Bomb active 7
  COLOR_RED_LOW,    // Bomb active 8
  COLOR_RED,        // Bomb active 9
  COLOR_RED,        // Bomb detroyed
  COLOR_YELLOW_LOW, // Door inactive
  COLOR_YELLOW      // Door active
};

class NG8x8RGBMatrixGameBoulderdash : public NGCustom8x8RGBMatrixGame {
    
private:
    NGColorDotMatrixBinaryDigit *_lives;
    NGColorDotMatrixFuse *_fuse;
    int _maze[GAMEBOULDERDASHMAZESIZEY][GAMEBOULDERDASHMAZESIZEX];
    long _lastGravityMove = 0;
    long _lastNPCMove = 0;
    long _lastFuseStep = 0;
    int _fuseStepDelay = 0;
    long _lastRockyBlinked = 0;
    byte _rockyBlinkIndex = 0;
    byte _livesCounter = GAMEBOULDERDASHLIVES;
    byte _fuseValue = GAMEBOULDERDASHMAXFUSE;
    byte _viewPosX = 0;
    byte _viewPosY = 0;
    byte _level = GAMEBOULDERDASHSTARTLEVEL;
    byte _levelDiamonds = 0;
    bool _levelFinished = false;
    bool _doorEntered = false;
    bool _levelRetry = false;
    byte _posXRocky = 0;
    byte _posYRocky = 0;
    bool _inStartUpAnimation = false;
    int _startUpAnimationStep = -1;
    long _lastStartUpAnimationStep = 0;
    long _lastBombIgnition = 0;
    
    void _resetMaze();
    
    bool _isColorIndexBomb(int index);
    
    void _computeGravity();
    
    void _computeNPC();
    
    void _initLevel();
    
    void _initLevelTestMaze();

    void _initLevelOneMaze();
    
    void _initLevelTwoMaze();
    
    void _initLevelThreeMaze();
    
    void _initLevelFourMaze();
    
    void _generateNPCUp(byte x, byte y);
    
    void _generateNPCDown(byte x, byte y);
    
    void _generateNPCLeft(byte x, byte y);
    
    void _generateNPCRight(byte x, byte y);
    
    void _generateNPC(byte x, byte y);
    
    void _generateNPC(byte x, byte y, byte kind);
    
    void _generateVoid(byte x, byte y);
    
    void _generateDirt(byte x, byte y);
    
    void _generateDiamond(byte x, byte y);
    
    void _generateDoor(byte x, byte y);
    
    void _generateBomb(byte x, byte y);
    
    void _generateBoulder(byte x, byte y);
    
    void _generateBoulderLine(byte topX, byte topY, byte bottomX, byte bottomY);
    
    void _generateWall(byte x, byte y);
    
    void _generateWallLine(byte topX, byte topY, byte bottomX, byte bottomY);
    
    void _generateLine(byte topX, byte topY, byte bottomX, byte bottomY, byte solid);
    
    void _generateVoidLine(byte topX, byte topY, byte bottomX, byte bottomY);
    
    void _generateVoidRect(byte topX, byte topY, byte bottomX, byte bottomY);
    
    void _generateDirtRect(byte topX, byte topY, byte bottomX, byte bottomY);
    
    void _generateSolidRect(byte topX, byte topY, byte bottomX, byte bottomY, byte solid);
    
    void _generateBoulderRectWithVoid(byte topX, byte topY, byte bottomX, byte bottomY);
    
    void _generateBoulderRectWithDiamonds(byte topX, byte topY, byte bottomX, byte bottomY);
    
    void _generateBoulderRect(byte topX, byte topY, byte bottomX, byte bottomY, byte filler);
    
    void _generateWallRectWithVoid(byte topX, byte topY, byte bottomX, byte bottomY);
    
    void _generateWallRect(byte topX, byte topY, byte bottomX, byte bottomY, byte filler);
    
    bool _checkBomb();
    
    void _computeBomb();
    
    void _computeDoor();
    
    void _clearRocky();
    
    void _computeRocky();
    
    bool _checkRocky(rockyMoveDirection direction);
    
    void _renderRocky();
    
    void _calculateViewPos();
    
    void _ownJoystickLoop();
    
    void _ownRender();
    
    void _ownIntro();
    
    void _ownIntroAnimation();
    
    void _ownOutro();
    
    void _ownLevelOutroFail();
    
    void _ownLevelOutroSuccess();

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
