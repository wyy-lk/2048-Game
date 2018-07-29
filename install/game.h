#ifndef GAME_H
#define GAME_H

extern int merge(int box[][4], int dir);
extern int check(int box[][4]);
extern int randnumber(int box[][4]);

enum STATUS {GAMING, WIN, LOSE = -1};
enum SCORE {NOSCORE = -1};

#endif
