//
//  NGSpriteDiamond.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.03.23.
//

#ifndef NGSpriteDiamond_h
#define NGSpriteDiamond_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGCustomSprite.h"

#define BLINKDELAY 200

class NGSpriteDiamond : public NGCustomSprite {
   
private:
    long _lastBlink = 0;
    bool _blink = false;
    
protected:
    void _create(NGIPaintableComponent *ipc);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteDiamond(NGIPaintableComponent *ipc);
};

#endif /* NGSpriteDiamond_h */
