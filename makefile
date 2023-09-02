make: main.c generator.c geography.c buildings.c iutils.c
	 gcc main.c generator.c geography.c buildings.c iutils.c -lGL -lglut -lm -o city_generator
	 