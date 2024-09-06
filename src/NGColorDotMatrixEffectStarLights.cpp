//
//  NGColorDotMatrixEffectStarLights.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 06.09.24.
//

#include "NGColorDotMatrixEffectStarLights.h"

NGColorDotMatrixEffectStarLights::NGColorDotMatrixEffectStarLights(NGIPaintableComponent *ipc) {
    _create(ipc);
}

void NGColorDotMatrixEffectStarLights::_create(NGIPaintableComponent *ipc) {
    _ipc = ipc;
}

void NGColorDotMatrixEffectStarLights::initialize() {
    
}

void NGColorDotMatrixEffectStarLights::processingLoop() {
    if (_lastUpdate == 0 || millis() - _lastUpdate > _delay) {
        colorRGB c;
        switch(random(0, 9)) {
            case 0:
            case 2:
            case 4:
            case 6:
            case 8:
                c = COLOR_BLACK;
                break;
            case 1:
                c = COLOR_RED;
                break;
            case 3:
                c = COLOR_BLUE;
                break;
            case 5:
                c = COLOR_GREEN;
                break;
            case 7:
                c = COLOR_YELLOW;
                break;
            }
        _ipc->drawPoint(random(0, _ipc->getWidth()), random(0, _ipc->getHeight()),  c);
        _lastUpdate = millis();
    }
}
