#include "head.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * @brief Allocates dynamic memory for an array of Boat structures.
 *
 * This function dynamically allocates memory for an array of Boat structures with a specified size `N`.
 * It checks if the allocation was successful, prints an error message, and exits the program with a failure code if not.
 * Additionally, it ensures that the size of the array is not greater than 6, printing an error message and exiting if true.
 *
 * @param N Size of the array of Boat structures.
 * @return Pointer to the allocated array of Boat structures.
 */

Boat* allouerTableauBoats(int N) {
    // Allocation dynamique du tableau
    if(N>6){
        printf("erreur, trop de bateau générer\n");
        exit(1);
    }
    Boat* tableau = (Boat*)malloc(N * sizeof(Boat));

    // Vérification si l'allocation a réussi
    if (tableau == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau de bateaux\n");
        exit(EXIT_FAILURE);
    }

    

    return tableau;
}

/**
 * @brief Frees the memory allocated for an array of Boat structures.
 *
 * This function frees the memory allocated for an array of Boat structures.
 *
 * @param tableau Pointer to the array of Boat structures.
 */

void libererTableauBoats(Boat* tableau) {
    free(tableau);
}


/**
 * @brief Checks if a case on the opponent's board is occupied by a boat.
 *
 * This function checks if a specific case on the opponent's board is occupied by a boat.
 * If the case contains 'B' (part of a boat) or 'O' (hit on a boat part), it returns 1 (true).
 * Otherwise, it returns 0 (false).
 *
 * @param sea Pointer to the opponent's board matrix.
 * @param a Row index of the case.
 * @param b Column index of the case.
 * @return Returns 1 if the case is occupied by a boat, otherwise returns 0.
 */

int case_occuper(char**sea,int a,int b){
    if(sea==NULL){exit(1);}
    if(sea[a][b]=='B'||sea[a][b]=='O'){
        return 1;
    }
    return 0;
}

/**
 * @brief Places a boat on the player's board based on given parameters.
 *
 * This function places a boat on the player's board based on the specified parameters.
 * It first checks if the placement is valid using the function `test_placement_boat`.
 * If the placement is valid, it updates the player's board matrix accordingly, marking the boat with 'B'.
 * The boat can be placed either horizontally or vertically based on the orientation parameter.
 *
 * @param plateau Pointer to the array of boards.
 * @param id_joueur Player ID (0 for human, 1 for bot).
 * @param length Size of each dimension of the matrix.
 * @param boat_length Length of the boat to be placed.
 * @param orientation Orientation of the boat (0 for horizontal, 1 for vertical).
 * @param a Row index for the starting point of the boat.
 * @param b Column index for the starting point of the boat.
 * @return Returns 1 if the boat is successfully placed, otherwise returns 0.
 */


int placement_boat(Board* plateau, int id_joueur, int length, int boat_length, int orientation, int a, int b) {
    if (!estNull(plateau)) {
        if(test_placement_boat(plateau,id_joueur,length,boat_length,orientation,a,b)){
        Board joueur_part = plateau[id_joueur];


        if (orientation == 1) {
            for (int i = 0; i < boat_length; i++) {
                check_pointer(joueur_part.matrix[a + i][b],1,boat_length,orientation,a,b);
                joueur_part.matrix[a + i][b] = 'B';
            }
        } else if (orientation == 0) {
            for (int i = 0; i < boat_length; i++) {
                check_pointer(joueur_part.matrix[a][b + i],2,boat_length,orientation,a,b);
                joueur_part.matrix[a][b + i] = 'B';
            }
        }
        return 1;
    }
    // printf("la place est occupé");
    return 0;
    }

    printf("Erreur d'entrée\n");
    exit(1);
}


/**
 * @brief Tests if it is possible to place a boat on the player's board.
 *
 * This function tests if it is possible to place a boat on the player's board based on the specified parameters.
 * It first checks if the boat placement is within the limits of the sea using the function `test_boat_limit`.
 * If the boat is within the limits, it checks if the designated cells are not already occupied by another boat using the function `case_occuper`.
 * The boat can be placed either horizontally or vertically based on the orientation parameter.
 *
 * @param plateau Pointer to the array of boards.
 * @param id_joueur Player ID (0 for human, 1 for bot).
 * @param length Size of each dimension of the matrix.
 * @param boat_length Length of the boat to be placed.
 * @param orientation Orientation of the boat (0 for horizontal, 1 for vertical).
 * @param a Row index for the starting point of the boat.
 * @param b Column index for the starting point of the boat.
 * @return Returns 1 if the boat can be placed, otherwise returns 0.
 */


int test_placement_boat(Board* plateau, int id_joueur, int length, int boat_length, int orientation, int a, int b) {
    // check if a boat is here. 
    if (!estNull(plateau)) {
        Board joueur_part = plateau[id_joueur];
        char** sea = joueur_part.matrix;;
        remplacer(plateau,id_joueur,length);
        if (!test_boat_limit(length,boat_length,orientation,a,b))
        {
            // printf("out of range check\n");
            return 0; // boat is out of sea's limits
        }
        
        
        if (orientation == 1) {
            for (int i = 0; i < boat_length; i++) {
                if (case_occuper(sea,a+i,b))
                {
                    return 0 ;// a boat is here
                }
            }
        } else if (orientation == 0) {
            for (int i = 0; i < boat_length; i++) {
                if (case_occuper(sea,a,b+i))
                {
                    return 0 ;// a boat is here
                }
            }
        }
        return 1; // no boat 
    }
    printf("erreur d'entrer\n");
    exit(1);
}


/**
 * @brief Tests if a boat placement is within the limits of the sea.
 *
 * This function tests if a boat placement is within the limits of the sea based on the specified parameters.
 * If the boat is placed vertically (orientation 1), it checks if the boat extends beyond the bottom of the sea.
 * If the boat is placed horizontally (orientation 0), it checks if the boat extends beyond the right side of the sea.
 * If the placement is within the limits, it returns 1; otherwise, it returns 0.
 *
 * @param lenght Size of each dimension of the matrix.
 * @param boat_length Length of the boat to be placed.
 * @param orientation Orientation of the boat (0 for horizontal, 1 for vertical).
 * @param a Row index for the starting point of the boat.
 * @param b Column index for the starting point of the boat.
 * @return Returns 1 if the boat placement is within the limits, otherwise returns 0.
 */


int test_boat_limit(int lenght, int boat_length, int orientation, int a, int b){

    if (orientation == 1) {
            if(a+boat_length>lenght){
                return 0;
            }
        } else if (orientation == 0) {
            if(b+boat_length>lenght){
                return 0;
            }
        }
    return 1;
}

/**
 * @brief Loads a random boat park onto the player's board.
 *
 * This function loads a random boat park onto the player's board.
 * It iteratively generates random boat placements until a valid placement is found for each boat in the park.
 * For each boat placed, a Boat structure is created and added to the boat park.
 * The boat park is an array of Boat structures that represents the player's fleet.
 *
 * @param boat_park Pointer to the array of Boat structures representing the boat park.
 * @param boat_park_length Length of the boat park (number of boats).
 * @param plateau Pointer to the array of boards.
 * @param id_joueur Player ID (0 for human, 1 for bot).
 */


void load_boat_park(Boat* boat_park,int boat_park_length, Board* plateau,int id_joueur){
    Board plateau_joueur = plateau[id_joueur];
    int taille_matrix = plateau_joueur.lenght;
    int cpt = 0;
    for (int i = 0; i <= boat_park_length-1; ++i){
        int tmp = 0;
        //affiche_joueur(plateau,id_joueur,taille_matrix);
        while (tmp==0){
            cpt ++;
            int orient = rdm_number(0,1);
            int x = rdm_number(0,taille_matrix-1);
            int y = rdm_number(0,taille_matrix-1);
            int  taille_boat = 2+i;
            if(taille_boat>4){
                taille_boat = 4;
            }
            tmp = placement_boat(plateau,id_joueur,taille_matrix,taille_boat,orient,x,y);
            if (tmp == 1)
            {
                 boat_park[i]=newBoat(taille_boat,x,y,orient);
                 print_caract_boat(boat_park[i]);
            }
            
        } 
        printf("\n\nnombre de tentative :%d\n",cpt);
    
       
    matriceCleanO(plateau,id_joueur,taille_matrix);
        
        

    }
}


/**
 * @brief Prints characteristics of a boat.
 *
 * This function prints the characteristics of a boat, including its length, head position, and orientation.
 *
 * @param bateau Boat structure representing the boat.
 */

void print_caract_boat(Boat bateau) {
    printf("\n\nLongueur du bateau: %d\n", bateau.lenght);
    printf("Coordonnées de la partie supérieure gauche: (%d, %d)\n", bateau.head_position[0], bateau.head_position[1]);
    printf("Orientation: %s\n", (bateau.orientation == 1) ? "Vertical" : "Horizontal");
}


/**
 * @brief Creates a new Boat structure with specified characteristics.
 *
 * This function creates and returns a new Boat structure with specified characteristics, including length, head position, and orientation.
 * It performs a validity check on the orientation parameter, ensuring it is either 1 (vertical) or 0 (horizontal).
 *
 * @param l Length of the boat.
 * @param x Row index for the head position of the boat.
 * @param y Column index for the head position of the boat.
 * @param o Orientation of the boat (1 for vertical, 0 for horizontal).
 * @return The created Boat structure.
 */

Boat newBoat(short int l ,int x, int y, int o){
    /*
    short int lenght; // boat lenght
    int head_position[2]; // coordinates of the boat part at the top left
    int orientation; // 1 or 0(vertical or horizontal
    */
   if(!(o == 1 || o==0)){
        exit(2);
   }
   Boat a;
   a.lenght = l;
   a.head_position[0] = x;
   a.head_position[1]=y;
   a.orientation = o;
   return a;
}



/**
 * @brief Replaces adjacent cells around boats with 'O' on the player's board.
 *
 * This function replaces adjacent cells around boats with 'O' on the player's board.
 * It iterates through each cell of the matrix, and if it finds a cell containing 'B' (part of a boat),
 * it replaces the adjacent cells with 'O' to indicate a hit on a boat.
 *
 * @param plateau Pointer to the array of boards.
 * @param id_joueur Player ID (0 for human, 1 for bot).
 * @param N Size of each dimension of the matrix.
 */



void remplacer( Board* plateau,int id_joueur, int N) { 
    Board sea = plateau[id_joueur];
    char** matrice  =sea.matrix;
    
    for (int i = 0; i < N; i++) 
    {


        for (int j = 0; j < N; j++) 
        {
        
            if (matrice[i][j] == 'B') 
            {
                // Parcours des cases adjacentes
                for (int x = i - 1; x <= i + 1; x++) 
                {
                    for (int y = j - 1; y <= j + 1; y++)
                     {
                        // Vérifie que la case adjacente est à l'intérieur de la matrice
                        if (x >= 0 && x < N && y >= 0 && y < N) 
                        {
                            // Remplace la case adjacente par 'w'
                            if(matrice[x][y]!='B'){matrice[x][y] = 'O';}
                            
                        }
                    }
                }
            }
        }
    }
}


/**
 * @brief Cleans the 'O' marks on the player's board.
 *
 * This function cleans the 'O' marks on the player's board, resetting them to 'w' (water).
 *
 * @param plateau Pointer to the array of boards.
 * @param id_joueur Player ID (0 for human, 1 for bot).
 * @param N Size of each dimension of the matrix.
 */

void matriceCleanO(Board* plateau,int id_joueur, int N){
    if (estNull(plateau)){exit(1);}
    Board sea = plateau[id_joueur];
    char** matrice  =sea.matrix;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            if(matrice[i][j]=='O'){
                matrice[i][j]='w';
            }
        }}
}