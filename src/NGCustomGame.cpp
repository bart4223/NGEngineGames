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

void NGCustomGame::initialize() {
    _initializeJoysticks();
    _doInitialize();
    _doInitialized();
}

void NGCustomGame::processingLoop() {
    for (int i = 0; i < _joystickCount; i++) {
        _joysticks[i].joystick->processingLoop();
    }
    _doProcessingLoop();
}

void NGCustomGame::handleKeyEvent(byte id) {
    for (int i = 0; i < _keyCount; i++) {
        if (_keys[i].id == id) {
            switch (_keys[i].function) {
                case gfStartGame:
                    if (!_gameStarted) {
                        startGame();
                    } else {
                        finishGame();
                    }
                    break;
            }
            switch (_keys[i].function) {
                case gfFinishGame:
                    finishGame();
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
        _gameStarted = true;
        if (_logging) {
            char log[100];
            sprintf(log, "...Game \"%s\" started", _name);
            writeInfo(log);
        }
    }
}

void NGCustomGame::finishGame() {
    if (_gameStarted) {
        _doFinishGame();
        _gameStarted = false;
        if (_logging) {
            char log[100];
            sprintf(log, "...Game \"%s\" finished", _name);
            writeInfo(log);
        }
    }
}
