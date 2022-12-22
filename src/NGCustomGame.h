//
//  NGCustomGame.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.12.22.
//

#ifndef NGCustomGame_h
#define NGCustomGame_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomNotification.h>
#include <NGJoystickControl.h>

#define GAMENOTIFICATIONCOUNT   3
#define MAXGAMEKEYCOUNT         5
#define MAXGAMEJOYSTICKCOUNT    3

enum gameFunction { gfStartGame, gfFinishGame };

struct gameKeyStruct
{
    byte id;
    gameFunction function;
};
typedef struct gameKeyStruct gameKey;

struct gameJoystickStruct
{
    NGJoystickControl *joystick;
};
typedef struct gameJoystickStruct gameJoystick;

class NGCustomGame {
    
protected:
    NGCustomNotification *_notification[GAMENOTIFICATIONCOUNT];
    int _notificationCount = 0;
    char* _name;
    bool _logging = false;
    bool _initialized = false;
    int _exceptionCount = 0;
    bool _gameStarted = false;
    gameKey _keys[MAXGAMEKEYCOUNT];
    int _keyCount = 0;
    gameJoystick _joysticks[MAXGAMEJOYSTICKCOUNT];
    int _joystickCount = 0;
    int _scoreCounter = 0;
    bool _doRender = false;
    
    void _create(char* name);
    
    void _raiseException(int id);
    
    bool _getYesOrNo();
    
    void _initializeJoysticks();
    
    virtual void _doInitialize();
    
    void _doInitialized();
    
    virtual void _doStartGame();
    
    virtual void _doFinishGame();
    
    virtual void _doProcessingLoop();
    
public:
    void registerNotification(NGCustomNotification *notification);
    
    void registerGameKey(gameFunction function, byte id);
    
    void registerGameJoystick(NGJoystickControl *joystick);
    
    void setLogging(bool logging);
    
    bool getLogging();
    
    void initialize();
        
    void processingLoop();
    
    void clearInfo();

    void writeInfo(char* info);
    
    void startGame();
    
    void finishGame();
    
    void handleKeyEvent(byte id);
};

#endif /* NGCustomGame_h */
