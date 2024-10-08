//
//  NGColorDotMatrixEffectZini.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 06.05.24.
//

#include "NGCommon.h"
#include "NGColorDotMatrixEffectZini.h"

NGColorDotMatrixEffectZini::NGColorDotMatrixEffectZini(NGIPaintableComponent *ipc) {
    _create(ipc, DEFZINICOLOR, DEFGRADIENTSTAGES, DEFZINIDELAY);
}

NGColorDotMatrixEffectZini::NGColorDotMatrixEffectZini(NGIPaintableComponent *ipc, colorRGB color, byte gradientstages) {
    _create(ipc, color, gradientstages, DEFZINIDELAY);
}

NGColorDotMatrixEffectZini::NGColorDotMatrixEffectZini(NGIPaintableComponent *ipc, colorRGB color, byte gradientstages, int delay) {
    _create(ipc, color, gradientstages, delay);
}

void NGColorDotMatrixEffectZini::_create(NGIPaintableComponent *ipc, colorRGB color, byte gradientstages, int delay) {
    _ipc = ipc;
    _defziniDelay = delay;
    _ziniDelay = _defziniDelay;
    _gp = new NGColorDotMatrixGradientPoint(ipc, color, gradientstages, true);
    _posX = random(0, ipc->getWidth());
    _posY = random(0, ipc->getHeight());
    _maxPosX = ipc->getWidth() - 1;
    _maxPosY = ipc->getHeight() - 1;
    _diceDirection();
}

void NGColorDotMatrixEffectZini::_render() {
    _gp->beginUpdate();
    _gp->setPosition(_posX, _posY);
    _gp->setGradient(_gradientX, _gradientY);
    _gp->endUpdate();
}

void NGColorDotMatrixEffectZini::_diceDirection() {
    if (getYesOrNo()) {
        switch(random(0, 4)) {
            case 0:
                _direction = zdLeft;
                break;
            case 1:
                _direction = zdRight;
                break;
            case 2:
                _direction = zdUp;
                break;
            case 3:
                _direction = zdDown;
                break;
        }
    }
}

void NGColorDotMatrixEffectZini::setRandomDelay(bool randomDelay) {
    _randomDelay = randomDelay;
}

void NGColorDotMatrixEffectZini::setBackgroundColor(colorRGB backgroundcolor) {
    _backgroundColor = backgroundcolor;
    _ipc->fillRect(0, 0, _ipc->getWidth() - 1, _ipc->getHeight() - 1, _backgroundColor);
}

void NGColorDotMatrixEffectZini::initialize() {
    
}

void NGColorDotMatrixEffectZini::processingLoop() {
    bool ok = _delay == 0;
    if (!ok) {
        ok = millis() - _delay > _ziniDelay;
        if (ok) {
            _delay = 0;
        }
    }
    if (ok) {
        int gradient = 0;
        _render();
        switch(_direction) {
            case zdLeft:
                _gradientX--;
                gradient = _gradientX;
                break;
            case zdRight:
                _gradientX++;
                gradient = _gradientX;
                break;
            case zdUp:
                _gradientY--;
                gradient = _gradientY;
                break;
            case zdDown:
                _gradientY++;
                gradient = _gradientY;
                break;
        }
        if (abs(gradient) >= _gp->getGradientStages()) {
            _gp->clear();
            switch(_direction) {
                case zdLeft:
                    _gradientX = 0;
                    _posX--;
                    if (_posX < 0) {
                        _posX = _maxPosX;
                    }
                    break;
                case zdRight:
                    _gradientX = 0;
                    _posX++;
                    if (_posX > _maxPosX) {
                        _posX = 0;
                    }
                    break;
                case zdUp:
                    _gradientY = 0;
                    _posY--;
                    if (_posY < 0) {
                        _posY = _maxPosY;
                    }
                    break;
                case zdDown:
                    _gradientY = 0;
                    _posY++;
                    if (_posY > _maxPosY) {
                        _posY = 0;
                    }
                    break;
            }
            _render();
            _diceDirection();
            _noDelay = true;
        }
        if (!_noDelay) {
            _delay = millis();
        } else {
            _noDelay = false;
            if (_randomDelay) {
                _ziniDelay = random(0, _defziniDelay);
            }
        }
    }
}
