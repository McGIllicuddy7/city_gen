make: main.c generator.c geography.c buildings.c
	gcc main.c generator.c geography.c buildings.c -framework GLUT -framework OPENGL -l pasco -o city_generator