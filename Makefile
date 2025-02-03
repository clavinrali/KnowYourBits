TARGET := knowyourbits


all:
	${CC} -o ${TARGET} main.c gameengine.c
clean:
	rm -rf ${TARGET}
