//
//  NGSpriteLaserbeam.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 26.03.23.
//

#ifndef NGSpriteLaserbeam_h
#define NGSpriteLaserbeam_h

#include <Arduino.h>
#include <NGCustomSprite.h>

class NGSpriteLaserbeam : public NGCustomSprite {
   
protected:
    void _create(NGIPaintableComponent *ipc, bool transparent);
    
    void _doRender(int x, int y);
    
public:
    NGSpriteLaserbeam(NGIPaintableComponent *ipc);

    NGSpriteLaserbeam(NGIPaintableComponent *ipc, bool transparent);
};

#endif /* NGSpriteLaserbeam_h */
