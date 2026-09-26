//
//  NGColorDotMatrixGameDot.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.12.22.
//

#ifndef NGColorDotMatrixGameDot_h
#define NGColorDotMatrixGameDot_h

#include <Arduino.h>
#include <Games/NGCustomColorDotMatrixGame.h>

#define DEFDOTMAXCATCHTIME 1000
#define DOTCATCHDELAY       200

#define GAMEDOTCOLORSCOREOFF { .red = 5, .green = 5, .blue = 5 }
#define GAMEDOTCOLORSCOREON COLOR_BLUE
#define GAMEDOTINTRODELAY   100

#define GAMESPRITEDOTID    1
#define GAMESPRITEPLAYERID 2

#define GAMEDOTCATCHTIMEFACTOR 1.5

class NGColorDotMatrixGameDot : public NGCustomColorDotMatrixGame {
    
private:
    byte _posXDot;
    byte _posYDot;
    byte _prevPosXDot;
    byte _prevPosYDot;
    long _dotSpawned;
    byte _posXPlayer;
    byte _posYPlayer;
    byte _prevPosXPlayer;
    byte _prevPosYPlayer;
    colorRGB _colorPlayer;
    int _dotMaxCatchTime;
    byte _maxGameDotX;
    byte _maxGameDotY;
    byte _minGameDotDiff;
    byte _maxGameDotDiff;
    byte _introPlayerX = 0;
    byte _introPlayerY = 0;
    
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
    
    void _ownIntroAnimation();
    
public:
    NGColorDotMatrixGameDot();
    
    void registerColorDotMatrix(NGIPaintableComponent *ipc);

    void registerDotSprite(NGCustomSprite *sprite);

    void registerPlayerSprite(NGCustomSprite *sprite);
};

#endif /* NGColorDotMatrixGameDot_h */
