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
    _digit = new NGColorDotMatrixDecimalDigit(pc);
    _digit->setColor(color);
}

void NGDecimalPointCounter::_render() {
    int counter = _counter;
    int maxdigits = _maxDigits;
    for (int i = 0; i < maxdigits; i++) {
        _digit->beginUpdate();
        _digit->setPosX(_posX + (8 * (maxdigits - i - 1)));
        _digit->setPosY(_posY);
        _digit->setValue(counter % 10);
        _digit->endUpdate();
        counter = counter / 10;
    }
}

void NGDecimalPointCounter::initialize() {
    
}

void NGDecimalPointCounter::setMaxDigits(byte digits) {
    _maxDigits = digits;
}

void NGDecimalPointCounter::setPosX(int x) {
    _posX = x;
}

void NGDecimalPointCounter::setPosY(int y) {
    _posY = y;
}

void NGDecimalPointCounter::setCounter(int counter) {
    _counter = counter;
    _isInvalid = true;
}

int NGDecimalPointCounter::getCounter() {
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
    }
}
