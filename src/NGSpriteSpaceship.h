//
//  NGSpriteSpaceship.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 28.03.23.
//

#ifndef NGSpriteSpaceship_h
#define NGSpriteSpaceship_h

#include <Arduino.h>
#include <NGCustomSprite.h>

class NGSpriteSpaceship : public NGCustomSprite {
   
protected:
    void _create(NGIPaintableComponent *ipc, bool transparent, int offsetX, int offsetY);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteSpaceship(NGIPaintableComponent *ipc);

    NGSpriteSpaceship(NGIPaintableComponent *ipc, bool transparent);

    NGSpriteSpaceship(NGIPaintableComponent *ipc, bool transparent, int offsetX, int offsetY);
};

#endif /* NGSpriteSpaceship_h */
