/*
TODO
    - add documentation (README)
*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// function prototypes
void init_game();
void draw_field();
void next_move();
int check_end_of_game();

char player_symbol, pc_symbol, start_smybol;
char field[] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
int available_fields[] = {0,1,2,3,4,5,6,7,8};
int available_fields_len = 9;




int main() {

    init_game();
    
    while(check_end_of_game()) {
        draw_field();
        next_move();
    }
    
    return 0;
}




void init_game() {
    // initializing game with symbols and starting symbol
    system("cls");

    printf("Choose between 'o' and 'x': ");
    scanf(" %c", &player_symbol);
    while(player_symbol != 'x' && player_symbol != 'o') {
        printf("Please enter a valid symbol: ");
        scanf(" %c", &player_symbol);
    }

    // determine pc_smybol's value
    pc_symbol = (player_symbol == 'x') ? 'o': 'x';

    // deciding starting symbol
    srand(time(NULL));
    start_smybol = (rand()%2 == 0) ? 'x' : 'o';
    //printf("start symbol is: %c\n", start_smybol);
    
    if(start_smybol == player_symbol) {
        printf("Player has the first move\n");
    } else {
        printf("PC has the first move\n");
    }
    Sleep(2000);
    system("cls");
    for (int i=3; i>0; i--) {
        printf("Game starts in: %i", i);
        Sleep(1000);
        system("cls");
    }
}




void draw_field() {
    // drawing the board
    char horisontal_line[] = "*---------*---------*---------*";
    char vertical_line[] =   "|         |         |         |";
    int vertical_cnt = 0;
    int field_cnt = 0;

    system("cls");

    for (int i=0; i<13; i++) {
        
        if(i%4 == 0){
            puts(horisontal_line);
            vertical_cnt = 0;
        } 
        else if(vertical_cnt == 1) {
            // adding the placed characters to the board
            char vertical_copy[strlen(vertical_line)];
            strncpy(vertical_copy, vertical_line, strlen(vertical_line));
            vertical_copy[5] = field[field_cnt++];
            vertical_copy[15] = field[field_cnt++];
            vertical_copy[25] = field[field_cnt++];
            puts(vertical_copy);
            vertical_cnt++;
        } 
        else {
            puts(vertical_line);
            vertical_cnt++;
        }
    }
}




void rearrange_list(int idx) {
    // moving the chosen field index out of the available field range
    for(int j=idx; j<available_fields_len; j++) {
        if(j<available_fields_len-1) {
            available_fields[j] = available_fields[j+1];
        }
    }
    available_fields_len--;
}




int validate_player_move(int idx) {
    // validating the player's input (if input is in range and is still available)

    // if input is invalid
    if(idx < 1 && idx > 9) { 
        return 1;
    }

    // if input is valid
    for(int i=0; i<available_fields_len; i++) {
        // if move is valid
        if(idx-1 == available_fields[i]) {
            field[available_fields[i]] = player_symbol;
            
            rearrange_list(i);

            return 0;
        }
    }
    
    // if move is invalid
    return 1;
}




void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}




void player_move() {
    // getting user input for the chosen field
    if(available_fields_len > 0) {
        int move = 0;

        printf("Enter your next move (1-9, top left is 1): ");
        scanf("%d", &move);
            
        // checking if the player input is a valid field value
        while(validate_player_move(move)){
            clear_input_buffer(); // clearing buffer if user input is a character
            printf("Enter a different move (1-9, top left is 1): ");
            scanf("%d", &move);
        }
    }
}




void pc_move() {
    // selecting a random available field from the list
    if(available_fields_len > 0) {
        int idx = (rand() % (available_fields_len));

        field[available_fields[idx]] = pc_symbol;
        
        rearrange_list(idx);
    }
}



/*
void print_field_options() {
    printf("the available fields are: ");
    for(int i=0; i<available_fields_len; i++) {
        printf("%i   ", available_fields[i]+1);
    }
    printf("\n");
}
*/



void next_move() {
    // determining move order according to the initialization
    if(player_symbol == start_smybol) {
        player_move();
        pc_move();
        draw_field();
    } else {
        pc_move();
        draw_field();
        player_move();
    }
}




int check_end_of_game() {
    char winner = 'd';

    // checking for winning row/column/diagonal
    for(int i=0; i<7; i+=3) {
        if(field[i] == field[i+1] && field[i+1] == field[i+2]) {
            winner = field[i];
        } else if(field[i/3] == field[i/3+3] && field[i/3+3] == field[i/3+6]) {
            winner = field[i/3];
        }
    }

    if (field[0] == field[4] && field[4] == field[8]) {
        winner = field[0];
    }
    else if (field[2] == field[4] && field[4] == field[6]) {
        winner = field[2];
    }

    // determining the outcome
    if(winner == player_symbol) {
        draw_field();
        printf("Player won!\n");
        return 0;
    }
    else if(winner == pc_symbol) {
        draw_field();
        printf("PC won!\n");
        return 0;
    }
    else if(available_fields_len == 0 && winner == 'd') {
        draw_field();
        printf("Draw\n");
        return 0;
    }

    return 1;
}