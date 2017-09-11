exe : maxi.o maxi_test_v2.o
	gcc -o exe maxi.o maxi_test_v2.o -lcunit -L /usr/local/lib
maxi_test_v2.o : maxi_test_v2.c
	gcc -c maxi_test_v2.c
maxi.o: maxi.c
	gcc -c maxi.c
