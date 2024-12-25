//
//  NGColorDotMatrixEffectSnowfall.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 22.12.24.
//

#ifndef NGColorDotMatrixEffectSnowfall_h
#define NGColorDotMatrixEffectSnowfall_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGIEffect.h"
#include "NGIPaintableComponent.h"

#define DEFEFFECTDELAY 250

class NGColorDotMatrixEffectSnowfall: public NGIEffect {
    
private:
    NGIPaintableComponent *_ipc;
    int _snow[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    byte _solid[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int _delay = DEFEFFECTDELAY;
    long _lastUpdate = 0;
    
protected:
    void _create(NGIPaintableComponent *ipc);
    
public:
    NGColorDotMatrixEffectSnowfall(NGIPaintableComponent *ipc);
    
    void initialize();
    
    void processingLoop();
};

#endif /* NGColorDotMatrixEffectSnowfall_h */
