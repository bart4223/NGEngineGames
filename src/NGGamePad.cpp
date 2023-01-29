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

void NGGamePad::_raiseException(int id) {
    char info[100];
    clearInfo();
    _exceptionCount++;
    sprintf(info, "Ex %d(%d)", id, _exceptionCount);
    writeInfo(info);
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
        _gamesCount++;
        sprintf(log, "Game %d registered", _games[_gamesCount - 1].game->getName());
        writeInfo(log);
    } else {
        _raiseException(ExceptionGamePadTooMuchGameCount);
    }
}

void NGGamePad::initialize() {
    for (int i = 0; i < _gamesCount; i++) {
        _games[i].game->initialize();
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

void NGGamePad::processingLoop() {

}

