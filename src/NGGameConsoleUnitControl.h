//
//  NGGameConsoleUnitControl.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 12.07.24.
//

#ifndef NGGameConsoleUnitControl_h
#define NGGameConsoleUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>
#include <NGCustomGame.h>

#define _VERSION "0.2"
#define VERSION (char*)_VERSION

class NGGameConsoleUnitControl : public NGCustomUnitControl {
    
private:
    NGCustomGame *_game;
        
protected:
    void _create(char* name, byte address, int serialRate, NGCustomGame *game);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();

public:
    NGGameConsoleUnitControl(char* name, NGCustomGame *game);
    
    NGGameConsoleUnitControl(char* name, byte address, int serialRate, NGCustomGame *game);
    
    void initialize();
    
    void processingLoop();
        
    void requestData(byte* data);
    
    void startGame();
    
    void toggleDoPlaySound();
};

#endif /* NGGameConsoleUnitControl_h */
