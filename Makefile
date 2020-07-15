make:
	g++ platformy.cpp `pkg-config --libs --cflags sdl2`
	./a.out
