//
//  NGColorDotMatrixEffectRetroRibbons.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 02.08.24.
//

#ifndef NGColorDotMatrixEffectRetroRibbons_h
#define NGColorDotMatrixEffectRetroRibbons_h

#include <Arduino.h>
#include <NGIEffect.h>
#include <NGIPaintableComponent.h>

#define COLORONE    { .red = 0x33, .green = 0x09, .blue = 0x0B }
#define COLORTWO    { .red = 0x7D, .green = 0x0D, .blue = 0x1F }
#define COLORTHREE  { .red = 0x9E, .green = 0x39, .blue = 0x26 }
#define COLORFOUR   { .red = 0x98, .green = 0x92, .blue = 0x26 }
#define COLORFIVE   { .red = 0x00, .green = 0x6D, .blue = 0x19 }

#define DEFEFFECTDELAY 100

class NGColorDotMatrixEffectRetroRibbons: public NGIEffect {
    
private:
    NGIPaintableComponent *_ipc;
    byte _stripHeight;
    byte _stripIndex;
    long _lastUpdate = 0;
    int _delay = DEFEFFECTDELAY;
    
protected:
    void _create(NGIPaintableComponent *ipc);
    
public:
    NGColorDotMatrixEffectRetroRibbons(NGIPaintableComponent *ipc);
    
    void initialize();
    
    void processingLoop();
};

#endif /* NGColorDotMatrixEffectRetroRibbons_h */
