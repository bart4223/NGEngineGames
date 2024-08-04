//
//  NGColorDotMatrixEffectRetroColors.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 02.08.24.
//

#ifndef NGColorDotMatrixEffectRetroColors_h
#define NGColorDotMatrixEffectRetroColors_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGIPaintableComponent.h"

#define COLORONE    { .red = 0x33, .green = 0x09, .blue = 0x0B }
#define COLORTWO    { .red = 0x7D, .green = 0x0D, .blue = 0x1F }
#define COLORTHREE  { .red = 0x9E, .green = 0x39, .blue = 0x26 }
#define COLORFOUR   { .red = 0x98, .green = 0x92, .blue = 0x26 }
#define COLORFIVE   { .red = 0x00, .green = 0x6D, .blue = 0x19 }

class NGColorDotMatrixEffectRetroColors {
    
private:
    NGIPaintableComponent *_ipc;
    byte _stripHeight;
    byte _stripIndex;
    
protected:
    void _create(NGIPaintableComponent *ipc);
    
public:
    NGColorDotMatrixEffectRetroColors(NGIPaintableComponent *ipc);
                               
    void processingLoop();
};

#endif /* NGColorDotMatrixEffectRetroColors_h */
