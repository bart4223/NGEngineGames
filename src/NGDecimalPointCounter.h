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

class NGDecimalPointCounter {
    
private:
    int _counter = 0;
    NGColorDotMatrixDecimalDigit *_digit;
    byte _maxDigits = DEFPOINTCOUNTERMAXDIGITS;
    int _posX = 0;
    int _posY = 0;
    bool _isInvalid = false;
    
protected:
    void _create(NGIPaintableComponent *pc, colorRGB color);
    
    void _render();
    
public:
    NGDecimalPointCounter(NGIPaintableComponent *pc);
    
    NGDecimalPointCounter(NGIPaintableComponent *pc, colorRGB color);
  
    void initialize();
    
    void setMaxDigits(byte digits);
    
    void setPosX(int x);
    
    void setPosY(int y);
    
    void setCounter(int counter);
    
    int getCounter();
    
    void incrementCounter();
    
    void incrementCounter(int step);
    
    void decrementCounter();
    
    void decrementCounter(int step);
    
    void processingLoop();
};

#endif /* NGDecimalPointCounter_h */
