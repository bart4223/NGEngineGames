//
//  NGSpriteBoulder.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 19.03.23.
//

#ifndef NGSpriteBoulder_h
#define NGSpriteBoulder_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGCustomSprite.h"

class NGSpriteBoulder : public NGCustomSprite {
   
protected:
    void _create(NGIPaintableComponent *ipc, bool transparent);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteBoulder(NGIPaintableComponent *ipc);
    
    NGSpriteBoulder(NGIPaintableComponent *ipc, bool transparent);
};

#endif /* NGSpriteBoulder_h */
