//
//  NGSpriteRocky.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.03.23.
//

#ifndef NGSpriteRocky_h
#define NGSpriteRocky_h

#include <Arduino.h>
#include <NGCustomSprite.h>

#define BLINKDELAY 500

class NGSpriteRocky : public NGCustomSprite {
    
private:
    long _lastBlink = 0;
    bool _blink = false;
    
protected:
    void _create(NGIPaintableComponent *ipc, bool transparent);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteRocky(NGIPaintableComponent *ipc);
    
    NGSpriteRocky(NGIPaintableComponent *ipc, bool transparent);
};

#endif /* NGSpriteRocky_h */
