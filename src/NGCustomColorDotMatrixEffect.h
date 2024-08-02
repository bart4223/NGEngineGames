//
//  NGCustomColorDotMatrixEffect.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 02.08.24.
//

#ifndef NGCustomColorDotMatrixEffect_h
#define NGCustomColorDotMatrixEffect_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class NGCustomColorDotMatrixEffect {
    
public:
    virtual void processingLoop();
};

#endif /* NGCustomColorDotMatrixEffect_h */
