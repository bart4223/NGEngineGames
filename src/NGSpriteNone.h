//
//  NGSpriteNone.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 27.03.23.
//

#ifndef NGSpriteNone_h
#define NGSpriteNone_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGCustomSprite.h"

class NGSpriteNone : public NGCustomSprite {
   
protected:
    void _create(NGIPaintableComponent *ipc, bool transparent);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteNone(NGIPaintableComponent *ipc);

    NGSpriteNone(NGIPaintableComponent *ipc, bool transparent);
};

#endif /* NGSpriteNone_h */
