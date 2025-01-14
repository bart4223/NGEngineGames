//
//  NGSpriteDot.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 20.03.23.
//

#ifndef NGSpriteDot_h
#define NGSpriteDot_h

#include <Arduino.h>
#include <NGCustomSprite.h>

class NGSpriteDot : public NGCustomSprite {
   
protected:
    void _create(NGIPaintableComponent *ipc, bool transparent);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteDot(NGIPaintableComponent *ipc);

    NGSpriteDot(NGIPaintableComponent *ipc, bool transparent);
};

#endif /* NGSpriteDot_h */
