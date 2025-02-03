#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gameengine.h"

struct gamecomplexity {
	unsigned int max_table_offset;
	unsigned int max_seq_length;
	unsigned int max_bit_size;
} gcomplex ;


struct gameconfig *config = NULL;


static void print(char *str, unsigned int size){
	config->ops->display(str, size);
}


static int seed_gen(){
	time_t rawtime;
	struct tm *timenow;
	char date_str[9];
	unsigned int date_int;

	time (&rawtime);
	timenow = localtime(&rawtime);

	sprintf(date_str, "%u%u%u", timenow->tm_mday, timenow->tm_mon + 1, timenow->tm_year + 1900);
	date_int = atoi(date_str);

	return date_int;
}


static int set_rand_seed(int seed){
	if(config->ops == NULL){
                return GAME_INIT_FAIL;
        }
        return config->ops->rand_ops->randseed(seed);
}


static int get_rand(){
	if(config->ops == NULL){
                return GAME_INIT_FAIL;
        }
	unsigned int rnum = config->ops->rand_ops->randnum() % 10000;
	
	return rnum % gcomplex.max_bit_size;
}



static void init_game_level(Difficulty lvl){
	switch(lvl){
		case EASY:
                        gcomplex.max_table_offset = 15;
                        gcomplex.max_seq_length = 10;
                        gcomplex.max_bit_size = 16;
                        break;
		case MEDIUM:
                        gcomplex.max_table_offset = 20;
                        gcomplex.max_seq_length = 15;
                        gcomplex.max_bit_size = 32;
                        break;
		case HARD:
                        gcomplex.max_table_offset = 20;
                        gcomplex.max_seq_length = 10;
                        gcomplex.max_bit_size = 64;
                        break;
		case SUPER_HARD:
                        gcomplex.max_table_offset = 20;
                        gcomplex.max_seq_length = 10;
                        gcomplex.max_bit_size = 256;
                        break;
		default:
			break;
	}
}

static int generate_table() {
    unsigned int seed = seed_gen();
    printf("Setting seed: %u\n", seed);

    char outbuf[1024];

    for (int i = 0; i < gcomplex.max_table_offset; i++) {
        int offset = snprintf(outbuf, sizeof(outbuf), "Seq:%d [", i);
        set_rand_seed(seed + i);

        for (int j = 0; j < gcomplex.max_seq_length; j++) {
            offset += snprintf(outbuf + offset, sizeof(outbuf) - offset, "%d%s", get_rand(),
                               (j == gcomplex.max_seq_length - 1) ? "" : ", ");
        }

        snprintf(outbuf + offset, sizeof(outbuf) - offset, "]\n");
        print(outbuf, strlen(outbuf));
    }

    return GAME_SUCCESS;
}


int init_game(struct gameconfig *gconfig){
	if(gconfig == NULL){
		return GAME_INIT_FAIL;
	}
	printf("Init Game\n");

	/* Set the game config*/
	config = gconfig;

	init_game_level(gconfig->level);

	generate_table();

	return GAME_SUCCESS;
}


int start_game(void){
	printf("Start Game\n");

	return GAME_SUCCESS;
}
