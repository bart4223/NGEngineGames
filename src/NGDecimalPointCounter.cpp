//
//  NGDecimalPointCounter.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 04.03.23.
//

#include "NGDecimalPointCounter.h"

NGDecimalPointCounter::NGDecimalPointCounter(NGIPaintableComponent *pc) {
    _create(pc, COLOR_BLUE);
}

NGDecimalPointCounter::NGDecimalPointCounter(NGIPaintableComponent *pc, colorRGB color) {
    _create(pc, color);
}

void NGDecimalPointCounter::_create(NGIPaintableComponent *pc,  colorRGB color) {
    _pc = pc;
    _digit = new NGColorDotMatrixDecimalDigit(_pc);
    _digit->setColor(color);
}

void NGDecimalPointCounter::_calculateCurrentMaxDigits() {
    _currentMaxDigits = _maxDigits;
    if (!_showMaxDigits) {
        _currentMaxDigits = 1;
        long tens = 10;
        for (int i = 0; i < _currentMaxDigits; i++) {
            if (_counter / tens == 0) {
                break;
            } else {
                _currentMaxDigits++;
            }
            tens = tens * 10;
        }
    }
}

void NGDecimalPointCounter::_render() {
    long counter = _counter;
    for (int i = 0; i < _currentMaxDigits; i++) {
        _digit->beginUpdate();
        _digit->setPosX(_posX + _animationPosXOffset + (_digit->PIXELCOUNT * (_currentMaxDigits - i - 1)));
        _digit->setPosY(_posY);
        _digit->setValue(counter % 10);
        _digit->endUpdate();
        counter = counter / 10;
    }
}

void NGDecimalPointCounter::initialize() {
    
}

void NGDecimalPointCounter::setIsAnimationEnabled(bool animationenabled) {
    _isAnimationEnabled = animationenabled;
}

void NGDecimalPointCounter::setAnimationDelay(int animationdelay) {
    _animationDelay = animationdelay;
}

void NGDecimalPointCounter::setMaxDigits(byte digits) {
    _maxDigits = digits;
}

void NGDecimalPointCounter::setShowMaxDigits(bool showmaxdigits) {
    _showMaxDigits = showmaxdigits;
}

void NGDecimalPointCounter::setPosX(int x) {
    _posX = x;
}

void NGDecimalPointCounter::setPosY(int y) {
    _posY = y;
}

void NGDecimalPointCounter::setCounter(long counter) {
    if (_counter != counter) {
        _counter = counter;
        _calculateCurrentMaxDigits();
        _currentAnimationDirection = pcadNone;
        _animationPosXOffset = 0;
        if (_isAnimationEnabled) {
            _hasAnimation = (_digit->PIXELCOUNT * _digit->getScale() * _currentMaxDigits + _posX) > _pc->getWidth();
            if (_hasAnimation) {
                if (_posX < 0) {
                    _currentAnimationDirection = pcadRight;
                } else {
                    _currentAnimationDirection = pcadLeft;
                }
            }
        }
        _isInvalid = true;
    }
}

long NGDecimalPointCounter::getCounter() {
    return _counter;
}

void NGDecimalPointCounter::incrementCounter() {
    incrementCounter(1);
}

void NGDecimalPointCounter::incrementCounter(int step) {
    setCounter(getCounter() + step);
}

void NGDecimalPointCounter::decrementCounter() {
    decrementCounter(1);
}

void NGDecimalPointCounter::decrementCounter(int step)  {
    if (getCounter() > 0) {
        if (getCounter() - step < 0) {
            setCounter(0);
        } else {
            setCounter(getCounter() - step);
        }
    }
}

void NGDecimalPointCounter::processingLoop() {
    if (_isInvalid) {
        _render();
        _isInvalid = false;
    } else if (_hasAnimation && (millis() - _lastAnimation) > _animationDelay) {
        switch(_currentAnimationDirection) {
            case pcadLeft:
                _animationPosXOffset--;
                if ((_digit->PIXELCOUNT * _digit->getScale() * _currentMaxDigits + _posX + ((_animationPosXOffset + _digit->getScale()) * _digit->getScale())) < _pc->getWidth()) {
                    _currentAnimationDirection = pcadRight;
                }
                _render();
                break;
            case pcadRight:
                _animationPosXOffset++;
                if (_posX + _animationPosXOffset >= _posX) {
                    _currentAnimationDirection = pcadLeft;
                }
                _render();
                _pc->beginUpdate();
                for (int y = 0; y < _digit->PIXELCOUNT * _digit->getScale(); y++) {
                    _pc->drawPoint(_posX + _animationPosXOffset - 1, _posY + y, COLOR_BLACK);
                }
                _pc->endUpdate();
                break;
        }
        _lastAnimation = millis();
    }
}
