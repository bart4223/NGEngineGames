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
    if (_logging) {
        char log[100];
        sprintf(log, "...Game \"%s\" initialized", _game->getName());
        writeInfo(log);
    }
}

void NGGameMachineUnitControl::processingLoop() {
    _game->processingLoop();
}
    
void NGGameMachineUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}

void NGGameMachineUnitControl::startGame() {
    char log[100];
    if (_logging) {
        sprintf(log, "Game \"%s\" startup...", _game->getName());
        writeInfo(log);
    }
    _game->startUp();
    _game->startGame();
    if (_logging) {
        sprintf(log, "...Game \"%s\" started", _game->getName());
        writeInfo(log);
    }
}

void NGGameMachineUnitControl::toggleDoPlaySound() {
    _game->toggleDoPlaySound();
}
