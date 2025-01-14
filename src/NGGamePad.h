//
//  NGGamePad.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 22.01.23.
//

#ifndef NGGamePad_h
#define NGGamePad_h

#include <Arduino.h>
#include <NGINotification.h>
#include <NGCustomGame.h>

#define GAMEPADNOTIFICATIONCOUNT 3
#define GAMEPADMAXGAMECOUNT      5

#define GAMEPADNOGAME -1

struct gamePadStruct
{
    NGCustomGame *game;
};
typedef struct gamePadStruct gamePad;

class NGGamePad {
    
private:
    NGINotification *_notification[GAMENOTIFICATIONCOUNT];
    int _notificationCount = 0;
    int _exceptionCount = 0;
    gamePad _games[GAMEPADMAXGAMECOUNT];
    byte _gamesCount = 0;
    bool _logging = false;
    int _currentGame = GAMEPADNOGAME;
    
protected:
    void _create();
    
    void _raiseException(int id);
        
public:
    NGGamePad();
    
    void initialize();

    void setLogging(bool logging);
    
    bool getLogging();
    
    void registerNotification(NGINotification *notification);
    
    void registerGame(NGCustomGame *game);

    void clearInfo();
    
    void writeInfo(char* info);
    
    void setCurrentGame(int current);
    
    void setNoCurrentGame();
    
    bool hasCurrentGame();
    
    void setTestMode(bool testmode);
    
    void toggleDoPlaySound();

    void processingLoop();    
    
    void handleGameKeyEvent(byte id);
};

#endif /* NGGamePad_h */
