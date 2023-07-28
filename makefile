debug:
	g++ CAApp.cpp `sdl2-config --cflags --libs` -o app

release:
	g++ -O2 CAApp.cpp `sdl2-config --cflags --libs` -o app
