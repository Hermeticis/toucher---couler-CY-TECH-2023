#include "head.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


/**
 * @brief Performs a shot on the opponent's board based on the player's ID.
 *
 * This function performs a shot on the opponent's board, updating the matrix accordingly.
 * If the player is human (ID 0), it prompts the user to input the row and column to shoot.
 * If the player is a bot (ID 1), it randomly selects a non-hit case to shoot.
 * After the shot, the function checks if the coordinates are valid and updates the case content accordingly.
 * 'D' represents a hit on a boat part, '*' represents a hit on water, and 'tire ligne x, colonne y' is printed to indicate the shot.
 *
 * @param plateau Pointer to the array of boards.
 * @param id_joueur Player ID (0 for human, 1 for bot).
 * @param taille Size of each dimension of the matrix.
 */

void tire(Board* plateau,int id_joueur,int taille) {
    Board sea = plateau[(id_joueur+1)%2];
    char** matrice = sea.matrix;
    int ligne = -1;
    int colonne = -1;
    if(id_joueur==0)
    {
         ligne =obtenirEntierDansPlage('L',taille-1);
         colonne =obtenirEntierDansPlage('C',taille-1);
    }
    else
    {

        int tmp = 1;
        while(tmp == 1){
             ligne = rdm_number(0,taille-1);
             colonne = rdm_number(0,taille-1);
            tmp  = case_deja_toucher(matrice,ligne,colonne);
        }
    }
    if (ligne >= 0 && ligne < taille && colonne >= 0 && colonne < taille) {
        printf("tire ligne %d , colonne %d",ligne,colonne);
        if (matrice[ligne][colonne] == 'B') { // the case containt a boat part
            matrice[ligne][colonne] = 'D';
        } else if (matrice[ligne][colonne] == 'w') { // the case is a water case 
            matrice[ligne][colonne] = '*';
        }
    }
    else{
    
        printf("Coordonnées non valides.\n");
    }
}

/**
 * @brief Displays the current turn information for a player.
 *
 * This function displays the information for the current turn of a player.
 * If the player is human (ID 0), it shows the opponent's vision of the board and the player's own board.
 * If the player is a bot (ID 1), it only shows the opponent's vision of the board.
 *
 * @param plateau Pointer to the array of boards.
 * @param id_joueur Player ID (0 for human, 1 for bot).
 */

void affichage_tour(Board* plateau,int id_joueur){

    if(plateau==NULL){
        exit(1);
    }

    if (id_joueur == 0)
    {
        afficherMatriceOpposant(plateau,id_joueur);
        affiche_joueur(plateau,id_joueur);
    }
    
}

/**
 * @brief Executes a player's turn, updating the game state.
 *
 * This function executes a player's turn, updating the game state based on their actions.
 * It begins by printing the start of the player's or bot's turn.
 * It then checks if the game has ended, displaying the outcome and returning 1 if true.
 * Next, it displays the player's board and the opponent's vision of the board.
 * The player or bot then performs a shot using the function `tire`.
 * Finally, it prints the end of the turn and returns 0.
 *
 * @param plateau Pointer to the array of boards.
 * @param id_joueur Player ID (0 for human, 1 for bot).
 * @return Returns 1 if the game has ended, otherwise returns 0.
 */

int tour(Board* plateau,int id_joueur){
    
    Board sea = plateau[id_joueur];
    if(id_joueur==0)
    {
        printf("Debut tour joueur\n");
    }
    else
    {
        printf("Debut tour BOT\n");
    }
    if(verifierFinpPartie(sea.matrix,sea.lenght)){// check if the game is over 
        printf("fin de jeu\n");
        if (id_joueur==1)
        {
            printf("vous avez Gagner \n");
            return 1;
        }
        printf("vous avez perdu\n");
        return 1;
    }
    affichage_tour(plateau,id_joueur); // print player board and the RADAR 
    tire(plateau,id_joueur,sea.lenght);// shoot !! 
    if(id_joueur==0)
    {
        printf("FIN tour joueur\n");
    }
    else
    {
        printf("FIN tour BOT\n");
    }
    return 0;
}


/**
 * @brief Checks if a case on the opponent's board has already been hit.
 *
 * This function checks if a specific case on the opponent's board has already been hit.
 * If the case contains 'D' (hit on a boat part) or '*' (hit on water), it returns 1 (true).
 * Otherwise, it returns 0 (false).
 *
 * @param sea Pointer to the oppzonent's board matrix.
 * @param a Row index of the case.
 * @param b Column index of the case.
 * @return Returns 1 if the case has already been hit, otherwise returns 0.
 */


int case_deja_toucher(char**sea,int a,int b){ 
    if(sea==NULL){ exit(1);}
    if(sea[a][b]=='D'||sea[a][b]=='*'){
        return 1;
    }
    return 0;
}










