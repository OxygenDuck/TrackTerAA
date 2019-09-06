#define RAILVAR 1

//io
int aoSpeedOnTrackPjan = 2;
int baseTrackValue = 3;

int doActivateBlockAdee[9] = {5, 6, 7, 8, 10, 11, 12, 14, 15}; //sb0x on ; sb0o off

int diTrainDetectedBlockAdee[9] = {28, 29, 30, 31, 32, 33, 34, 35, 36}; //db0 returns true or false

int doTakeTurnTurnoutAdee[8] = {37, 38, 39, 40, 41, 42, 43}; //sw0x straight sw0o turn

//int doStraightAheadTurnoutAdee[8] = {32, 34, 36, 38, 40, 42, 44, 46}; //useless af

int doTurnOutEnableAdee = 47;

//globals
bool trainDetectedBlock0 = false;
bool trainDetectedBlock1 = false;

bool switchTrainBlock0Adee = false;
bool switchTrainBlock1Adee = false;
bool trainDetected = false;
