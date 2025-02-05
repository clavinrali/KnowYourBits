#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gameengine.h"

struct gamecomplexity {
	unsigned int max_table_offset;
	unsigned int max_seq_length;
	unsigned int max_bit_size;
	unsigned int disp_delay_ms;
} gcomplex ;


struct gameconfig *config = NULL;

static void readinput(unsigned char *val){
	config->ops->getinput(val);
}

static void print(char *str, unsigned int size){
	config->ops->display(str, size);
}

static void printbin(char *str, unsigned int size){
	config->ops->display_bin(str, size);
}

static int delay_ms(unsigned int value){
	 if(config->ops == NULL){
                return GAME_INIT_FAIL;
        }

	config->ops->delayms_fn(value);
	return GAME_SUCCESS;
}

static int clr_dispbuf(){
         if(config->ops == NULL){
                return GAME_INIT_FAIL;
        }

        config->ops->clear_dispbuffer();
        return GAME_SUCCESS;
}

static int seed_gen(unsigned int flag){
	time_t rawtime;
	struct tm *timenow;
	char date_str[9];
	unsigned int date_int;

	time (&rawtime);
	timenow = localtime(&rawtime);

	if(!flag){
		sprintf(date_str, "%u%u%u", timenow->tm_mday, timenow->tm_mon + 1, timenow->tm_year + 1900);
		date_int = atoi(date_str);
	} else {

		sprintf(date_str, "%u%u%u", timenow->tm_hour, timenow->tm_min, timenow->tm_sec);
		date_int = atoi(date_str);
	}


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
	unsigned int rnum = config->ops->rand_ops->randnum();
        rnum %= 10000;
	rnum %= gcomplex.max_bit_size;

	return rnum;
}

static int get_rand_seqno(){
	if(config->ops == NULL){
                return GAME_INIT_FAIL;
        }
	unsigned int rnum = config->ops->rand_ops->randnum();
	rnum /= 100000;
        rnum %= 100;
	rnum %= gcomplex.max_table_offset;
	
	return rnum;
}



static void init_game_level(Difficulty lvl){
	switch(lvl){
		case EASY:
                        gcomplex.max_table_offset = 35;
                        gcomplex.max_seq_length = 10;
                        gcomplex.max_bit_size = 16;
                        gcomplex.disp_delay_ms = 1000;
                        break;
		case MEDIUM:
                        gcomplex.max_table_offset = 35;
                        gcomplex.max_seq_length = 15;
                        gcomplex.max_bit_size = 32;
                        gcomplex.disp_delay_ms = 1000;
                        break;
		case HARD:
                        gcomplex.max_table_offset = 35;
                        gcomplex.max_seq_length = 10;
                        gcomplex.max_bit_size = 64;
                        gcomplex.disp_delay_ms = 1000;
                        break;
		case SUPER_HARD:
                        gcomplex.max_table_offset = 35;
                        gcomplex.max_seq_length = 10;
                        gcomplex.max_bit_size = 256;
                        gcomplex.disp_delay_ms = 1000;
                        break;
		case IMPOSSIBLE:
                        gcomplex.max_table_offset = 40;
                        gcomplex.max_seq_length = 15;
                        gcomplex.max_bit_size = 65535;
                        gcomplex.disp_delay_ms = 1000;
                        break;
		default:
			gcomplex.max_table_offset = 35;
                        gcomplex.max_seq_length = 10;
                        gcomplex.max_bit_size = 16;
                        gcomplex.disp_delay_ms = 1000;
			break;
	}
}

static int gen_seq_ans(){
	if(config->ops == NULL){
                return GAME_INIT_FAIL;
        }
        unsigned int rnum = config->ops->rand_ops->randnum();
        rnum /= 100000;
        rnum %= 100;
        rnum %= config->number_of_inputs;

        return rnum;
}

static int validate_seq_ans(unsigned char ans, int seed){
	set_rand_seed(seed);
	if((int)ans == gen_seq_ans()){
		return ROUND_WIN;
	}else {
		return ROUND_LOSS;
	}
}


int generate_table() {
	if(config == NULL){
		return TABLE_FAIL;
	}

	unsigned int seed = seed_gen(0);

	char outbuf[1024];

	snprintf(outbuf, sizeof(outbuf), "--- Sequence Table ---\n");
	print(outbuf, strlen(outbuf));

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

	snprintf(outbuf, sizeof(outbuf), "\n--- Input Mapping Table ---\n");
	print(outbuf, strlen(outbuf));

	for (int i = 0; i < gcomplex.max_table_offset; i++) {
		int offset = snprintf(outbuf, sizeof(outbuf), "Seq:%d -> ", i);
		set_rand_seed(seed + i);
		snprintf(outbuf + offset, sizeof(outbuf) - offset, "%d\n",gen_seq_ans());
		print(outbuf, strlen(outbuf));
	}


	return GAME_SUCCESS;
}


int init_game(struct gameconfig *gconfig){
	if(gconfig == NULL){
		return GAME_INIT_FAIL;
	}

	/* Set the game config */
	config = gconfig;

	init_game_level(config->level);

	if(config->number_of_inputs == 0)
		config->number_of_inputs = 2;

	return GAME_SUCCESS;
}


static int count_down(){
	char outbuf[1024];
	snprintf(outbuf, sizeof(outbuf), "Starting Game in\n");
	print(outbuf, strlen(outbuf));
	snprintf(outbuf, sizeof(outbuf), "3\n");
	print(outbuf, strlen(outbuf));
	delay_ms(1000);
	snprintf(outbuf, sizeof(outbuf), "2\n");
	print(outbuf, strlen(outbuf));
	delay_ms(1000);
	snprintf(outbuf, sizeof(outbuf), "1\n");
	print(outbuf, strlen(outbuf));
	delay_ms(1000);
	clr_dispbuf();
	snprintf(outbuf, sizeof(outbuf), "\n");
	print(outbuf, strlen(outbuf));
}


int start_game_round(void){
	unsigned char binbuf[2];

	count_down();

	/* Randomly select a sequence offest */
	unsigned int seed = seed_gen(1);
	set_rand_seed(seed);
	int seq_offset = get_rand_seqno();

	/* Generate the sequence based on the offset*/
	int seq_seed = seed_gen(0);
	set_rand_seed(seq_seed + seq_offset);

	for (int j = 0; j < gcomplex.max_seq_length; j++) {
		int num = get_rand();
		binbuf[0] = (unsigned char)(num & 0xFF);
		binbuf[1] = (unsigned char)((num >> 8) & 0xFF) ;
		printbin(binbuf,(binbuf[1] == 0)?1:2);
		delay_ms(gcomplex.disp_delay_ms);
	}

	/* Select Input */
	unsigned char in_val;
	readinput(&in_val);

	int ret = validate_seq_ans(in_val, seq_seed + seq_offset);
	return ret;
}
