make: main.c generator.c geography.c buildings.c iutils.c
	 gcc main.c generator.c geography.c buildings.c iutils.c -l raylib -lm -o city_generator -g3
	 
