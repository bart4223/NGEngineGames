//
//  NGSpriteDirt.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 14.03.23.
//

#ifndef NGSpriteDirt_h
#define NGSpriteDirt_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGCustomSprite.h"

class NGSpriteDirt : public NGCustomSprite {
   
protected:
    void _create(NGIPaintableComponent *ipc);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteDirt(NGIPaintableComponent *ipc);
};

#endif /* NGSpriteDirt_h */
