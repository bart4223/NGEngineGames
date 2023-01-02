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
#include <NGSoundMachine.h>
#include <NGJoystickControl.h>

#define GAMENOTIFICATIONCOUNT   3
#define MAXGAMEKEYCOUNT         5
#define MAXGAMEJOYSTICKCOUNT    3

#define GAMENOSOUND -1

#define DEFGAMENEXTSTEPDELAYSTEPSIZE 50

enum gameFunction { gfStartGame, gfFinishGame, gfBreakGame, gfFasterGame, gfSlowerGame };
enum gameToggleMode { gtmStartFinish, gtmBreakContinue };

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
    NGSoundMachine *_soundMachine = nullptr;
    NGCustomNotification *_notification[GAMENOTIFICATIONCOUNT];
    int _notificationCount = 0;
    char* _name;
    bool _logging = false;
    bool _initialized = false;
    int _exceptionCount = 0;
    bool _gameStarted = false;
    bool _gameBreaked = false;
    bool _gameFinished = false;
    int _gameFinishedDelay = 0;
    int _gameNextStepDelay = 0;
    int _gameNextStepDelayStepSize = DEFGAMENEXTSTEPDELAYSTEPSIZE;
    gameToggleMode _gameToggleMode = gtmStartFinish;
    gameKey _keys[MAXGAMEKEYCOUNT];
    int _keyCount = 0;
    gameJoystick _joysticks[MAXGAMEJOYSTICKCOUNT];
    int _joystickCount = 0;
    int _scoreCounter = 0;
    bool _doRender = false;
    bool _autoRestartGame = false;
    int _soundStart = GAMENOSOUND;
    int _soundFinish = GAMENOSOUND;

    void _create(char* name);
    
    void _raiseException(int id);
    
    bool _getYesOrNo();
    
    void _initializeJoysticks();
    
    virtual void _doInitialize();
    
    void _doInitialized();
    
    void _playSound(int index);
    
    virtual void _doStartGame();
    
    virtual void _doBreakGame();
    
    virtual void _doContinueGame();
    
    virtual void _doFinishGame();
    
    virtual void _doProcessingLoop();
    
public:
    void registerSoundMachine(NGSoundMachine *soundmachine);
    
    void registerSoundStart(int sound);
    
    void registerSoundFinish(int sound);
    
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
    
    void breakGame();
    
    void continueGame();
    
    void finishGame();
    
    void handleKeyEvent(byte id);
};

#endif /* NGCustomGame_h */
