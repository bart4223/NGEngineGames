//
//  NGColorDotMatrixGameDot.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.12.22.
//

#ifndef NGColorDotMatrixGameDot_h
#define NGColorDotMatrixGameDot_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomColorDotMatrixGame.h>

#define MAXGAMEDOTX     6
#define MAXGAMEDOTY     7
#define MINGAMEDOTDIFF  1
#define MAXGAMEDOTDIFF  4

#define DOTMAXCATCHTIME 1000
#define DOTCATCHDELAY    200

#define GAMDEDOTCOLORSCOREOFF { .red = 5, .green = 5, .blue = 5 }
#define GAMDEDOTCOLORSCOREON COLOR_BLUE

#define GAMESPRITEDOTID    1
#define GAMESPRITEPLAYERID 2

#define GAMEDOTSCOREDIGITS 8

class NGColorDotMatrixGameDot : public NGCustomColorDotMatrixGame {
    
private:
    byte _posXDot;
    byte _posYDot;
    long _dotSpawned;
    byte _posXPlayer;
    byte _posYPlayer;
    colorRGB _colorPlayer;
    
    void _rollPlayerColor();

    void _calculateNewDotPosition();
    
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
    
public:
    NGColorDotMatrixGameDot();
};

#endif /* NGColorDotMatrixGameDot_h */
