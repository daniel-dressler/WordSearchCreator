/* ----------- Includes -------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ----------- Declarations ---------------- */
#define RESIZE_THRESHOLD 20
/* Debuging */
/* In production only the board unformated
 * and dimensions will be sent to stdout. */
/*#define DEBUG 1 */
#ifndef DEBUG
	#define console(args) 
	#define printBoard(this) \
		printf("%d,%d,%s", this->width, this->height, this->board);
#else
	#define console(args) printf(args)
	#define printBoard(this) {\
		console("-- Board --\n");
		int i = 0;\
		while (i < this->area) {\
			puts(this->board[i++]);\
			if (i % this->width == 0)\
				puts("\n");\
		}\
	}
#endif


/* We need direct addressing so unicode8
 * cannot be used directly. No problem. */
typedef char letter;

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

letter **parseWordList (int, letter *);
int insertWordInBin(board_obj *,
					letter *,
					point,
					point);
void createWordSearch(point *);

/* ----------- Board Member data ---------------- */
typedef struct {
	int num_rows;
	int *row;
	
	int num_cols;
	int *col;
	
	int num_dias;
	int *dia;
	int dia_offset
} bin_s;

typedef struct {
	int width;
	int height;
	int area;
	letter *board;
	
	int allowed_angles;
	bin_s bin;
	
	int num_words;
	int words_iter;
	letter **words;
	
	int num_swears;
	letter **swears;	
	
	int unfit_boards;
} board_obj;


/* ----------- Board Member functions ----------------*/
void newBoard(board_obj *this, int width, int height)
{
	this->width = width;
	this->height = height;
	this->area = width * height;
	this->board = calloc(sizeof(letter), this.area);
	
	this->bin.num_rows = height;
	this->bin.row = malloc(sizeof(int) * height);
	for (int i = 0; i < height; i++) {
		this->bin.row[i] = width;
	}
	
	this->bin.num_cols = width;
	this->bin.col = malloc(sizeof(int) * width);
	for (int i = 0; i < width; i++) {
		this->bin.col[i] = height;
	}
	
	/* Sat down with pencil and paper
	 * and worked out these formulas.
	 * If you need to understand them
	 * you'll want to do the same. */
	this->bin.num_dias = width + height - 1;
	this->bin.dia = malloc(sizeof(int) * this->bin.num_dias);
	this->bin.dia_offset = width - 1;
	console("-- dia capacity --\n");
	for (int i = 0; i < this.bin.num_dias; i++) {
		int w = this.bin.dia_offset - i;
		if (w > 0)
			this->bin.dia[i] = width - w;
		else
			this->bin.dia[i] = height + w;
		console("%d: %d\n", i, this->bin.dia[i]);
	}
	console("\n\n");
	
	this->words_iter = 0;
	this->unfit_boards = 0;
}

void resizeBoard(board_obj *this, int factor)
{
	this->words_iter = 0;
	this->unfit_boards = 0;
	free(this->board);
	newBoard(this, this->.width + factor, this->height + factor);
}

void clearBoard(board_obj *this)
{
	free(this->board);
	newBoard(this, this->.width + factor, this->height);
}


/* ----------- Point Object ----------------- */
typedef struct {
	int x;
	int y;
} point;

point getRandomPoint(board_obj board)
{
	point p;
	p.x = rand() % board->width;
	p.y = rand() % board->height;
	return p;
}

point getNextPoint(board_obj board, point p, point dp)
{
	p.x = (p.x + dp.x) % board->width;
	p.y = (p.y + dp.y) % board->height;
	return p;
}

/* -------------- Main ----------------- */
void main (int argc, char *args[])
{
	board_obj this;
	
	newBoard(&this, atoi(args[1]), atoi(args[2]);
	this.allowed_angles = atoi(args[3]);
	
	this.num_words = atoi(args[4]);
	this.words = parseWordList(this.num_words, args[5]);
	
	this.num_swears = atoi(args[6]);
	this.swears = parseWordList(this.num_swears, args[7]);
	
	srand(atoi(args[8]));
	
	while (!createWordSearch(this)) {/*empty*/}
	
	printBoard();
}

letter **parseWordList (int length, char *source)
{
	letter **words = malloc(sizeof(*words) * length);
	int i = 0;
	int k = 0;
	
	do {
		*(words + i++) = (letter *)(source + k);
		while (*(source + k) != ';') {
			k++;
		}
	} while (i < length);
	return words;
}

/* -------------- Bin checks ---------------- */
int fitCol(board_obj board, point p, word_t word)
{
	return (board->bin.col[p.x] <= word.length);
}
void addCol(board_obj board, point p)
{
	board->bin.col[p.x]--;
}


int fitRow(board_obj board, point p, word_t word)
{
	return (board->bin.col[p.y] <= word.length);
}
void addRow(board_obj board, point p)
{
	board->bin.col[p.y]--;
}

int fitDia(board_obj board, point p, word_t word)
{
	return (board->bin.dia[p.y - p.x + this->bin.dia_offset]
													<= word.length);
}
int addDia(board_obj board, point p)
{
	board->bin.dia[p.y - p.x + this->bin.dia_offset]--;
}


/* check bounds */
#define checkBounds(p) (p.x >= 0 && p.y >= 0 &&
						(p.x < board->width) && (p.y < board->height))

/* provides fast access to a point on the board */
#define accessBoard(p) (*(board->board + p.x + board->width * p.y))

void pasteWord(board_obj *board, letter *word
				point p,
				point dp)
{
	while (accessBoard(p) = *(word)) {
		addCol(board. p);
		addRow(board, p);
		adddia(board, p);
		
		p = getNextPoint(board, p, dp);
		word++;
	}
}

int testFit(board_obj *board,
					letter *word,
					point p,
					point dp)
{
	int i = 0;
	while (checkBounds(p) &&
			(accessBoard(p) == '\0' ||
			 accessBoard(p) == word[i++])) {
		p = getNextPoint(board, p, dp);
		if (word[i] == '\0')
			return 1;
	}
	return 0;
}

int insertWordInBin(board_obj *board,
					letter *word,
					point p,
					point dp)
{
	point p_orgin;
	point inverse_p;
	point inverse_dp;
	
	inverse_dp = {-dp.x, -dp.y};
	do {
		if (testFit(board, word, p, dp)) {
			pasteWord(board, word, p, dp);
			return 1;
		}
		if (testFit(board, word, inverse_p, inverse_dp)) {
			pasteWord(board, word, inverse_p, inverse_dp);
			return 1;
		}
		
		p = getNextPoint(board, p, dp);
		inverse_p = getNextPoint(board, inverse_p, inverse_dp);
	} while (checkBounds(p) || checkBounds(inverse_p));
	return 0;
}

/* ------------ Word Search Creating Algorithmn -------- */
/* The board is layed out from top left corner.
 * like windowing addresses.*/

int createWordSearch(point *board)
{
	point p;
	point p_origin;
	point diagonal;
	word_t word;
	int tries = 0;
	
	word = this->words[this->words_iter++];
	while (word != NULL) {
		p = getRandomPoint(board);
		p_origin = p;
		diagonal = p.y - p.x + board->bin.dia_offset;
		
		/* find room for word */
		do {
			/* todo: fix proapbilities */
			if (NORTHWEST ^ board->allowed_angles &&
				fitDia(board, p, word) &&
				insertWordInBin(board, word, p, {-1, -1})) {
				break;
			} else
			if (NORTH ^ board->allowed_angles &&
				fitCol(board, p, word) &&
				insertWordInBin(board, word, p, {0, -1})) {
				break;
			} else
			if (NORTHEAST ^ board->allowed_angles &&
				fitDia(board, p, word) &&
				insertWordInBin(board, word, p, {1, -1})) {
				break;
			} else
			if (EAST ^ board->allowed_angles &&
				fitRow(board, p, word) &&
				insertWordInBin(board, word, p, {1, 0})) {
				break;
			} else
			if (SOUTHEAST ^ board->allowed_angles &&
				fitRow(board, p, word) &&
				insertWordInBin(board, word, p, {1, 1})) {
				break;
			} else
			if (SOUTH ^ board->allowed_angles &&
				fitRow(board, p, word) &&
				insertWordInBin(board, word, p, {0, 1})) {
				break;
			} else
			if (SOUTHWEST ^ board->allowed_angles &&
				fitRow(board, p, word) &&
				insertWordInBin(board, word, p, {-1, 1})) {
				break;
			} else
			if (WEST ^ board->allowed_angles &&
				fitRow(board, p, word) &&
				insertWordInBin(board, word, p, {-1, 0})) {
				break;
			} else {
				p = getNextPoint(board, p, {1, 1});
				diagonal = (diagonal + 1) % board->bin.num_dia;
			}
		} while (p != p_origin);
		
		/* If we failed to place a word
		 * then reset and keep trying */
		if (p == p_origin) {
			if (tries++ < RESIZE_THRESHOLD) {
				clearBoard(board);
			} else {
				tries = 0;
				resizeBoard(board, 1, 1);
			}
		}
		
		word = this->words[this->words_iter++];
	}
	
	/* Fill Empty Points */
	
	/* if we find a swear */
	if (0) {
		if (board->unfit_boards++ > RESIZE_THRESHOLD)
			resizeBoard(board, 1);
		else
			clear_board();
		return 0;
	}
	
	return 1;
}
