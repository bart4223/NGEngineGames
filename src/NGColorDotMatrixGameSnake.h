//
//  NGColorDotMatrixGameSnake.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 22.12.22.
//

#ifndef NGColorDotMatrixGameSnake_h
#define NGColorDotMatrixGameSnake_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomColorDotMatrixGame.h>

#define GAMESNAKECOLORSCOREOFF { .red = 5, .green = 5, .blue = 5 }
#define GAMESNAKECOLORSCOREON COLOR_BLUE

#define GAMESNAKEMAZESIZEX   7
#define GAMESNAKEMAZESIZEY   8
#define GAMESNAKESCOREDIGITS 8

#define GAMESNAKEMOVEDELAY    500
#define GAMESNAKEFINISHDELAY 3000
#define GAMESNAKEINTRODELAY   100
#define GAMESNAKEOUTRODELAY   100

class NGColorDotMatrixGameSnake : public NGCustomColorDotMatrixGame {
  
private:
    byte _posXSnake;
    byte _posYSnake;
    int _directionXSnake;
    int _directionYSnake;
    int _snakeThreshold;
    byte _posXDiamond;
    byte _posYDiamond;
    byte _maze[GAMESNAKEMAZESIZEY][GAMESNAKEMAZESIZEX];
    colorRGB _colorSnake;
    long _lastSnakeMove = 0;
    
    void _rollSnakeColor();
    
    void _calculateNewDiamondPosition();
    
    void _resetMaze();
    
    void _computeMaze();
    
    bool _moveSnake();
    
protected:
    void _doInitialize();
    
    void _doStartUp();
    
    void _doStartUpDone();
    
    void _doStartGame();
    
    void _doBreakGame();
    
    void _doContinueGame();
    
    void _doFinishGame();
    
    void _doProcessingLoop();
    
    void _ownJoystickLoop();
    
    void _ownRender();
    
    void _ownIntro();
    
    void _ownOutro();
    
public:
    NGColorDotMatrixGameSnake();
};

#endif /* NGColorDotMatrixGameSnake_h */
