#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_t *game, unsigned int snum);
static char next_square(game_t *game, unsigned int snum);
static void update_tail(game_t *game, unsigned int snum);
static void update_head(game_t *game, unsigned int snum);

/* Task 1 */
game_t *create_default_game() {
  // TODO: Implement this function.
  game_t * game =(game_t*) malloc((sizeof(game_t)));
  game->num_rows=18;
  game->num_snakes=1;
  snake_t * snake=(snake_t*)malloc(10*sizeof(snake_t));
  snake[0].head_col=4;
  snake[0].head_row=2;
  snake[0].tail_col=2;
  snake[0].tail_row=2;
  snake[0].live=true;
  game->snakes=snake;
  //board
  game->board=(char **)malloc (18*sizeof(char *));
  for(int i=0;i<18;i++){
      game->board[i]=(char *) malloc(22*sizeof(char));
  }
  strcpy(game->board[0],"####################\n");
  strcpy(game->board[17],"####################\n");
  for(int i=1;i<17;i++){
      strcpy(game->board[i],"#                  #\n");
  }
  game->board[2][2]='d';
  game->board[2][3]='>';
  game->board[2][4]='D';
  game->board[2][9]='*';
  return game;
}

/* Task 2 */
void free_game(game_t *game) {
  // TODO: Implement this function.
  free(game->snakes);
  for(int i=0;i<game->num_rows;i++){
      free(game->board[i]);
  }
  free(game->board);
  free(game);
  return;
}

/* Task 3 */
void print_board(game_t *game, FILE *fp) {
  // TODO: Implement this function.
  if(fp==NULL)printf("file is not opened");
  for(int i=0;i<game->num_rows;i++){
      fprintf(fp,"%s",game->board[i]);
  }
  return;
}

/*
  Saves the current game into filename. Does not modify the game object.
  (already implemented for you).
*/
void save_board(game_t *game, char *filename) {
  FILE *f = fopen(filename, "w");
  print_board(game, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_t *game, unsigned int row, unsigned int col) { return game->board[row][col]; }

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch) {
  game->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  if(strchr("wasd",c)!=NULL && c != '\0')return true;
  return false;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  if(strchr("WASDx",c)!=NULL && c !='\0')return true;
  return false;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  if(strchr("wasd^<v>WASDx",c)!=NULL && c!='\0')return true;
  return false;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  switch (c) {
      case '^':return 'w';
      case '<':return 'a';
      case 'v':return 's';
      case '>':return 'd';
      default:return '?';
  }
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  switch (c) {
      case 'W':return '^';
      case 'A':return '<';
      case 'S':return 'v';
      case 'D':return '>';
      default:return '?';
  }
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  if(strchr("vsS",c)!=NULL && c !='\0'){
      return cur_row+1; 
  }
  if (strchr("^wW",c)!=NULL && c!='\0') {
      return cur_row-1;
  }
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  if(strchr(">dD",c)!=NULL && c!='\0')return cur_col+1;
  if(strchr("<aA",c)!=NULL && c!='\0')return cur_col-1;
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_game. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int head_row =game->snakes[snum].head_row;
  unsigned int head_col =game->snakes[snum].head_col;
  char c = get_board_at(game,head_row,head_col);
  unsigned int  row=get_next_row(head_row,c);
  unsigned int  col =get_next_col(head_col,c);
  return get_board_at(game,row,col);
}

/*
  Task 4.3

  Helper function for update_game. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int head_row =game->snakes[snum].head_row;
  unsigned int head_col =game->snakes[snum].head_col;
  char head = get_board_at(game,head_row,head_col);
  unsigned int  row=get_next_row(head_row,head);
  unsigned int  col =get_next_col(head_col,head);
  set_board_at(game,row,col,head);
  set_board_at(game,head_row,head_col,head_to_body(head));
  game->snakes[snum].head_row=row;
  game->snakes[snum].head_col=col;
  return;
}

/*
  Task 4.4

  Helper function for update_game. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int tail_row =game->snakes[snum].tail_row;
  unsigned int tail_col =game->snakes[snum].tail_col;
  char tail = get_board_at(game,tail_row,tail_col);
  unsigned int  row=get_next_row(tail_row,tail);
  unsigned int  col =get_next_col(tail_col,tail);
  char new_tail=get_board_at(game,row,col);
  set_board_at(game,row,col,body_to_tail(new_tail));
  set_board_at(game,tail_row,tail_col,' ');
  game->snakes[snum].tail_row=row;
  game->snakes[snum].tail_col=col;
  return;
}

/* Task 4.5 */
void update_game(game_t *game, int (*add_food)(game_t *game)) {
  // TODO: Implement this function.
  for(unsigned int i=0;i<game->num_snakes;i++){
    if(!game->snakes[i].live)continue;
    char c =next_square(game,i);
    unsigned int  head_row=game->snakes[i].head_row;
    unsigned int  head_col=game->snakes[i].head_col;
    if(c == '*'){
        update_head(game,i);
        add_food(game);
    }
    else if( c==' '||is_tail(c)){
        update_head(game,i);
        update_tail(game,i);
    }
    else {
        char current_head = get_board_at(game, head_row, head_col);
        if (current_head != '\n' && current_head != '\0') {
            set_board_at(game, head_row, head_col, 'x');
        }
        game->snakes[i].live=false;
    }
  }
  return;
}

/* Task 5.1 */
char *read_line(FILE *fp) {
  // TODO: Implement this function.
    if(fp==NULL)return NULL;
    unsigned int capacity = 64; // 初始容量，小一点没关系，我们有 realloc
    char *buffer = (char *)malloc(capacity * sizeof(char));
    if (buffer == NULL) return NULL;

    unsigned int length = 0;
    int c;

    // 逐个字符读取，直到遇到 EOF 或者换行符 \n
    while ((c = fgetc(fp)) != EOF) {
        // 如果当前长度快要超过容量了（要留一个位置给 '\0'）
        if (length + 1 >= capacity) {
            capacity *= 2; // 容量翻倍
            char *temp = (char *)realloc(buffer, capacity * sizeof(char));
            if (temp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        buffer[length] = (char)c;
        length++;

        // 如果读到了换行符，这一行就结束了
        if (c == '\n') {
            break;
        }
    }

    // 如果连一个字符都没读到（比如直接遇到了 EOF），释放内存并返回 NULL
    if (length == 0) {
        free(buffer);
        return NULL;
    }

    // 别忘了 C 语言字符串的灵魂结尾！
    buffer[length] = '\0';
    return buffer;
}

/* Task 5.2 */
game_t *load_board(FILE *fp) {
  // TODO: Implement this function.
    game_t * game =(game_t*)malloc(sizeof(game_t));
    if(game ==NULL){
        free(game);
        return NULL;
    }
    unsigned int size =20;
    game->board=(char **)malloc(size*sizeof(char*));
    unsigned int num_rows=0;
    char * line;
    while ((line =read_line(fp))!=NULL) {
        if(num_rows==size){
            size*=2;
            char** temp=realloc(game->board,size*sizeof(char*));
            if(temp==NULL){
                free(temp);
                free(game->board);
                free(game);
                return NULL;
            }
            game->board=temp;
        }    
       game->board[num_rows]=line; 
       num_rows++;
}
    game->num_rows=num_rows;
    game->num_snakes=0;
    game->snakes=NULL;
    return game;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  snake_t snake=game->snakes[snum];
  unsigned int current_row=snake.tail_row;
  unsigned int current_col=snake.tail_col;
  char current_c=get_board_at(game,current_row,current_col);
  while (!is_head(current_c)) {
      unsigned int next_row=get_next_row(current_row,current_c);
      unsigned int next_col=get_next_col(current_col,current_c);
      if(next_row==current_row && next_col==current_col)break;
      current_row=next_row;
      current_col=next_col;
      
      current_c=get_board_at(game,current_row,current_col);
  }
  game->snakes[snum].head_col=current_col;
  game->snakes[snum].head_row=current_row;
  return;
}

/* Task 6.2 */
game_t *initialize_snakes(game_t *game) {
  // TODO: Implement this function.
  unsigned int num_snakes=0;
  for(unsigned int row =0;row<game->num_rows;row++){
    char * line =game->board[row];
    for(unsigned int col=0;line[col]!='\0'&& line[col]!='\n';col++){
        if(is_tail(line[col]))num_snakes++;
    }
  }
  if(num_snakes==0)return game;
  game->num_snakes=num_snakes;
  game->snakes=(snake_t*)malloc(num_snakes*sizeof(snake_t));
  if(game->snakes==NULL)return game;
  int i=0;
  for(unsigned int row =0;row<game->num_rows;row++){
    char * line =game->board[row];
    for(unsigned int col=0;line[col]!='\0'&& line[col]!='\n';col++){
        if(is_tail(line[col])){
            game->snakes[i].tail_col=col;
            game->snakes[i].tail_row=row;
            i++;
        }
    }
  }
  for(unsigned int j=0;j<num_snakes;j++){
      find_head(game,j);
      char c=get_board_at(game,game->snakes[j].head_row,game->snakes[j].head_col);
      if(c!='x')game->snakes[j].live=true;
      else{
          game->snakes[j].live=false;
      }
  }
  return game;
  
}

