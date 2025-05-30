//
//  NGColorDotMatrixEffectZini.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 06.05.24.
//

#ifndef NGColorDotMatrixEffectZini_h
#define NGColorDotMatrixEffectZini_h

#include <Arduino.h>
#include <NGIEffect.h>
#include <NGIPaintableComponent.h>
#include <NGColorDotMatrixGradientPoint.h>

#define DEFZINICOLOR        COLOR_RED
#define DEFBACKGROUNDCOLOR  COLOR_BLACK
#define DEFGRADIENTSTAGES   10
#define DEFZINIDELAY        10

enum ziniDirection { zdLeft, zdRight, zdUp, zdDown };

class NGColorDotMatrixEffectZini: public NGIEffect {
  
private:
    NGIPaintableComponent *_ipc;
    NGColorDotMatrixGradientPoint *_gp;
    int _posX = 0;
    int _posY = 0;
    int _maxPosX = 0;
    int _maxPosY = 0;
    int _gradientX = 0;
    int _gradientY = 0;
    ziniDirection _direction;
    long _delay;
    bool _noDelay = false;
    int _ziniDelay = DEFZINIDELAY;
    int _defziniDelay = DEFZINIDELAY;
    bool _randomDelay = true;
    colorRGB _backgroundColor = DEFBACKGROUNDCOLOR;
    
protected:
    void _create(NGIPaintableComponent *ipc, colorRGB color, byte gradientstages, int delay);
    
    void _render();
    
    void _diceDirection();
    
public:
    NGColorDotMatrixEffectZini(NGIPaintableComponent *ipc);
    
    NGColorDotMatrixEffectZini(NGIPaintableComponent *ipc, colorRGB color, byte gradientstages);
    
    NGColorDotMatrixEffectZini(NGIPaintableComponent *ipc, colorRGB color, byte gradientstages, int delay);
    
    void setRandomDelay(bool randomDelay);
    
    void setBackgroundColor(colorRGB backgroundcolor);
    
    void initialize();
    
    void processingLoop();
};

#endif /* NGColorDotMatrixEffectZini_h */
