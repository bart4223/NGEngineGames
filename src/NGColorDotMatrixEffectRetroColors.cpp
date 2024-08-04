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
    _stripHeight = _ipc->getHeight() / 5;
    _stripIndex = 0;
}

void NGColorDotMatrixEffectRetroColors::processingLoop() {
    _ipc->beginUpdate();
    for (int y = 0; y < _ipc->getHeight(); y++) {
        colorRGB color;
        switch(_stripIndex / _stripHeight) {
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
        _stripIndex++;
        if (_stripIndex >= _stripHeight * 5) {
            _stripIndex = 0;
        }
    }
    _ipc->endUpdate();
    delay(1000);
}
