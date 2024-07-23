//
//  NGGameMachineUnitControl.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 12.07.24.
//

#include "NGGameMachineUnitControl.h"

NGGameMachineUnitControl::NGGameMachineUnitControl(char* name, NGCustomGame *game) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, game);
}

NGGameMachineUnitControl::NGGameMachineUnitControl(char* name, byte address, int serialRate, NGCustomGame *game) {
    _create(name, address, serialRate, game);
}

void NGGameMachineUnitControl::_create(char* name, byte address, int serialRate, NGCustomGame *game) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
    _game = game;
}

void NGGameMachineUnitControl::_processingReceivedData() {
    
}

void NGGameMachineUnitControl::_processingStartupLoop() {
    
}

void NGGameMachineUnitControl::_processingIRRemoteData() {
    
}

void NGGameMachineUnitControl::initialize() {
    _game->initialize();
}

void NGGameMachineUnitControl::processingLoop() {
    _game->processingLoop();
}
    
void NGGameMachineUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}

long int NGGameMachineUnitControl::startUp() {
    long int res = NGCustomUnitControl::startUp();
    if (_logging) {
        char log[100];
        sprintf(log, "%s started in game mode %d", _name, _game->getGameMode());
        writeInfo(log);
    }
    return res;
}

void NGGameMachineUnitControl::startGame() {
    if (_game->isGameStarted()) {
        _game->finishGame();
    }
    _game->startUp();
    _game->startGame();
}

void NGGameMachineUnitControl::toggleDoPlaySound() {
    _game->toggleDoPlaySound();
}

void NGGameMachineUnitControl::registerNotification(NGCustomNotification *notification) {
    NGCustomUnitControl::registerNotification(notification);
    _game->registerNotification(notification);
}

void NGGameMachineUnitControl::setLogging(bool logging) {
    NGCustomUnitControl::setLogging(logging);
    _game->setLogging(logging);
}
