//
//  NGColorDotMatrixGameSnake.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 22.12.22.
//

#ifndef NGColorDotMatrixGameSnake_h
#define NGColorDotMatrixGameSnake_h

#include <Arduino.h>
#include <NGCustomColorDotMatrixGame.h>

#define GAMESNAKECOLORSCOREOFF { .red = 5, .green = 5, .blue = 5 }
#define GAMESNAKECOLORSCOREON COLOR_BLUE

#define GAMESNAKEMAXMAZESIZEX   16
#define GAMESNAKEMAXMAZESIZEY   16

#define GAMESNAKEMOVEDELAY              500
#define GAMESNAKEFINISHDELAY           3000
#define GAMESNAKEINTRODELAY             100
#define GAMESNAKEINTRODONEDELAY         500
#define GAMESNAKEOUTRODELAY             100
#define GAMESNAKEINTROANIMATIONSTEPS      8

class NGColorDotMatrixGameSnake : public NGCustomColorDotMatrixGame {
  
private:
    byte _maxGameSnakeX;
    byte _maxGameSnakeY;
    byte _posXSnake;
    byte _posYSnake;
    int _directionXSnake;
    int _directionYSnake;
    int _snakeThreshold;
    byte _posXDiamond;
    byte _posYDiamond;
    byte _maze[GAMESNAKEMAXMAZESIZEY][GAMESNAKEMAXMAZESIZEX];
    colorRGB _colorSnake;
    long _lastSnakeMove = 0;
    int _introAnimationIndex = 0;
    
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
    
    void _ownIntroAnimation();
    
    void _ownOutro();
    
public:
    NGColorDotMatrixGameSnake();
    
    void registerColorDotMatrix(NGIPaintableComponent *ipc);
};

#endif /* NGColorDotMatrixGameSnake_h */
