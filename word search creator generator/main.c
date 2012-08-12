#include <stdio.h>
	
/* Like unix permissions. Each new permission is greator than
 * all prior ones combined.
 */
enum angles {
	NORTHWEST = 1,
	NORTH     = 2,
	NORTHEAST = 4,
	EAST      = 8,
	SOUTHEAST = 16,
	SOUTH     = 32,
	SOUTHWEST = 64,
	WEST      = 128
}
/* Add them up to assemble a set of allowed angles */

/* We need direct addressing so unicode8
 * cannot be used directly. No problem. */
typedef char point;

point **parseWordList (int, point);

/* GLOBAL DATA
 * Pretend this is an object and these are our
 * members */
int width;
int height;
int goal;
int angles_allowed;

/* SETUP */
/* ===== */
void main (int argc, char *args[])
{
	width  = atoi(args[1]);
	height = atoi(args[2]);
	goal = atoi(args[3]);
	angles_allowed = atoi(args[4]);
	
	int num_source_words = atoi(args[5]);
	point *source_words = (point *)args[6];
	point **words = parseWordList(num_source_words, source_words);
	
	int num_band_words = atoi(args[5]);
	point *source_band_words = (point *)args[6];
	point **band_words =
				parseWordList(num_band_words, source_band_words);
	
	point *board = calloc(sizeof(point), width * height);
}

point **parseWordList (int length, point *source)
{
	point **words = malloc(sizeof(**words) * length);
	int i = 0;
	int k = 0;
	
	do {
		*(words + i++) = source;
		while (*(source + k) != ';') {
			k++;
		}
	} while (i < length);
	return words;
}

/* Board manipulation */
/* The board is layed out from top left corner.
 * like windowing addresses.*/
/* ================== */
/* check bounds, no negative checking */
#define b(x, y) ((x < width) &&	(y < height))

/* provides fast access to a point on the board */
#define p(x, y) (*(board + x + width * y))

int test_direction(point *board, point *word,
					int pos_hoz, int pos_vert,
					int velocity_hoz, int velocity_vert)
{
	int i = 0;
	while (b(pos_hoz, pos_vert) &&
			(p(pos_hoz, pos_vert) == '\0' ||
			 p(pos_hoz, pos_vert) == word[i++])) {
		pos_hoz  += velocity_hoz;
		pos_vert += velocity_vert;
		if (word[i] == '\0')
			return 1;
	}
	return 0;
}

int fits(point *board, point *word, int test_angles, int x, int y,)
{
	int does_fit = 0;
	if (!(does_fit || test_angles ^ NORTHWEST))
		does_fit = (test_direction(board, word, x, y, -1, -1));
	if (!(does_fit || test_angles ^ NORTH))
		does_fit = (test_direction(board, word, x, y, 0, -1));
	if (!(does_fit || test_angles ^ NORTHEAST))
		does_fit = (test_direction(board, word, x, y, 1, -1));
	
	if (!(does_fit || test_angles ^ EAST))
		does_fit = (test_direction(board, word, x, y, 1, 0));
	
	if (!(does_fit || test_angles ^ SOUTHEAST))
		does_fit = (test_direction(board, word, x, y, 1, 1));
	if (!(does_fit || test_angles ^ SOUTH))
		does_fit = (test_direction(board, word, x, y, 1, 0));
	if (!(does_fit || test_angles ^ SOUTHWEST))
		does_fit = (test_direction(board, word, x, y, -1, 1));
	
	if (!(does_fit || test_angles ^ WEST))
		does_fit = (test_direction(board, word, x, y, -1, 0));
	
	return does_fit;
}

void place_word(point *board, point *word
				int pos_hoz, int pos_vert,
				int velocity_hoz, int velocity_vert)
{
	while (p(pos_hoz, pos_vert) = *(word++)) {
		pos_hoz  += velocity_hoz;
		pos_vert += velocity_vert;
	}
}

