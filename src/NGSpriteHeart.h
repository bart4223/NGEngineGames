//
//  NGSpriteHeart.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 15.03.23.
//

#ifndef NGSpriteHeart_h
#define NGSpriteHeart_h

#include <Arduino.h>
#include <NGCustomSprite.h>

class NGSpriteHeart : public NGCustomSprite {
   
protected:
    void _create(NGIPaintableComponent *ipc, bool transparent);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteHeart(NGIPaintableComponent *ipc);

    NGSpriteHeart(NGIPaintableComponent *ipc, bool transparent);
};

#endif /* NGSpriteHeart_h */
