//
//  NGColorOLED.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 05.03.23.
//

#include "NGColorOLED.h"

NGColorOLED::NGColorOLED() {
    _create();
}

void NGColorOLED::_create() {
    _display = new Adafruit_SSD1331(SPI_SC, SPI_DC, SPI_RST);
}

int NGColorOLED::_getColor(colorRGB c) {
    return convertColorRGBToInt(c);
}

void NGColorOLED::initialize() {
    if (_updateCount == 0) {
        _display->begin();
    }
    _updateCount++;
}

int NGColorOLED::getWidth() {
    return _display->TFTWIDTH;
}

int NGColorOLED::getHeight() {
    return _display->TFTHEIGHT;
}

void NGColorOLED::beginUpdate() {
    _display->startWrite();
}

void NGColorOLED::endUpdate() {
    if (_updateCount > 0) {
        _updateCount--;
    }
    if (_updateCount == 0) {
        _display->endWrite();
    }
}

void NGColorOLED::setScale(int scale) {
    _scale = scale;
}

void NGColorOLED::clear() {
    _display->fillScreen(_getColor(COLOR_BLACK));
}

bool NGColorOLED::drawPoint(int x, int y, colorRGB color) {
    if (_scale == DEFCOLOROLEDSCALE) {
        _display->writePixel(x, y, _getColor(color));
    } else {
        _display->fillRect(x * _scale, y * _scale, _scale, _scale, _getColor(color));
    }
}
