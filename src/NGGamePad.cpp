//
//  NGGamePad.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 22.01.23.
//

#include "NGGamePad.h"
#include "NGGameExceptions.h"

NGGamePad::NGGamePad() {
    _create();
}

void NGGamePad::_create() {
    
}

void NGGamePad::_raiseException(int id) {
    char info[100];
    clearInfo();
    _exceptionCount++;
    sprintf(info, "Ex %d(%d)", id, _exceptionCount);
    writeInfo(info);
}

void NGGamePad::setLogging(bool logging) {
    _logging = logging;
    for (int i = 0; i < _gamesCount; i++) {
        _games[i].game->setLogging(_logging);
    }
}

bool NGGamePad::getLogging() {
    return _logging;
}

void NGGamePad::registerNotification(NGCustomNotification *notification) {
    if (_notificationCount < GAMEPADNOTIFICATIONCOUNT) {
        char log[100];
        _notification[_notificationCount] = notification;
        _notification[_notificationCount]->initialize();
        _notificationCount++;
        sprintf(log, "%s registered", _notification[_notificationCount - 1]->getName());
        writeInfo(log);
    } else {
        _raiseException(ExceptionGamePadTooMuchGameCount);
    }
}

void NGGamePad::registerGame(NGCustomGame *game) {
    if (_gamesCount < GAMEPADMAXGAMECOUNT) {
        char log[100];
        _games[_gamesCount].game = game;
        _games[_gamesCount].game->setLogging(_logging);
        for (int i = 0; i < _notificationCount; i++) {
            _games[_gamesCount].game->registerNotification(_notification[i]);
        }
        _gamesCount++;
        sprintf(log, "Game \"%s\" registered", _games[_gamesCount - 1].game->getName());
        writeInfo(log);
    } else {
        _raiseException(ExceptionGamePadTooMuchGameCount);
    }
}

void NGGamePad::initialize() {
    for (int i = 0; i < _gamesCount; i++) {
        _games[i].game->initialize();
    }
    if (_logging) {
        writeInfo("...GamePad initialized");
    }
}

void NGGamePad::clearInfo() {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->clear(0);
    }
}

void NGGamePad::writeInfo(char* info) {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->writeInfo(info, 0, 0);
    }
}

void NGGamePad::setCurrentGame(int current) {
    if (current == GAMEPADNOGAME || (current >= 0 && current < _gamesCount)) {
        if (_currentGame != GAMEPADNOGAME) {
            _games[_currentGame].game->finishGame();
        }
        _currentGame = current;
        if (hasCurrentGame()) {
            _games[_currentGame].game->startUp();
        }
    }
}

bool NGGamePad::hasCurrentGame() {
    return _currentGame != GAMEPADNOGAME;
}

void NGGamePad::processingLoop() {
    if (hasCurrentGame()) {
        _games[_currentGame].game->processingLoop();
    }
}

void NGGamePad::handleGameKeyEvent(byte id) {
    if (hasCurrentGame()) {
        _games[_currentGame].game->handleKeyEvent(id);
    }
}
