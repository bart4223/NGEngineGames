//
//  NGDecimalPointCounter.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 04.03.23.
//

#ifndef NGDecimalPointCounter_h
#define NGDecimalPointCounter_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGColorDotMatrixDecimalDigit.h>

#define DEFPOINTCOUNTERMAXDIGITS 1
#define DEFPOINTCOUNTERANIMATIONDELAY 500

enum pointCounterAnimationDirection { pcadNone, pcadLeft, pcadRight };

class NGDecimalPointCounter {
    
private:
    long _counter = 0;
    NGIPaintableComponent *_pc;
    NGColorDotMatrixDecimalDigit *_digit;
    byte _maxDigits = DEFPOINTCOUNTERMAXDIGITS;
    byte _currentMaxDigits = 0;
    int _posX = 0;
    int _posY = 0;
    bool _isInvalid = false;
    bool _showMaxDigits = true;
    bool _isAnimationEnabled = false;
    bool _hasAnimation = false;
    long _lastAnimation = 0;
    int _animationDelay = DEFPOINTCOUNTERANIMATIONDELAY;
    pointCounterAnimationDirection _currentAnimationDirection = pcadNone;
    int _animationPosXOffset = 0;
    
protected:
    void _create(NGIPaintableComponent *pc, colorRGB color);
    
    void _calculateCurrentMaxDigits();
    
    void _render();
    
public:
    NGDecimalPointCounter(NGIPaintableComponent *pc);
    
    NGDecimalPointCounter(NGIPaintableComponent *pc, colorRGB color);
  
    void initialize();
    
    void setMaxDigits(byte digits);
    
    void setShowMaxDigits(bool showmaxdigits);
    
    void setIsAnimationEnabled(bool animationenabled);
    
    void setAnimationDelay(int animationdelay);
    
    void setPosX(int x);
    
    void setPosY(int y);
    
    void setCounter(long counter);
    
    long getCounter();
    
    void incrementCounter();
    
    void incrementCounter(int step);
    
    void decrementCounter();
    
    void decrementCounter(int step);
    
    void processingLoop();
};

#endif /* NGDecimalPointCounter_h */
