//
//  NGColorDotMatrixEffectRetroColors.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 02.08.24.
//

#include "NGColorDotMatrixEffectRetroColors.h"

NGColorDotMatrixEffectRetroColors::NGColorDotMatrixEffectRetroColors(NGIPaintableComponent *ipc) {
    _create(ipc);
}

void NGColorDotMatrixEffectRetroColors::_create(NGIPaintableComponent *ipc) {
    _ipc = ipc;
}

void NGColorDotMatrixEffectRetroColors::processingLoop() {
    int h = _ipc->getHeight() / 5;
    byte ci = _start;
    colorRGB color;
    _ipc->beginUpdate();
    for (int y = 0; y < _ipc->getHeight(); y++) {
        if (y % h == 0) {
            ci++;
            if (ci > 4) {
                ci = 0;
            }
        }
        switch(ci) {
            case 0:
                color = COLORONE;
                break;
            case 1:
                color = COLORTWO;
                break;
            case 2:
                color = COLORTHREE;
                break;
            case 3:
                color = COLORFOUR;
                break;
            case 4:
                color = COLORFIVE;
                break;
        }
        _ipc->drawLine(0, y, _ipc->getWidth() - 1, y, color);
    }
    _ipc->endUpdate();
    _start++;
    if (_start > 4) {
        _start = 0;
    }
    delay(1000);
}
