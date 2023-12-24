#include "head.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//taille: 3 orient: 1  coord (3,9) error 
int main(){

    srand(time(NULL));
    int taille = 6;
    int boats_number=3;
    int id_bot = 1;
    int id_player=0;
    Board *jeu = init_game(taille);
    Boat* boats_bot= allouerTableauBoats(boats_number);
    Boat* boats_player = allouerTableauBoats(boats_number);
    load_boat_park(boats_player,boats_number,jeu,id_player);
    load_boat_park(boats_player,boats_number,jeu,id_bot);
    int victoire_tmp =0;
    int nb_tour =0;
    while(victoire_tmp== 0){
        victoire_tmp = tour(jeu,nb_tour%2);
        nb_tour ++;
    }

    end_game(jeu);
    libererTableauBoats(boats_bot);
    libererTableauBoats(boats_player);
}


