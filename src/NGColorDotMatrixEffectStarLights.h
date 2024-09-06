//
//  NGColorDotMatrixEffectStarLights.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 06.09.24.
//

#ifndef NGColorDotMatrixEffectStarLights_h
#define NGColorDotMatrixEffectStarLights_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGIEffect.h"
#include "NGIPaintableComponent.h"

#define DEFEFFECTDELAY 100

class NGColorDotMatrixEffectStarLights: public NGIEffect {
    
private:
    NGIPaintableComponent *_ipc;
    int _delay = DEFEFFECTDELAY;
    long _lastUpdate = 0;
    
protected:
    void _create(NGIPaintableComponent *ipc);
    
public:
    NGColorDotMatrixEffectStarLights(NGIPaintableComponent *ipc);
    
    void initialize();
    
    void processingLoop();
};

#endif /* NGColorDotMatrixEffectStarLights_h */
