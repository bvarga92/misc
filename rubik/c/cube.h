#ifndef _CUBE_H_
#define _CUBE_H_

	typedef struct{
		unsigned size;
		char *colors;
	} cube_t;

	void draw(const cube_t *cube);
	void move(const char *seq, cube_t *cube);
	void randomScramble(char *scrmbl, unsigned length);
	unsigned solve2x2(const cube_t *cube, char **moves);
	unsigned solve3x3(const cube_t *cube, char **moves);

#endif
