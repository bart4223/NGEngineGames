//
//  NG8x8RGBMatrixGameSnake.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 22.12.22.
//

#ifndef NG8x8RGBMatrixGameSnake_h
#define NG8x8RGBMatrixGameSnake_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustom8x8RGBMatrixGame.h>

#define GAMESNAKECOLORSCOREOFF { .red = 5, .green = 5, .blue = 5 }
#define GAMESNAKECOLORSCOREON COLOR_BLUE

#define GAMESNAKEMAZESIZEX   7
#define GAMESNAKEMAZESIZEY   8
#define GAMESNAKESCOREDIGITS 8

#define GAMESNAKEMOVEDELAY    500
#define GAMESNAKEFINISHDELAY 1000

class NG8x8RGBMatrixGameSnake : public NGCustom8x8RGBMatrixGame {
  
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
    
public:
    NG8x8RGBMatrixGameSnake();
};

#endif /* NG8x8RGBMatrixGameSnake_h */
