//
//  NG8x8RGBMatrixGameDot.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.12.22.
//

#ifndef NG8x8RGBMatrixGameDot_h
#define NG8x8RGBMatrixGameDot_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustom8x8RGBMatrixGame.h>

#define MAXGAMEDOTX     6
#define MAXGAMEDOTY     7
#define MINGAMEDOTDIFF  1
#define MAXGAMEDOTDIFF  4

#define DOTMAXCATCHTIME 1000
#define DOTCATCHDELAY    200

#define GAMDEDOTCOLORSCOREOFF { .red = 5, .green = 5, .blue = 5 }
#define GAMDEDOTCOLORSCOREON COLOR_BLUE

#define GAMEDOTSCOREDIGITS 8

class NG8x8RGBMatrixGameDot : public NGCustom8x8RGBMatrixGame {
    
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
    
    void _doStartGame();
    
    void _doFinishGame();
    
    void _doProcessingLoop();
    
    void _ownJoystickLoop();
    
    void _ownRender();
    
public:
    NG8x8RGBMatrixGameDot();
};

#endif /* NG8x8RGBMatrixGameDot_h */
