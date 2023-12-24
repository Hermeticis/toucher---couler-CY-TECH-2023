#include "head.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Handles the end of the game by freeing memory.
 *
 * This function handles the end of the game by freeing memory associated with the provided array of boards.
 * It checks if the input pointer `jeu` is NULL and returns early if true.
 * It then prints a message indicating the end of the game and proceeds to free the memory of both boards.
 *
 * @param jeu Pointer to the array of boards.
 */

void end_game(Board* jeu) {
    if (estNull(jeu)) {
        return;
    }
    printf("End_Game\n");
    FreeBoard(&jeu[0]);
    FreeBoard(&jeu[1]);
    free(jeu);
}

/**
 * @brief Initializes a game with dynamic memory allocation.
 *
 * This function initializes a game by dynamically allocating memory for an array of two boards.
 * It prints a message indicating the start of the game initialization.
 * If the memory allocation fails, an error message is printed, and the program exits with a failure code.
 * Two boards are then created for each player using the function `createBoard`.
 * Finally, messages are printed to indicate the end of the game initialization and the start of playing.
 *
 * @param taille Size of the game board.
 * @return Pointer to the array of boards.
 */

Board* init_game(int taille) { 
    printf("game init start\n");
    Board* jeu = (Board*)malloc(2 * sizeof(Board));

    if (estNull(jeu)) {
        fprintf(stderr, "Échec de l'allocation de mémoire pour le tableau de structures.\n");
        exit(EXIT_FAILURE);
    }

    jeu[0] = createBoard(taille);
    jeu[1] = createBoard(taille);
    printf("               game init end\n\n\n");
    printf("               start playing\n\n");
    return jeu;
}

/**
 * @brief Initializes a 2D character matrix with a specified value.
 *
 * This function initializes a 2D character matrix with the value 'w' (representing 'water').
 * The size of the matrix is determined by the parameter `taille`.
 *
 * @param matrice Pointer to the 2D character matrix.
 * @param taille Size of the matrix.
 */

void loadMatrix(char** matrice, int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            matrice[i][j] = 'w';
        }
    }
}


/**
 * @brief Allocates memory for a 2D character matrix and initializes it.
 *
 * This function dynamically allocates memory for a 2D character matrix of size `lenght x lenght`.
 * If the memory allocation fails, an error message is printed, and the program exits with a failure code.
 * It then allocates memory for each column of the matrix and initializes the entire matrix using the function `loadMatrix`.
 *
 * @param lenght Size of each dimension of the square matrix.
 * @return Pointer to the allocated 2D character matrix.
 */

char** alloce_matrix(int lenght) {
    char** matrix = (char**)malloc(lenght * sizeof(char*));

    if (matrix == NULL) {
        fprintf(stderr, "Échec de l'allocation de mémoire pour la matrice.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < lenght; i++) {
        matrix[i] = (char*)malloc(lenght * sizeof(char));

        if (matrix[i] == NULL) {
            fprintf(stderr, "Échec de l'allocation de mémoire pour les colonnes de la matrice.\n");

            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);

            exit(EXIT_FAILURE);
        }
    }
    loadMatrix(matrix,lenght);

    return matrix;
}

/**
 * @brief Creates a board with a water-filled matrix.
 *
 * This function creates a Board structure with a square matrix of size `lenght x lenght`,
 * where each element is initialized to 'w' (representing 'water').
 * If the specified length is less than 5, the program exits with an error code.
 *
 * @param lenght Size of each dimension of the square matrix.
 * @return The created Board instance.
 */

Board createBoard(int lenght) {
    if(lenght >=5){
    Board instance;
    instance.lenght = lenght;
    instance.matrix = alloce_matrix(lenght); 
    afficherMatriceCaracteres(instance.matrix,lenght); 
    return instance;
    }
    else{
        exit(1);
    };
    
}

/**
 * @brief Frees the memory allocated for a 2D character matrix.
 *
 * This function frees the memory allocated for a 2D character matrix of size `lenght x lenght`.
 * It iterates over each column and then frees the memory for the rows before freeing the overall matrix.
 *
 * @param matrix Pointer to the 2D character matrix.
 * @param lenght Size of each dimension of the matrix.
 */



void FreeMatrix(char** matrix, int lenght) {
    
    for (int i = 0; i < lenght; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/**
 * @brief Frees the memory allocated for a Board structure.
 *
 * This function frees the memory allocated for the matrix within a Board structure.
 * If the input pointer `structure` is NULL, the function returns early.
 * Otherwise, it calls the function `FreeMatrix` to free the memory of the matrix.
 *
 * @param structure Pointer to the Board structure.
 */


void FreeBoard(Board* structure) {
    if (structure==NULL) {
        return;
    }
    FreeMatrix(structure->matrix, structure->lenght);
}


/**
 * @brief Displays a matrix of characters along with row and column indices.
 *
 * This function prints a matrix of characters along with row and column indices.
 * The indices of the first row (X-axis) are displayed above the matrix,
 * and the indices of the first column (Y-axis) are displayed to the left of each row.
 *
 * @param matrice Pointer to the 2D character matrix.
 * @param taille Size of each dimension of the matrix.
 */

void afficherMatriceCaracteres(char** matrice, int taille) {
    
    printf("   ");
    for (int i = 0; i < taille; i++) {
        printf("%3d", i);
    }
    printf("\n");

    
    for (int i = 0; i < taille; i++) {
        printf("%3d", i); 
        for (int j = 0; j < taille; j++) {
            printf("%3c", matrice[i][j]);  
        }
        printf("\n");
    }
    printf("\n\n");
}


/**
 * @brief Checks if the game has ended by verifying the absence of 'B' in the matrix.
 *
 * This function iterates through each element of the character matrix.
 * If it finds any element equal to 'B', it returns 0 (false) indicating that the game has not ended.
 * If no element is equal to 'B', it returns 1 (true) indicating that the game has ended.
 *
 * @param matrice Pointer to the 2D character matrix.
 * @param taille Size of each dimension of the matrix.
 * @return Returns 1 if the game has ended (no 'B' in the matrix), otherwise returns 0.
 */


int verifierFinpPartie(char **matrice, int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (matrice[i][j] == 'B') {
                return 0;
            }
        }
    }
    return 1;
}


/**
 * @brief Displays the opponent's vision of the board with hidden information.
 *
 * This function prints the opponent's vision of the board, hiding certain information.
 * It displays indices of the first row (X-axis) and the first column (Y-axis).
 * The opponent's board is obtained based on the provided player ID (`id_joueur`).
 * If the player is human (ID 0), it displays "-----VISION PLAYER-----".
 * If the player is a bot (ID 1), it displays "-----VISION BOT-----".
 * The function hides 'B' and 'w' elements, replacing them with dots ('.') for a concealed view.
 *
 * @param plateau Pointer to the array of boards.
 * @param id_joueur Player ID (0 for human, 1 for bot).
 */


void afficherMatriceOpposant(Board* plateau,int id_joueur) {
    
    if(plateau==NULL){
        exit(1);
    }
    Board side = plateau[(id_joueur+1)%2];
    if(id_joueur==0){
        printf("-----VISION PLAYER-----\n");
    }
    else{
        printf("-----VISION BOT-----\n");
    }


    int taille = side.lenght;
    char** matrice = side.matrix;
    printf("   ");
    for (int i = 0; i < taille; i++) {
        printf("%3d", i);
    }
    printf("\n");
   
    for (int i = 0; i < taille; i++) {
        printf("%3d", i);  
        for (int j = 0; j < taille; j++) {
            if(matrice[i][j]=='B'|| matrice[i][j]== 'w'){
                printf("  .");
            }
            else{
                printf("%3c", matrice[i][j]); 
            }
            
        }
        printf("\n");
    }
    printf("\n\n");
}