all: ptab.o procs.o com.o student.c
	gcc -c student.c
	gcc -o student ptab.o com.o procs.o student.o -I /usr/pkg/share/x11-links/include -L /usr/pkg/share/x11-links/lib -lX11 -lm -g

