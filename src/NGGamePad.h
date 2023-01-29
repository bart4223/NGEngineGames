//
//  NGGamePad.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 22.01.23.
//

#ifndef NGGamePad_h
#define NGGamePad_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomNotification.h>
#include <NGCustomGame.h>

#define GAMEPADNOTIFICATIONCOUNT 3
#define GAMEPADMAXGAMECOUNT      5

struct gamePadStruct
{
    NGCustomGame *game;
};
typedef struct gamePadStruct gamePad;

class NGGamePad {
    
private:
    NGCustomNotification *_notification[GAMENOTIFICATIONCOUNT];
    int _notificationCount = 0;
    int _exceptionCount = 0;
    gamePad _games[GAMEPADMAXGAMECOUNT];
    byte _gamesCount = 0;
    bool _logging = false;
    
protected:
    void _create();
    
    void _raiseException(int id);
        
public:
    NGGamePad();
    
    void initialize();

    void setLogging(bool logging);
    
    bool getLogging();
    
    void registerNotification(NGCustomNotification *notification);
    
    void registerGame(NGCustomGame *game);

    void clearInfo();
    
    void writeInfo(char* info);
    
    void processingLoop();
};

#endif /* NGGamePad_h */
