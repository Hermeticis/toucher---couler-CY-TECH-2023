#include "head.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * @brief Checks if a pointer is NULL.
 *
 * This function takes a pointer as a parameter and returns 1 if the pointer is NULL, and 0 otherwise.
 *
 * @param ptr The pointer to check.
 * @return Returns 1 if the pointer is NULL, and 0 otherwise.
 */

int estNull(void* ptr) {
    // is the pointer NULL ?
    return ptr == NULL;
}



/**
 * @brief Checks if a pointer is NULL and displays an error message if needed.
 *
 * This function takes a pointer, a message, the length of a boat, its orientation, and its coordinates,
 * and displays an error message with the provided details if the pointer is NULL. In case of an error, the program exits.
 *
 * @param c The pointer to check.
 * @param msg The error message associated.
 * @param boat_length The length of the boat.
 * @param orientation The orientation of the boat.
 * @param a The first coordinate of the boat.
 * @param b The second coordinate of the boat.
 */
void check_pointer(void* c,int msg,int boat_length, int orientation, int a, int b){
 if(c==NULL){
    printf("\n\n msg : %d\n taille: %d orient: %d  coord (%d,%d)\n\n",msg,boat_length,orientation,a,b);
    exit(1);
 }
}

/**
 * @brief Generates a random number within a specified range.
 *
 * This function generates a random number between 'a' and 'b' (inclusive).
 * It initializes the seed based on the current time.
 *
 * @param a The lower bound of the range.
 * @param b The upper bound of the range.
 * @return A random number within the specified range.
 */
int rdm_number(int a, int b) {
    // init seed time based 

    // return the random number 
    return rand() % (b - a + 1) + a;   
}


/**
 * @brief Displays the board of a specific player.
 *
 * This function displays the board of a specified player identified by `joueur_id`.
 * It checks if the provided board pointer is not NULL and if the player ID is valid (0 or 1).
 * If the conditions are met, it prints the player's board using the function `afficherMatriceCaracteres`.
 * If the conditions are not met, an error message is displayed, and the program exits with an error code.
 *
 * @param plateau Pointer to the array of boards.
 * @param joueur_id ID of the player (0 or 1).
 */

void affiche_joueur(Board* plateau, int joueur_id){
    
    if(!estNull(plateau) && (joueur_id == 0 || joueur_id == 1 ))
    {

    
        printf("\n   ---Mon Plateau---\n");

        Board a = plateau[joueur_id];
        afficherMatriceCaracteres(a.matrix,a.lenght); 
    }
    else
    {
        printf("erreur d'entrée\n");
        exit(1);
    }
}

/**
 * @brief Verifies if the given integer represents a valid player ID.
 *
 * This function checks if the provided integer `a` is equal to 0 or 1,
 * indicating a valid player ID. If the condition is true, it returns 1;
 * otherwise, it returns 0.
 *
 * @param a The integer to verify as a player ID.
 * @return Returns 1 if `a` is a valid player ID (0 or 1), otherwise returns 0.
 */

int verifJoueur(int a){
    if(a==0||a==1){
        return 1;
    }
    return 0;
}

/**
 * @brief Obtains an integer within a specified range based on user input.
 *
 * This function prompts the user to input an integer within the range [0, N].
 * The character 'c' is used to specify whether the input is for a column ('C') or a row ('L').
 * It continuously prompts the user until a valid integer within the specified range is entered.
 *
 * @param c Character specifying 'C' for column or 'L' for row.
 * @param N The upper bound of the range (inclusive).
 * @return The obtained integer within the specified range.
 */

int obtenirEntierDansPlage(char c, int N) {
    int entier;

    while (1) {
        if(c=='C'){
            printf(" la coordonné Colone (entre 0 et %d) : ", N);
        }
        else if (c=='L')
        {
            printf(" la coordonné Ligne (entre 0 et %d) : ", N);
        }
        else{exit(1);}
        
        
        if (scanf("%d", &entier) != 1 || entier < 0 || entier > N) 
        {
            printf("Entrée invalide. Veuillez réessayer.\n");
                while (getchar() != '\n');  // Vider le tampon d'entrée
        } 
        
        else {
            break;
        }
    }

    return entier;
}


