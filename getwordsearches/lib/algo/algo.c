// ./a.out 5 5 255 1 "a;" 1 "fuck;" 1231
// todo: fix allowed angles

/* =========== Includes ============== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* =========== Declarations ============== */
#define RESIZE_THRESHOLD 20
/* Debuging */
/* In production only the board unformated
 * and dimensions will be sent to stdout. */
#define __DEBUG__ 1
#ifndef __DEBUG__
	#define console(...) 
	#define printBoard(this) \
		printf("%d,%d,%s\n", this.width, this.height,\
												(char *)this.board);
#else
	#define console(...) printf(__VA_ARGS__)
	#define printBoard(this) {\
		console("-- Board --\n");\
		int i = 0;\
		while (i < this.area) {\
			putchar(this.board[i++]);\
			if (i % this.width == 0)\
				putchar('\n');\
		}\
	}
#endif

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
};
/* Add them up to assemble a set of allowed angles */


/* ---------- Words ----------------------------- */
/* We need direct addressing so unicode8
 * cannot be used directly. No problem. */
typedef char letter;
typedef struct {
	int length;
	letter *string;
} word_s;


/* =========== Board Object ===================== */
/* ----------- Board Member data ---------------- */
typedef struct {
	int num_rows;
	int *row;
	
	int num_cols;
	int *col;
	
	int num_dias;
	int *dia;
	int dia_offset;
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
	word_s *words;
	
	int num_swears;
	word_s *swears;	
	
	int unfit_boards;
} board_obj;


/* ----------- Board Member functions ----------------*/
void newBoard(board_obj *this, int width, int height)
{
	int i;
	int w;
	
	this->width = width;
	this->height = height;
	this->area = width * height;
	this->board = calloc(sizeof(letter), this->area);
	
	this->bin.num_rows = height;
	this->bin.row = malloc(sizeof(int) * height);
	for (i = 0; i < height; i++) {
		this->bin.row[i] = width;
	}
	
	this->bin.num_cols = width;
	this->bin.col = malloc(sizeof(int) * width);
	for (i = 0; i < width; i++) {
		this->bin.col[i] = height;
	}
	
	/* Sat down with pencil and paper
	 * and worked out these formulas.
	 * If you need to understand them
	 * you'll have to do the same.
	 * Sorry, I don't know how I could
	 * explain them. */
	this->bin.num_dias = width + height - 1;
	this->bin.dia = malloc(sizeof(int) * this->bin.num_dias);
	this->bin.dia_offset = width - 1;
	console( "-- dia capacity --\n" );
	for (i = 0; i < this->bin.num_dias; i++) {/*todo: fix formula on non-squares*/
		w = this->bin.dia_offset - i;
		if (w > 0)
			this->bin.dia[i] = width - w;
		else
			this->bin.dia[i] = height + w;
		console( "%d: %d\n", i, this->bin.dia[i] );
	}
	console( "\n\n" );
	
	this->words_iter = 0;
	this->unfit_boards = 0;
}

void resizeBoard(board_obj *this, int factor)
{
	console("Resizing board to %d:%d\n", this->width + factor, 
											this->height + factor);
	this->words_iter = 0;
	this->unfit_boards = 0;
	free(this->board);
	newBoard(this, this->width + factor, this->height + factor);
}

void clearBoard(board_obj *this)
{
	console("Clearing board\n");
	free(this->board);
	newBoard(this, this->width, this->height);
}


/* =========== Point Object ============== */
typedef struct {
	int x;
	int y;
} point;

point getRandomPoint(board_obj *board)
{
	point p;
	p.x = rand() % board->width;
	p.y = rand() % board->height;
	return p;
}

point getNextPoint(board_obj *board, point p, point dp)
{
	/* Ugh, C leaves mod for negative oprands
	 * implementation defined. This means that
	 * -1 % 2 can == -1 and not the more mathy
	 * -1 % 2 == 1. Thus we add an otherwise
	 * redundent factor. This works so long as
	 * the velocity is less than the board size. */
	p.x = (p.x + dp.x + board->width) % board->width;
	p.y = (p.y + dp.y + board->height) % board->height;
	return p;
}


/* =========== Bin checks & manipulators ============== */
int fitCol(board_obj *board, point p, word_s *word)
{
	return (board->bin.col[p.x] <= word->length);
}
void addCol(board_obj *board, point p)
{
	board->bin.col[p.x]--;
}


int fitRow(board_obj *board, point p, word_s *word)
{
	return (board->bin.col[p.y] <= word->length);
}
void addRow(board_obj *board, point p)
{
	board->bin.col[p.y]--;
}

/*todo: add proper support for the other direction of
 * diagonals. */
int fitDia(board_obj *board, point p, word_s *word)
{
	return (board->bin.dia[p.y - p.x + board->bin.dia_offset]
													<= word->length);
}
int addDia(board_obj *board, point p)
{
	board->bin.dia[p.y - p.x + board->bin.dia_offset]--;
}


/* =========== Board manipulators ============== */
/* The board is layed out from top left corner.
 * like windowing addresses.*/
 
/* provides fast access to a point on the board */
#define accessBoard(p) (*(board->board + p.x + board->width * p.y))

#define checkBounds(p) (p.x >= 0 && p.y >= 0 && \
						(p.x < board->width) && (p.y < board->height))

int testForFragmentation(board_obj *board,
					letter *word,
					point p,
					point dp)
{
	int i = 0;
	while (checkBounds(p) &&
			(accessBoard(p) == '\0' ||
			 accessBoard(p) == word[i])) {
		p.x += dp.x;
		p.y += dp.y;
		if (word[++i] == '\0')
			return 1;
	}
	return 0;
}

void pasteWord(board_obj *board,
				letter *word,
				point p,
				point dp)
{
	while (*(word) != '\0' && (accessBoard(p) = *(word))) {
		addCol(board, p);
		addRow(board, p);
		addDia(board, p);
		
		p = getNextPoint(board, p, dp);
		word++;
	}
}

int insertWordInBin(board_obj *board,
					word_s *word,
					point p,
					point dp)
{
	point inverse_p;
	point inverse_dp;
	
	inverse_dp.x = -dp.x;
	inverse_dp.y = -dp.y;
	do {
		if (testForFragmentation(board, word->string, p, dp)) {
			pasteWord(board, word->string, p, dp);
			return 1;
		}
		if (testForFragmentation(board, word->string, inverse_p,
														inverse_dp)) {
			pasteWord(board, word->string, inverse_p, inverse_dp);
			return 1;
		}
		
		p.x += dp.x;
		p.y += dp.y;
		inverse_p.x += inverse_dp.x;
		inverse_p.y += inverse_dp.y;
	} while (checkBounds(p) || checkBounds(inverse_p));
	return 0;
}


/* =========== Algorithmn ============== */

/* ---- Compiled Directions ---- */
typedef struct {
	int direction;
	int (*testDirectionFit)(board_obj *board, point p, word_s *word);
	point unit_vector;
} compiled_direction;

compiled_direction compiled_directions[] = {
	{NORTHWEST , &fitDia, {-1, -1}},
	{NORTH     , &fitCol, { 0, -1}},
	{NORTHEAST , &fitDia, {+1, -1}},
	{EAST      , &fitCol, {+1,  0}},
	{SOUTHEAST , &fitDia, {+1, +1}},
	{SOUTH     , &fitCol, { 0, +1}},
	{SOUTHWEST , &fitDia, {-1, +1}},
	{WEST      , &fitRow, {-1,  0}}
};

int createWordSearch(board_obj *board)
{
	point p;
	point p_origin;
	int diagonal;
	word_s *word;
	int tries = 0;
	int i;
	int i_origin;
	int inserted;
	
	console("== Creating board ==\n");
	
	word = board->words + board->words_iter++;
	while (word->length != 0) {
		console("Trying %s\n", word->string);

		inserted = 0;
		p = getRandomPoint(board);
		p_origin = p;
		diagonal = p.y - p.x + board->bin.dia_offset;
		
		/* find room for word at point p. */
		do {
			/* Test each direction */
			i_origin = i = rand() % 8;
			do {
				if (board->allowed_angles ^
								compiled_directions[i].direction &&
					compiled_directions[i].
								testDirectionFit(board, p, word)) {
					console("Atempting %s\n", word->string);
					inserted = insertWordInBin(board, word, p,
								compiled_directions[i].unit_vector);
					if (inserted) {
						console("Inserted %s\n\n", word->string);
					}
				}
				i = (i + 1) % 8; 
			} while (i != i_origin && !inserted);

			p = getNextPoint(board, p, (point){1, 1});
			/*todo: fix not searching all diagonals */
			diagonal = (diagonal + 1) % board->bin.num_dias;
		} while (!inserted && p.x != p_origin.x);
		
		/* If we failed to place a word
		 * then reset and keep trying */
		if (!inserted) {
			if (tries++ < RESIZE_THRESHOLD) {
				clearBoard(board);
			} else {
				tries = 0;
				resizeBoard(board, 1);
			}
		}
		
		word = board->words + board->words_iter++;
	}
	
	
	/* if we find a swear */
	if (0) {
		if (board->unfit_boards++ > RESIZE_THRESHOLD)
			resizeBoard(board, 1);
		else
			clear_board();
		return 0;
	}
	
	/* Fill Empty Points without adding a swear */
	i = 0;
	while (i < board->area) {
		if (board->board[i] == '\0')
			board->board[i] = '.';
		i++;
	}
	return 1;
}


/* =========== Main ================== */
word_s *parseWordList (int length, char *source)
{
	word_s *words;
	int i = 0;
	int k = 0;

	words = malloc(sizeof(*words) * (length + 1));
	while (i < length) {
		words[i].string = (letter *)(source + k);
		while (source[k] != ';') {
			k++;
		}
		source[k++] = '\0';
		words[i].length = strlen(words[i].string);
		console("Added %d:%s\n", words[i].length, words[i].string);
		i++;
	}
	words[length].length = 0;
	
	return words;
}

void main (int argc, char *args[])
{
	board_obj this;
	
	newBoard(&this, atoi(args[1]), atoi(args[2]));
	this.allowed_angles = atoi(args[3]);
	
	this.num_words = atoi(args[4]);
	this.words = parseWordList(this.num_words, args[5]);
	
	this.num_swears = atoi(args[6]);
	this.swears = parseWordList(this.num_swears, args[7]);
	
	srand(atoi(args[8]));
	
	while (!createWordSearch(&this)) {/*empty*/}
	printBoard(this);
}

