/*
TODO
    - check update logic for player and pc moves
    - make gameplay more fluent
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
void remove_field(int idx);

char player_symbol, pc_symbol, start_smybol;
char field[] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
int available_fields[] = {0,1,2,3,4,5,6,7,8};
int available_fields_len = 9;


int main() {

    init_game();
    Sleep(5000);
    while(check_end_of_game()) {
        draw_field();
        next_move();
    }
    


    return 0;
}


void init_game() {
    system("cls");

    printf("Choose between 'o' and 'x': ");
    scanf(" %c", &player_symbol);
    while(player_symbol != 'x' && player_symbol != 'o') {
        printf("Please enter a valid symbol: ");
        scanf(" %c", &player_symbol);
    }
    //printf("\n");

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
}



void draw_field() {
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

int validate_player_move(int idx) {
    //int valid_move = 0;

    if(idx >= 1 && idx <= 9) {
        for(int i=0; i<available_fields_len; i++) {
            if(idx-1 == available_fields[i]) {
                field[available_fields[i]] = player_symbol;
                
                for(int j=i; j<available_fields_len; j++) {
                    if(j<available_fields_len-1) {
                        available_fields[j] = available_fields[j+1];
                    }
                }
                available_fields_len--;
                return 0;
            }
        }
    }
    return 1;
}

void player_move() {
    int move;
    printf("Enter your next move (1-9, top left is 1): ");
    scanf("%i", &move);
        
    // checking if field is available
    while(validate_player_move(move)){
        printf("Enter a different move (1-9, top left is 1): ");
        scanf("%i", &move);
    }
    

}


void pc_move() {
    int idx = (rand() % (available_fields_len));

    field[available_fields[idx]] = pc_symbol;
    
    for(int i=idx; i<available_fields_len; i++){
        if(i<available_fields_len-1) {
            available_fields[i] = available_fields[i+1];
        }
    }
    available_fields_len--;
}

void print_field_options() {
    printf("the available fields are: ");
    for(int i=0; i<available_fields_len; i++) {
        printf("%i   ", available_fields[i]+1);
    }
    printf("\n");
}

void next_move() {
    if(player_symbol == start_smybol) {
        print_field_options();
        player_move();
        pc_move();
        draw_field();
    } else {
        pc_move();
        draw_field();
        print_field_options();
        player_move();
    }
    
}


int check_end_of_game() {
    char winner = 'n';
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

    if(winner == player_symbol) {
        printf("Player won!\n");
        return 0;
    }
    else if(winner == pc_symbol) {
        printf("PC won!\n");
        return 0;
    }

    return 1;
}