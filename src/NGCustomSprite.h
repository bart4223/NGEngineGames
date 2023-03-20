//
//  NGCustomSprite.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 14.03.23.
//

#ifndef NGCustomSprite_h
#define NGCustomSprite_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGIPaintableObject.h>
#include <NGIPaintableComponent.h>

class NGCustomSprite : public NGIPaintableObject {
    
protected:
    NGIPaintableComponent *_ipc;
    int _width;
    int _height;
    int _posX = 0;
    int _posY = 0;
    int _imageSize = 0;
    int _scale = 1;
    colorRGB _background = COLOR_BLACK;
    colorRGB _color = COLOR_BLACK;
    bool _transparent = false;
    char* _name;

    void _create(NGIPaintableComponent *ipc);

    virtual void _doRender(int x, int y);
    
public:
    void render();
    
    void render(int x, int y);
    
    void setPosition(int x, int y);
    
    void setTransparent(bool transparent);
    
    bool getTransparent();
    
    void setBackground(colorRGB background);
    
    void setColor(colorRGB color);
    
    char* getName();
    
    void setScale(int scale);
    
    int getScale();
    
    int getWidth();
    
    int getHeight();
};

#endif /* NGCustomSprite_h */
