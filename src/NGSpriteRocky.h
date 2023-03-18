//
//  NGSpriteRocky.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.03.23.
//

#ifndef NGSpriteRocky_h
#define NGSpriteRocky_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGCustomSprite.h"

#define BLINKDELAY 500

class NGSpriteRocky : public NGCustomSprite {
   
private:
    long _lastBlink = 0;
    bool _blink = false;
    
protected:
    void _create(NGIPaintableComponent *ipc);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteRocky(NGIPaintableComponent *ipc);
};

#endif /* NGSpriteRocky_h */
