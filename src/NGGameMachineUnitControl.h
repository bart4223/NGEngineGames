//
//  NGGameMachineUnitControl.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 12.07.24.
//

#ifndef NGGameMachineUnitControl_h
#define NGGameMachineUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>
#include <NGCustomGame.h>

#define _VERSION "2.7"
#define VERSION (char*)_VERSION

class NGGameMachineUnitControl : public NGCustomUnitControl {
    
private:
    NGCustomGame *_game;
    NGIEffect *_effectIdle = nullptr;
        
protected:
    void _create(char* name, byte address, int serialRate, NGCustomGame *game);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();

public:
    NGGameMachineUnitControl(char* name, NGCustomGame *game);
    
    NGGameMachineUnitControl(char* name, byte address, int serialRate, NGCustomGame *game);
    
    void initialize();
    
    void processingLoop();
        
    void requestData(byte* data);
    
    long int startUp();
    
    void startGame();
    
    bool isGameStarted();
    
    void toggleDoPlaySound();
    
    void setPlayStartUpSoundConcurrently(bool concurrently);
    
    void registerNotification(NGINotification *notification);
    
    void registerEffectIdle(NGIEffect *effect);
    
    void setLogging(bool logging);
};

#endif /* NGGameMachineUnitControl_h */
