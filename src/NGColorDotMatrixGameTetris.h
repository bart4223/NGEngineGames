//
//  NGColorDotMatrixGameTetris.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 30.12.22.
//

#ifndef NGColorDotMatrixGameTetris_h
#define NGColorDotMatrixGameTetris_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomColorDotMatrixGame.h>

#define GAMETETRISCOLORSCOREOFF { .red = 5, .green = 5, .blue = 5 }
#define GAMETETRISCOLORSCOREON COLOR_BLUE

#define GAMETETRISMAZESIZEX    7
#define GAMETETRISMAZESIZEY    8
#define GAMETETRISSCOREDIGITS  8

#define GAMETETRISMOVEDELAY    500
#define GAMETETRISFINISHDELAY 1000

#define GAMETETRISSPLASHTIMES                10
#define GAMETETRISSPLASHDELAY               200
#define GAMETETRISOUTRODELAY                100
#define GAMETETRISOUTRODPOINTCOUNTERDELAY  3000

static byte globalTetrominoColors[7][3] = {
  {255, 0, 0},
  {255, 102, 0},
  {255, 255, 0},
  {0, 255, 0},
  {0, 128, 128},
  {0, 0, 255},
  {128, 0, 128}
};

enum tetrominoKind { tkNone, tkI, tkL };

class NGColorDotMatrixGameTetris : public NGCustomColorDotMatrixGame {
 
private:
    byte _posXTetromino = 0;
    byte _posYTetromino = 0;
    tetrominoKind _tetrominoKind = tkNone;
    byte _tetrominoSequence = 0;
    byte _tetrominoColor = 0;
    int _maze[GAMETETRISMAZESIZEY][GAMETETRISMAZESIZEX];
    long _lastTetrominoMove = 0;
    bool _inStartUpAnimation = false;
    int _startUpAnimationStep = -1;
    long _lastStartUpAnimationStep = 0;

    void _resetMaze();
    
    void _clearTetromino();
    
    void _computeTetromino();
    
    void _computeMaze();
    
    void _spawnTetromino();
    
    void _persistTetromino();

    bool _checkTetromino(byte posX, byte posY, byte sequence);
    
    void _ownJoystickLoop();
    
    void _ownRender();
    
    void _ownIntro();
    
    void _ownIntroAnimation();
    
    void _ownOutro();
    
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
    NGColorDotMatrixGameTetris();
};

#endif /* NGColorDotMatrixGameTetris_h */
