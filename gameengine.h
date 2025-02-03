#ifndef __GAMEENGINE_H_INCLUDED
#define __GAMEENGINE_H_INCLUDED

typedef enum{
	GAME_SUCCESS = 0,
	GAME_INIT_FAIL = -10,
	TABLE_FAIL,
} Errcode;

typedef enum{
        EASY = 0,
        MEDIUM,
        HARD,
	SUPER_HARD,
	IMPOSSIBLE,
} Difficulty;

struct random_ops {
	int (*randseed) (int);
	int (*randnum) (void);
};


struct gameops {
	int (*getinput) (char *);
	int (*display) (char *, unsigned int);
	struct random_ops *rand_ops;
};

struct gameconfig {
	Difficulty level;
	struct gameops *ops;
};

int init_game(struct gameconfig *gconfig);
int start_game(void);

#endif
