//
//  NGSpriteHeart.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 15.03.23.
//

#ifndef NGSpriteHeart_h
#define NGSpriteHeart_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGCustomSprite.h"

class NGSpriteHeart : public NGCustomSprite {
   
protected:
    void _create(NGIPaintableComponent *ipc);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteHeart(NGIPaintableComponent *ipc);
};

#endif /* NGSpriteHeart_h */
