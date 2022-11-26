CFLAGS= -std=c99 -Wall -Wextra -Werror -g

cluster: cluster.c
	gcc $(CFLAGS) cluster.c -o cluster -lm
testing: testing.c
	gcc $(CFLAGS) testing.c -o testing
test2: test2.c
	gcc $(CFLAGS) test2.c -o test2
test1: test1.c
	gcc $(CFLAGS) test1.c -o test1
distance: distance.c
	gcc $(CFLAGS) distance.c -o distance