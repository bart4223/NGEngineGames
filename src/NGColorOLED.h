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

#define SPI_SC   10
#define SPI_RST   9
#define SPI_DC    8

class NGColorOLED : public NGIPaintableComponent {

private:
    Adafruit_SSD1331 *_display;
    int _scale = DEFCOLOROLEDSCALE;
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
    
    void clear();
    
    bool clearPoint(int x, int y);
    
    bool drawPoint(int x, int y, colorRGB color);
    
    bool fillRect(int top, int left, int bottom, int right, colorRGB color);
    
    void clearCircle(int x0, int y0, int radius);
    
    void drawCircle(int x0, int y0, int radius, colorRGB color);
};

#endif /* NGColorOLED_hpp */
