//
//  NGColorDotMatrixEffectSnowfall.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 22.12.24.
//

#include "NGColorDotMatrixEffectSnowfall.h"

NGColorDotMatrixEffectSnowfall::NGColorDotMatrixEffectSnowfall(NGIPaintableComponent *ipc) {
    _create(ipc);
}

void NGColorDotMatrixEffectSnowfall::_create(NGIPaintableComponent *ipc) {
    _ipc = ipc;
}

void NGColorDotMatrixEffectSnowfall::initialize() {
    
}

void NGColorDotMatrixEffectSnowfall::processingLoop() {
    if (_lastUpdate == 0 || millis() - _lastUpdate > _delay) {
        _ipc->beginUpdate();
        _ipc->clear();
        for (int i = 0; i < sizeof(_snow) / sizeof(_snow[0]); i++) {
            if (random(0, 10) == 5) {
                if ((_snow[i] & 0x02) == 0x00) {
                    _snow[i] = _snow[i] | 0x01;
                }
            }
            colorRGB c;
            int x = 0x01;
            for (int j = 0; j < _ipc->getHeight() - 1; j++) {
                if ((_snow[i] & x) != 0x00) {
                    c.red = 50 + random(0, 100);
                    c.green = 100 + random(0, 100);
                    c.blue = 100 + random(0, 150);
                    _ipc->drawPoint(i, j, c);
                }
                x = x << 1;
            }
            _snow[i] = _snow[i] << 1;
        }
        _ipc->drawLine(0, _ipc->getHeight() - 1, _ipc->getWidth() - 1, _ipc->getHeight() - 1, COLOR_WHITE);
        _ipc->endUpdate();
        _lastUpdate = millis();
    }
}
