#include <stdio.h>
#include <stdlib.h>

#include "gameengine.h"

int input(char * in) {
	printf("Input Fn called\n");
	return 0;
}

int output (char *out, unsigned int size){
	printf("%s",out);

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
		.rand_ops = &random_gen_t
	};

	struct gameconfig g_config = {
		.level = EASY,
		.ops = &g_ops,
	};



	ret = init_game(&g_config);
	if (ret < 0){
		printf("Error\n");
		return -1;
	}

	start_game();



        return 0;
}
