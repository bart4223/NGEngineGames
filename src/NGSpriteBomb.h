//
//  NGSpriteBomb.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 19.03.23.
//

#ifndef NGSpriteBomb_h
#define NGSpriteBomb_h

#include <Arduino.h>
#include <NGCustomSprite.h>

class NGSpriteBomb : public NGCustomSprite {
   
protected:
    void _create(NGIPaintableComponent *ipc, bool transparent);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteBomb(NGIPaintableComponent *ipc);
    
    NGSpriteBomb(NGIPaintableComponent *ipc, bool transparent);
};

#endif /* NGSpriteBomb_h */
