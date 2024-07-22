//
//  NGCustomGame.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.12.22.
//

#include "NGCommon.h"
#include <NGExceptionDefinitions.h>
#include <NGGameExceptions.h>
#include "NGCustomGame.h"

void NGCustomGame::_create(char* name) {
    _name = name;
    randomSeed(analogRead(0));
}

void NGCustomGame::_raiseException(int id) {
    char info[100];
    clearInfo();
    _exceptionCount++;
    sprintf(info, "Ex %d(%d)", id, _exceptionCount);
    writeInfo(info);
}

bool NGCustomGame::_getYesOrNo() {
    return getYesOrNo();
}

void NGCustomGame::_initializeJoysticks() {
    for (int i = 0; i < _joystickCount; i++) {
        _joysticks[i].joystick->initialize();
        if (_logging) {
            char log[100];
            sprintf(log, "Joystick %d initialized", _joysticks[i].joystick->getID());
            writeInfo(log);
        }
    }
}

void NGCustomGame::_doInitialized() {
    _initialized = true;
    if (_logging) {
        char log[100];
        sprintf(log, "...Game \"%s\" initialized", _name);
        writeInfo(log);
    }
}

void NGCustomGame::_playSound(int index) {
    if (hasSoundMachine() && _doPlaySound) {
        _soundMachine->play(index);
    }
}

void NGCustomGame::registerSoundMachine(NGSoundMachine *soundmachine) {
    _soundMachine = soundmachine;
}

void NGCustomGame::registerSoundStartUp(int sound) {
    _soundStartUp = sound;
}

void NGCustomGame::registerSoundStart(int sound) {
    _soundStart = sound;
}
                            
void NGCustomGame::registerSoundFinish(int sound) {
    _soundFinish = sound;
}

void NGCustomGame::registerNotification(NGCustomNotification *notification) {
    if (_notificationCount < GAMENOTIFICATIONCOUNT) {
        char log[100];
        _notification[_notificationCount] = notification;
        _notification[_notificationCount]->initialize();
        _notificationCount++;
        sprintf(log, "%s registered", _notification[_notificationCount - 1]->getName());
        writeInfo(log);
    } else {
        _raiseException(ExceptionTooMuchNotificationCount);
    }
}

void NGCustomGame::registerGameKey(gameFunction function, byte id) {
    if (_keyCount < MAXGAMEKEYCOUNT) {
        char log[100];
        _keys[_keyCount].id = id;
        _keys[_keyCount].function = function;
        _keyCount++;
        sprintf(log, "Key %d registered", _keys[_keyCount - 1].id);
        writeInfo(log);
    } else {
        _raiseException(ExceptionGameTooMuchKeyCount);
    }
}

void NGCustomGame::registerGameJoystick(NGJoystickControl *joystick) {
    if (_joystickCount < MAXGAMEJOYSTICKCOUNT) {
        char log[100];
        _joysticks[_joystickCount].joystick = joystick;
        _joysticks[_joystickCount].joystick->setLogging(_logging);
        _joystickCount++;
        sprintf(log, "Joystick %d registered", _joysticks[_joystickCount - 1].joystick->getID());
        writeInfo(log);
    } else {
        _raiseException(ExceptionGameTooMuchJoystickCount);
    }
}

void NGCustomGame::setLogging(bool logging) {
    _logging = logging;
    for (int i = 0; i < _joystickCount; i++) {
        _joysticks[i].joystick->setLogging(_logging);
    }
}

bool NGCustomGame::getLogging() {
    return _logging;
}

char* NGCustomGame::getName() {
    return _name;
}

void NGCustomGame::setTestMode(bool testmode) {
    _testMode = testmode;
}

bool NGCustomGame::getTestMode() {
    return _testMode;
}

void NGCustomGame::setPlayStartUpSoundConcurrently(bool concurrently) {
    _playStartUpSoundConcurrently = concurrently;
}

bool NGCustomGame::hasSoundMachine() {
    return _soundMachine != nullptr;
}

bool NGCustomGame::hasSoundStartUp() {
    return _soundStartUp != GAMENOSOUND;
}

bool NGCustomGame::hasSoundStart() {
    return _soundStart != GAMENOSOUND;
}

bool NGCustomGame::hasSoundFinish() {
    return _soundFinish != GAMENOSOUND;
}

void NGCustomGame::setDoPlaySound(bool doplaysound) {
    _doPlaySound = doplaysound;
}

bool NGCustomGame::getDoPlaySound() {
    return _doPlaySound;
}

void NGCustomGame::toggleDoPlaySound() {
    setDoPlaySound(!getDoPlaySound());
}

void NGCustomGame::initialize() {
    _initializeJoysticks();
    _doInitialize();
    _doInitialized();
}

void NGCustomGame::startUp() {
    _startUpDone = false;
    if (_playStartUpSoundConcurrently) {
        if (hasSoundMachine()) {
            _soundMachine->setConcurrently(true);
        }
        if (hasSoundStartUp()) {
            _playSound(_soundStartUp);
        }
        while (!_startUpDone) {
            if (hasSoundMachine()) {
                _soundMachine->processingLoop();
            }
            _doStartUp();
        }
    } else {
        _doStartUp();
    }
    if (!_playStartUpSoundConcurrently && hasSoundStartUp()) {
        _playSound(_soundStartUp);
    }
    if (_startUpDoneDelay > 0) {
        delay(_startUpDoneDelay);
    }
    _doStartUpDone();
}

void NGCustomGame::processingLoop() {
    if (!_gameBreaked) {
        for (int i = 0; i < _joystickCount; i++) {
            _joysticks[i].joystick->processingLoop();
        }
        _doProcessingLoop();
        if (_gameFinished) {
            if (_gameFinishedDelay > 0) {
                delay(_gameFinishedDelay);
            }
            finishGame();
            if (_autoRestartGame) {
                startGame();
            }
        }
    }
}

void NGCustomGame::handleKeyEvent(byte id) {
    for (int i = 0; i < _keyCount; i++) {
        if (_keys[i].id == id) {
            switch (_keys[i].function) {
                case gfStartGame:
                    if (!_gameStarted) {
                        startGame();
                    } else {
                        switch (_gameToggleMode) {
                            case gtmStartFinish:
                                finishGame();
                                break;
                            case gtmBreakContinue:
                                if (!_gameBreaked) {
                                    breakGame();
                                } else {
                                    continueGame();
                                }
                                break;
                        }
                    }
                    break;
                case gfFinishGame:
                    finishGame();
                    break;
                case gfBreakGame:
                    if (!_gameBreaked) {
                        breakGame();
                    } else {
                        continueGame();
                    }
                    break;
                case gfFasterGame:
                    if ((_gameNextStepDelay - _gameNextStepDelayStepSize) > 0) {
                        _gameNextStepDelay = _gameNextStepDelay - _gameNextStepDelayStepSize;
                    }
                    break;
                case gfSlowerGame:
                    _gameNextStepDelay = _gameNextStepDelay + _gameNextStepDelayStepSize;
                    break;
            }
        }
    }
}

void NGCustomGame::clearInfo() {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->clear(0);
    }
}

void NGCustomGame::writeInfo(char* info) {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->writeInfo(info, 0, 0);
    }
}

void NGCustomGame::startGame() {
    if (!_gameStarted) {
        _scoreCounter = 0;
        _doStartGame();
        _gameFinished = false;
        _gameBreaked = false;
        _gameStarted = true;
        if (_logging) {
            char log[100];
            sprintf(log, "...Game \"%s\" started", _name);
            writeInfo(log);
        }
        if (hasSoundStart()) {
            if (hasSoundMachine()) {
                _soundMachine->setConcurrently(false);
            }
            _playSound(_soundStart);
        }
    }
}

void NGCustomGame::breakGame() {
    if (_gameStarted) {
        _gameBreaked = true;
        _doBreakGame();
        if (_logging) {
            char log[100];
            sprintf(log, "...Game \"%s\" breaked", _name);
            writeInfo(log);
        }
    }
}

void NGCustomGame::continueGame() {
    if (_gameStarted && _gameBreaked) {
        _gameBreaked = false;
        _doContinueGame();
        if (_logging) {
            char log[100];
            sprintf(log, "...Game \"%s\" continued", _name);
            writeInfo(log);
        }
    }
}

void NGCustomGame::finishGame() {
    if (_gameStarted) {
        _doFinishGame();
        _gameStarted = false;
        if (hasSoundFinish()) {
            if (hasSoundMachine()) {
                _soundMachine->setConcurrently(false);
            }
            _playSound(_soundFinish);
        }
        if (_logging) {
            char log[100];
            sprintf(log, "...Game \"%s\" finished", _name);
            writeInfo(log);
        }
    }
}

bool NGCustomGame::isGameStarted() {
    return _gameStarted;
}

gameMode NGCustomGame::getGameMode() {
    return _gameMode;
}
