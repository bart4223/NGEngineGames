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

#define GAMETETRISMAXMAZESIZEX    16
#define GAMETETRISMAXMAZESIZEY    16

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

enum tetrisMode { tmMinimal, tmNormal };
enum tetrominoKind { tkNone, tkI, tkL };

class NGColorDotMatrixGameTetris : public NGCustomColorDotMatrixGame {
 
private:
    byte _maxGameTetrisX;
    byte _maxGameTetrisY;
    byte _posXTetromino = 0;
    byte _posYTetromino = 0;
    tetrominoKind _tetrominoKind = tkNone;
    byte _tetrominoSequence = 0;
    byte _tetrominoColor = 0;
    int _maze[GAMETETRISMAXMAZESIZEY][GAMETETRISMAXMAZESIZEX];
    long _lastTetrominoMove = 0;
    bool _inStartUpAnimation = false;
    int _startUpAnimationStep = -1;
    long _lastStartUpAnimationStep = 0;
    tetrisMode _tetrisMode = tmNormal;

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
    
    void registerColorDotMatrix(NGIPaintableComponent *ipc);
};

#endif /* NGColorDotMatrixGameTetris_h */
