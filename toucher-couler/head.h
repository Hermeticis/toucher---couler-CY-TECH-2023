#ifndef HEAD_H  
#define HEAD_H
//enum
enum water_state {water,shooted_water,boat_part,wreck};

/**
 * @brief Structure representing a boat.
 */
typedef struct boat Boat ; // boat structure 
struct boat{
    short int lenght;  /**< Length of the boat. */
    int head_position[2];  /**< Coordinates of the boat part at the top left. */
    int orientation;  /**< Orientation of the boat (1 for vertical, 0 for horizontal). */
};

/**
 * @brief Structure representing a game board.
 */
typedef struct board Board ;
struct board{
    int lenght;
    char** matrix;
};

// function PROTOTYPE

// common.c
int estNull(void* ptr);
int rdm_number(int a, int b) ;
int verifJoueur(int a);
void affiche_joueur(Board* plateau, int joueur_id);
void check_pointer(void* c,int msg,int boat_length, int orientation, int a, int b);
int obtenirEntierDansPlage(char c, int N);

//matrix.c 
void afficherMatriceCaracteres(char** matrice, int taille);
Board createBoard(int lenght);
char** alloce_matrix(int lenght);
Board* init_game(int taille);
void loadMatrix(char** matrice, int taille); 
void end_game(Board* jeu);
void FreeBoard(Board* structure);
void FreeMatrix(char** matrix, int lenght);
void afficherMatriceOpposant(Board* plateau,int id_joueur);
int verifierFinpPartie(char **matrice, int taille);

//jeu.c
void tire(Board* plateau,int id_joueur,int taille);
void affichage_tour(Board* plateau,int id_joueur);
int tour(Board* plateau,int id_joueur);
int case_deja_toucher(char**sea,int a,int b);

//boat.c
void load_boat_park(Boat* boat_park,int boat_park_length, Board* plateau,int id_joueur);
void libererTableauBoats(Boat* tableau);
Boat* allouerTableauBoats(int N);
int case_occuper(char**sea,int a,int b);
int test_placement_boat(Board* plateau, int id_joueur, int length, int boat_length, int orientation, int a, int b);
int test_boat_limit(int lenght, int boat_length, int orientation, int a, int b);
int placement_boat(Board* plateau,int id_joueur, int lenght,int boat_lenght,int orientation, int a,int b);
Boat newBoat(short int l ,int x, int y, int o);
void remplacer( Board* plateau,int id_joueur, int N);
void matriceCleanO(Board* plateau,int id_joueur, int N);


#endif



