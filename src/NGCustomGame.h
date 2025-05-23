//
//  NGCustomGame.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.12.22.
//

#ifndef NGCustomGame_h
#define NGCustomGame_h

#include <Arduino.h>
#include <NGINotification.h>
#include <NGSoundMachine.h>
#include <NGJoystickControl.h>

#define GAMENOTIFICATIONCOUNT   3
#define MAXGAMEKEYCOUNT         5
#define MAXGAMEJOYSTICKCOUNT    3

#define GAMENOSOUND -1

#define DEFGAMENEXTSTEPDELAYSTEPSIZE 50

enum gameFunction { gfStartGame, gfFinishGame, gfBreakGame, gfFasterGame, gfSlowerGame };
enum gameToggleMode { gtmStartFinish, gtmBreakContinue };
enum gameMode { gmMinimal, gmNormal, gmBig };

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
    NGINotification *_notification[GAMENOTIFICATIONCOUNT];
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
    int _soundStartUp = GAMENOSOUND;
    bool _playStartUpSoundConcurrently = false;
    int _soundStart = GAMENOSOUND;
    int _soundFinish = GAMENOSOUND;
    int _startUpDoneDelay = 0;
    bool _startUpDone = false;
    bool _doPlaySound = true;
    bool _testMode = false;
    gameMode _gameMode = gmNormal;
    bool _inStartUpAnimation = false;
    int _startUpAnimationStep = -1;
    long _lastStartUpAnimationStep = 0;
    
    void _create(char* name);
    
    void _raiseException(int id);
    
    bool _getYesOrNo();
    
    void _initializeJoysticks();
    
    virtual void _doInitialize();
    
    virtual void _doStartUp();
    
    virtual void _doStartUpDone();
    
    void _doInitialized();
    
    void _playSound(int index);
    
    virtual void _doStartGame();
    
    virtual void _doBreakGame();
    
    virtual void _doContinueGame();
    
    virtual void _doFinishGame();
    
    virtual void _doProcessingLoop();
    
public:
    void registerSoundMachine(NGSoundMachine *soundmachine);
    
    void registerSoundStartUp(int sound);
    
    void registerSoundStart(int sound);
    
    void registerSoundFinish(int sound);
    
    void registerNotification(NGINotification *notification);
    
    void registerGameKey(gameFunction function, byte id);
    
    void registerGameJoystick(NGJoystickControl *joystick);
    
    void setLogging(bool logging);
    
    bool getLogging();
    
    char* getName();
    
    void setTestMode(bool testmode);
    
    bool getTestMode();
    
    void setPlayStartUpSoundConcurrently(bool concurrently);
    
    bool hasSoundMachine();
    
    bool hasSoundStartUp();
    
    bool hasSoundStart();
    
    bool hasSoundFinish();
    
    void setDoPlaySound(bool doplaysound);
    
    bool getDoPlaySound();
    
    void toggleDoPlaySound();
    
    void initialize();
    
    void startUp();
        
    void processingLoop();
    
    void clearInfo();

    void writeInfo(char* info);
    
    void startGame();
    
    void breakGame();
    
    void continueGame();
    
    void finishGame();
    
    void handleKeyEvent(byte id);
    
    bool isGameStarted();
    
    gameMode getGameMode();
};

#endif /* NGCustomGame_h */
