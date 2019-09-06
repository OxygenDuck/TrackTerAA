#define RAILVAR 1

//io
int aoSpeedOnTrackPjan = 2;

int doActivateBlockAdee[9] = {0, 1, 2, 3, 4, 6, 7, 8, 9}; //sb0x on ; sb0o off

int diTrainDetectedBlockAdee[9] = {22, 23, 24, 25, 26, 27, 28, 29, 30}; //db0 returns true or false

int doTakeTurnTurnoutAdee[8] = {31, 33, 35, 37, 39, 41, 43, 45}; //sw0x straight sw0o turn

//int doStraightAheadTurnoutAdee[8] = {32, 34, 36, 38, 40, 42, 44, 46}; //useless af

int doTurnOutEnableAdee = 47;

//globals
bool trainDetectedBlock0 = false;
bool trainDetectedBlock1 = false;

bool switchTrainBlock0Adee = false;
bool switchTrainBlock1Adee = false;
bool trainDetected = false;

