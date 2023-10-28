make: main.c generator.c geography.c buildings.c data.c iutils.c
	 gcc main.c generator.c geography.c buildings.c data.c iutils.c -l raylib -lm -o city_generator -g3
	 
