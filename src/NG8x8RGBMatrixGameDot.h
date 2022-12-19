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

class NG8x8RGBMatrixGameDot : public NGCustom8x8RGBMatrixGame {
    
private:
    byte _posX;
    byte _posY;
    bool _doRender = false;
    colorRGB _color;

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
