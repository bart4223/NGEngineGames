//
//  NGColorOLED.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 05.03.23.
//

#ifndef NGColorOLED_h
#define NGColorOLED_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

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
    
    void clear();
    
    bool clearPoint(int x, int y);
    
    bool drawPoint(int x, int y, colorRGB color);
    
    void clearLine(int x1, int y1, int x2, int y2);
    
    void drawLine(int x1, int y1, int x2, int y2, colorRGB color);
    
    void clearRect(int top, int left, int bottom, int right);
    
    void drawRect(int top, int left, int bottom, int right, colorRGB color);
    
    void fillRect(int top, int left, int bottom, int right, colorRGB color);
    
    void clearCircle(int x0, int y0, int radius);
    
    void drawCircle(int x0, int y0, int radius, colorRGB color);
    
    void drawImage(int coord[][2], colorRGB color, int size);

    void drawImage(int offsetX, int offsetY, int coord[][2], colorRGB color, int size);

    void drawImage(int coord[][2], byte color[][3], int size);

    void drawImage(int offsetX, int offsetY, int coord[][2], byte color[][3], int size);
};

#endif /* NGColorOLED_hpp */
