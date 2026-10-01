//
//  NGColorDotMatrixEffectGameIdle.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 01.10.26.
//

#ifndef NGColorDotMatrixEffectGameIdle_h
#define NGColorDotMatrixEffectGameIdle_h

#include <Arduino.h>
#include <NGIEffect.h>
#include <NGIPaintableComponent.h>
#include <Games/NGCustomGame.h>
#include <NGColorDotMatrixText.h>

#define DEFTEXTCOLOR COLOR_BLACK
#define DEFIDLEEFFECTMODE giemSimple

enum gameIdleEffectMode { giemSimple };


class NGColorDotMatrixEffectGameIdle: public NGIEffect {
    
private:
    NGIPaintableComponent *_ipc;
    NGCustomGame *_game;
    NGColorDotMatrixText *_text;
    char *_textSecondary;
    colorRGB _textColor = DEFTEXTCOLOR;
    gameIdleEffectMode _mode = DEFIDLEEFFECTMODE;

protected:
    void _create(NGIPaintableComponent *ipc, NGCustomGame *game, gameIdleEffectMode mode);
    
public:
    NGColorDotMatrixEffectGameIdle(NGIPaintableComponent *ipc, NGCustomGame *game);
    
    void initialize();
    
    void processingLoop();

    void setFont(NGCustomFont *font);

    void setTextSecondary(char* textsecondary);

    void setTextColor(colorRGB colortext);
};

#endif /* NGColorDotMatrixEffectGameIdle_h */
