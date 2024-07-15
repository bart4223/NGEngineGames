//
//  NGGameConsoleUnitControl.cpp
//  NGEngineGames
//
//  Created by Nils Grimmer on 12.07.24.
//

#include "NGGameConsoleUnitControl.h"

NGGameConsoleUnitControl::NGGameConsoleUnitControl(char* name, NGCustomGame *game) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, game);
}

NGGameConsoleUnitControl::NGGameConsoleUnitControl(char* name, byte address, int serialRate, NGCustomGame *game) {
    _create(name, address, serialRate, game);
}

void NGGameConsoleUnitControl::_create(char* name, byte address, int serialRate, NGCustomGame *game) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
    _game = game;
}

void NGGameConsoleUnitControl::_processingReceivedData() {
    
}

void NGGameConsoleUnitControl::_processingStartupLoop() {
    
}

void NGGameConsoleUnitControl::_processingIRRemoteData() {
    
}

void NGGameConsoleUnitControl::initialize() {
    _game->initialize();
    if (_logging) {
        char log[100];
        sprintf(log, "...Game \"%s\" initialized", _game->getName());
        writeInfo(log);
    }
}

void NGGameConsoleUnitControl::processingLoop() {
    _game->processingLoop();
}
    
void NGGameConsoleUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}

void NGGameConsoleUnitControl::startGame() {
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

void NGGameConsoleUnitControl::toggleDoPlaySound() {
    _game->toggleDoPlaySound();
}
