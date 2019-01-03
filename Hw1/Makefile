#Thomas Nemeh. September 14, 2018.
#Makefile to compile programs for hw. Also includes clean target to delete executables.

all: hello student-rot128 student-diamond

hello: HelloWorld.c
	gccx -o hello HelloWorld.c

student-rot128: rot128.c
	gccx -o student-rot128 rot128.c

student-diamond: diamond.c
	gccx -o student-diamond diamond.c

clean: 
	rm -f hello student-rot128 student-diamond


