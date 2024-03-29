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
    _display->begin();
}

int NGColorOLED::getWidth() {
    return _display->width();
}

int NGColorOLED::getHeight() {
    return _display->height();
}

void NGColorOLED::beginUpdate() {
    if (_updateCount == 0) {
        _display->startWrite();
    } else {
        _updateCount++;
    }
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

void NGColorOLED::setBackground(colorRGB color) {
    _background = color;
}

colorRGB NGColorOLED::getBackground() {
    return _background;
}

void NGColorOLED::clear() {
    _display->fillScreen(_getColor(_background));
}

bool NGColorOLED::clearPoint(int x, int y) {
    return drawPoint(x, y, _background);
}

bool NGColorOLED::drawPoint(int x, int y, colorRGB color) {
    drawPoint(x, y, _getColor(color));
}

bool NGColorOLED::drawPoint(int x, int y, int color) {
    if (_scale == DEFCOLOROLEDSCALE) {
        _display->writePixel(x + _offsetX, y + _offsetY, color);
    } else {
        _display->writeFillRect(x * _scale + _offsetX, y * _scale + _offsetY, _scale, _scale, color);
    }
    return true;
}

void NGColorOLED::clearLine(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y2, _background);
}

void NGColorOLED::drawLine(int x1, int y1, int x2, int y2, colorRGB color) {
    if (_scale == DEFCOLOROLEDSCALE) {
        _display->writeLine(x1, y1, x2, y2, _getColor(color));
    } else {
        int dx =  abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = dx + dy, e2;
        for(;;){
            drawPoint(x1, y1, color);
            if (x1 == x2 && y1 == y2)
                break;
            e2 = 2 * err;
            if (e2 > dy) { err += dy; x1 += sx; }
            if (e2 < dx) { err += dx; y1 += sy; }
        }
    }
}

void NGColorOLED::clearRect(int top, int left, int bottom, int right) {
    fillRect(top, left, bottom, right, _background);
}

void NGColorOLED::drawRect(int top, int left, int bottom, int right, colorRGB color) {
    drawLine(left, top, right, top, color);
    drawLine(left, top, left, bottom, color);
    drawLine(right, top, right, bottom, color);
    drawLine(left, bottom, right, bottom, color);
    return true;
}

void NGColorOLED::fillRect(int top, int left, int bottom, int right, colorRGB color) {
    if (_scale == DEFCOLOROLEDSCALE) {
        _display->writeFillRect(left, top, right - left + 1, bottom - top + 1, _getColor(color));
    } else {
        for (int y = top; y <= bottom; y++) {
            drawLine(left, y, right, y, color);
        }
    }
    return true;
}

void NGColorOLED::clearCircle(int x0, int y0, int radius) {
    drawCircle(x0, y0, radius, _background);
}

void NGColorOLED::drawCircle(int x0, int y0, int radius, colorRGB color) {
    if (_scale == DEFCOLOROLEDSCALE) {
        _display->drawCircle(x0 * _scale, y0 * _scale, radius * _scale, _getColor(color));
    } else {
        for (int i = 0; i < _scale; i++) {
            _display->drawCircle(x0 * _scale, y0 * _scale, radius * _scale + i, _getColor(color));
        }
    }
}

void NGColorOLED::drawImage(coord2D coord[], colorRGB color, int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(_offsetX + coord[i].x, _offsetY + coord[i].y, color);
    }
    endUpdate();
}

void NGColorOLED::drawImage(coord2D coord[], colorRGB color[], int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(_offsetX + coord[i].x, _offsetY + coord[i].y, color[i]);
    }
    endUpdate();
}

void NGColorOLED::setOffset(int offsetX, int offsetY) {
    _offsetX = offsetX;
    _offsetY = offsetY;
}
