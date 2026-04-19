//
//  NGColorOLED.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 05.03.23.
//

#ifndef NGColorOLED_h
#define NGColorOLED_h

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <NGIPaintableComponent.h>

#define DEFCOLOROLEDSCALE 1
#define DEFCOLOROLEDBACKGROUNDCOLOR COLOR_BLACK

#define SPI_SC   10
#define SPI_RST   9
#define SPI_DC    8

class NGColorOLED : public NGIPaintableComponent {
    
private:
    Adafruit_SSD1331 *_display;
    int _scale = DEFCOLOROLEDSCALE;
    colorRGB _background = DEFCOLOROLEDBACKGROUNDCOLOR;
    int _updateCount = 0;
    int _offsetX = 0;
    int _offsetY = 0;
    
protected:
    void _create();
    
    int _getColor(colorRGB c);
    
public:
    NGColorOLED();
    
    void initialize();
    
    int getWidth();
    
    int getHeight();
    
    void beginUpdate();
    
    void endUpdate();
    
    void setScale(int scale);
    
    int getScale();
    
    void setBackground(colorRGB color);
    
    colorRGB getBackground();
    
    void clear();
    
    bool clearPoint(int x, int y);
    
    bool drawPoint(int x, int y, colorRGB color);
    
    bool drawPoint(int x, int y, int color);
    
    void clearLine(int x1, int y1, int x2, int y2);
    
    void drawLine(int x1, int y1, int x2, int y2, colorRGB color);
    
    void clearRect(int top, int left, int bottom, int right);
    
    void drawRect(int top, int left, int bottom, int right, colorRGB color);
    
    void fillRect(int top, int left, int bottom, int right, colorRGB color);
    
    void clearCircle(int x0, int y0, int radius);
    
    void drawCircle(int x0, int y0, int radius, colorRGB color);
    
    void drawImage(coord2D coord[], colorRGB color, int size);

    void drawImage(coord2D coord[], colorRGB color[], int size);

    void setOffset(int offsetX, int offsetY);
};

#endif /* NGColorOLED_hpp */
