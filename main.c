#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gameengine.h"

int input(unsigned char *in) {
	int val = -1;
	printf("\nEnter the Input: ");
	scanf("%d",&val);
	*in = val;

	return 0;
}

int clr_output(){
	printf("\033[2J\033[H");
	fflush(stdout);
	return 0;
}

int output (char *out, unsigned int size){
	printf("%s",out);
	return 0;
}

int output_bin (unsigned char *out, unsigned int size){
	if(size == 1){
		printf("\33[2K\r");
		printf("\r%08b --- %d",(unsigned int)*out, (unsigned int)*out);
	} else {
		printf("\r%016b",(*(unsigned int*)out) & 0xFFFF );
	}
	fflush(stdout);
	return 0;
}


int delay_function(unsigned int dlay_ms){
	usleep(dlay_ms * 1000);
	return 0;
}

int random_seed (int sd){
	srand(sd);
        return 0;
}

int random_numgen (void){
	return rand();
}


int main(){
	int ret = -1;

	struct random_ops random_gen_t = {
		.randseed = random_seed,
		.randnum = random_numgen,
	};

	struct gameops g_ops = {
		.getinput = input,
		.display = output,
		.display_bin = output_bin,
		.clear_dispbuffer = clr_output,
		.delayms_fn = delay_function,
		.rand_ops = &random_gen_t
	};

	struct gameconfig g_config = {
		.level = EASY,
		.number_of_inputs = 3,
		.ops = &g_ops,
	};




	ret = init_game(&g_config);
	if (ret < 0){
		printf("Error: %d\n",ret);
		return -1;
	}

	ret = generate_table();
	if (ret < 0){
		printf("Error: %d\n",ret);
                return -1;
        }


	ret = start_game_round();
	if (ret == ROUND_WIN){
		printf("Correct Answer\n");
	}else if (ret == ROUND_LOSS){
		printf("Wrong Answer\n");
	}

        return 0;
}
