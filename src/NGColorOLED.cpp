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
    return _display->width();
}

int NGColorOLED::getHeight() {
    return _display->height();
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

int NGColorOLED::getScale() {
    return _scale;
}

void NGColorOLED::clear() {
    _display->fillScreen(_getColor(COLOR_BLACK));
}

bool NGColorOLED::clearPoint(int x, int y) {
    return drawPoint(x, y, COLOR_BLACK);
}

bool NGColorOLED::drawPoint(int x, int y, colorRGB color) {
    if (_scale == DEFCOLOROLEDSCALE) {
        _display->writePixel(x, y, _getColor(color));
    } else {
        _display->fillRect(x * _scale, y * _scale, _scale, _scale, _getColor(color));
    }
    return true;
}

bool NGColorOLED::fillRect(int top, int left, int bottom, int right, colorRGB color) {
    if (_scale == DEFCOLOROLEDSCALE) {
        _display->fillRect(left, top, right - left, bottom - top, _getColor(color));
    } else {
        _display->fillRect(left * _scale, top * _scale, (right - left) * _scale, (bottom - top) * _scale, _getColor(color));
    }
    return true;
}

void NGColorOLED::clearCircle(int x0, int y0, int radius) {
    drawCircle(x0, y0, radius, COLOR_BLACK);
}

void NGColorOLED::drawCircle(int x0, int y0, int radius, colorRGB color) {
    _display->drawCircle(x0 * _scale, y0 * _scale, radius * _scale, _getColor(color));
}
