#define RAILVAR 1

//io
int aoSpeedOnTrackPjan = 2;
int baseTrackValue = 3;

int doActivateBlockAdee[9] = {5, 6, 7, 11, 10, 8, 12, 14, 15}; //sb0x on ; sb0o off

int diTrainDetectedBlockAdee[9] = {26,27,28, 29, 30, 31, 32, 33, 34}; //db0 returns true or false

int doTakeTurnTurnoutAdee[8] = {37, 38, 39, 40, 41, 42, 43}; //sw0x straight sw0o turn

//int doStraightAheadTurnoutAdee[8] = {32, 34, 36, 38, 40, 42, 44, 46}; //useless af

int doTurnOutEnableAdee = 47;

int trigPin[3] = {46,45,44};
int echoPin[3] = {50,49,48};
