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

void NGColorOLED::clearLine(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y2, COLOR_BLACK);
}

void NGColorOLED::drawLine(int x1, int y1, int x2, int y2, colorRGB color) {
    _display->drawLine(x1 * _scale, y1 * _scale, x2 * _scale, y2 * _scale, _getColor(color));
}

void NGColorOLED::clearRect(int top, int left, int bottom, int right) {
    fillRect(top, left, bottom, right, COLOR_BLACK);
}

void NGColorOLED::drawRect(int top, int left, int bottom, int right, colorRGB color) {
    if (_scale == DEFCOLOROLEDSCALE) {
        _display->drawRect(left, top, right - left, bottom - top, _getColor(color));
    } else {
        _display->drawRect(left * _scale, top * _scale, (right - left) * _scale, (bottom - top) * _scale, _getColor(color));
    }
    return true;
}

void NGColorOLED::fillRect(int top, int left, int bottom, int right, colorRGB color) {
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

void NGColorOLED::drawImage(int coord[][2], colorRGB color, int size) {
    drawImage(0, 0, coord, color, size);
}

void NGColorOLED::drawImage(int offsetX, int offsetY, int coord[][2], colorRGB color, int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(offsetX + coord[i][0], offsetY + coord[i][1], color);
    }
    endUpdate();
}

void NGColorOLED::drawImage(int coord[][2], byte color[][3], int size) {
    drawImage(0, 0, coord, color, size);
}

void NGColorOLED::drawImage(int offsetX, int offsetY, int coord[][2], byte color[][3], int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(offsetX + coord[i][0], offsetY + coord[i][1], { color[i][0], color[i][1], color[i][2] });
    }
    endUpdate();
}
