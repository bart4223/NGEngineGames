//
//  NGColorDotMatrixGameAsteroids.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 07.01.23.
//

#ifndef NGColorDotMatrixGameAsteroids_h
#define NGColorDotMatrixGameAsteroids_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomColorDotMatrixGame.h>

#define GAMEASTEROIDSCOLORSCOREOFF  { .red = 5, .green = 5, .blue = 5 }
#define GAMEASTEROIDSCOLORSCOREON   COLOR_GREEN

#define GAMEASTEROIDSCOLOROUTRO   COLOR_RED

//#define GAMEASTEROIDSMAZESIZEX           12
#define GAMEASTEROIDSMAZESIZEX            8
#define GAMEASTEROIDSMAZESIZEY            7
#define GAMEASTEROIDSSCOREDIGITS          8
#define GAMEASTEROIDSSCOREDIGITXPOS       0
#define GAMEASTEROIDSSCOREDIRECTION bddLeft

#define GAMEASTEROIDSMOVEDELAY             500
#define GAMEASTEROIDSFINISHDELAY          1000
#define GAMEASTEROIDSLASERBEAMSPAWNDELAY   200

#define GAMEASTEROIDSSTARTPOSX 0
#define GAMEASTEROIDSSTARTPOSY 3

#define GAMEASTEROIDSCOLORINDEXSPACECRAFT01 1
#define GAMEASTEROIDSCOLORINDEXSPACECRAFT02 2
#define GAMEASTEROIDSCOLORINDEXLASERBEAM    3
#define GAMEASTEROIDSCOLORINDEXASTEROID     4

#define GAMEASTEROIDSINTROLASERBEAMTIMES           5
#define GAMEASTEROIDSINTRODELAY                  100
#define GAMEASTEROIDSINTROSHOTDELAY                0
#define GAMEASTEROIDSOUTRODELAY                  100
#define GAMEASTEROIDSOUTRODPOINTCOUNTERDELAY    3000

#define GAMEASTEROIDSMAXLOST 3

static byte globalAsteroidsColors[4][3] = {
  {0, 0, 255},  // Spacecraft 01
  {0, 0, 255},  // Spacecraft 02
  {255, 0, 0},  // Laser
  {255, 255, 0} // Asteroid
};

class NGColorDotMatrixGameAsteroids : public NGCustomColorDotMatrixGame {
 
private:
    byte _posXSpacecraft = GAMEASTEROIDSSTARTPOSX;
    byte _posYSpacecraft = GAMEASTEROIDSSTARTPOSY;
    int _maze[GAMEASTEROIDSMAZESIZEY][GAMEASTEROIDSMAZESIZEX];
    long _lastAsteroidsMove = 0;
    long _lastSpawnLaserbeam = 0;
    byte _asteroidsLost = 0;
    int _introShotDelay = GAMEASTEROIDSINTROSHOTDELAY;
    
    void _resetMaze();
    
    bool _isColorIndexSpacecraft(int index);
    
    void _computeAsteroids();
    
    bool _computeLaserbeam();
    
    void _spawnAsteroid();
    
    void _spawnLaserbeam();
    
    void _clearSpacecraft();
    
    void _computeSpacecraft();
    
    bool _checkSpacecraft(byte posX, byte posY);
    
    void _ownJoystickLoop();
    
    void _ownRender();
    
    void _ownIntro();
    
    void _ownOutro();
    
protected:
    void _doInitialize();
    
    void _doStartUp();
    
    void _doStartUpDone();
    
    void _doStartGame();
    
    void _doBreakGame();
    
    void _doContinueGame();
    
    void _doFinishGame();
    
    void _doProcessingLoop();
       
public:
    NGColorDotMatrixGameAsteroids();
    
    void setIntroShotDelay(int shotdelay);
};


#endif /* NGColorDotMatrixGameAsteroids_h */
