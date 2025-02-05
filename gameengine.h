#ifndef __GAMEENGINE_H_INCLUDED
#define __GAMEENGINE_H_INCLUDED

typedef enum{
	GAME_SUCCESS = 0,
	ROUND_WIN,
	GAME_INIT_FAIL = -10,
	TABLE_FAIL,
	ROUND_LOSS,
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
	int (*getinput) (unsigned char *);
	int (*display) (char *, unsigned int);
	int (*display_bin) (unsigned char *, unsigned int);
	int (*clear_dispbuffer) (void);
	int (*delayms_fn) (unsigned int);
	struct random_ops *rand_ops;
};

struct gameconfig {
	Difficulty level;
	unsigned int number_of_inputs;
	struct gameops *ops;
};

int generate_table(void);
int init_game(struct gameconfig *gconfig);
int start_game_round(void);

#endif
