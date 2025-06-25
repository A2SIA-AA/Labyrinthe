#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 100


struct maze{//cette structure permet de definir toutes les composantes d'une case de labyrinthe.
    int N;//= 1 si le mur en haut de la case donnee est ferme, 0 sinon.	
    int S; //= 1 si le mur en bas de la case donnee est ferme, 0 sinon.   
    int W;//= 1 si le mur en haut de la case donnee est ferme, 0 sinon.
    int E; //= 1 si le mur a droite de la case donnee est ferme, 0 sinon.   
    int backtracking_visiter;
    int resolution_visiter;
    int distance; //on appelera distance d'une case, la distance (en nombre de case+1) minimal qui relie la case d'une certaine case init_labiale choisie en amont en respectant les regles du labyrinthe, cette donnee nous seras utile pour trouve le chemin le plus court.	
    int solution;//=1 si la cellule fait partie d'un des chemins les plus courts pour relier une cellule init_labial choisie avec une cellule finale choisie.
 };


int randint(int,int);

void init_lab(struct maze lab[MAX][MAX], int, int);

void affiche_lab(struct maze lab[MAX][MAX], int, int);

void creuse(struct maze lab[MAX][MAX], int, int, int, int);

int candidat_visite(struct maze lab[MAX][MAX], int, int, int, int, int xcandidat[4], int ycandidat[4]);

int candidat_chemin(struct maze lab[MAX][MAX], int, int, int, int, int xcandidat[4], int ycandidat[4]);

int candidat_visite_chemin(struct maze lab[MAX][MAX], int, int, int, int, int xcandidat[4], int ycandidat[4]);

void Backtracking(struct maze lab[MAX][MAX], int, int, int, int);

void backtracking_sans_boucle(struct maze lab[MAX][MAX], int , int, int , int);

void Division(struct maze lab[MAX][MAX], int, int, int, int);

void init_lab_distance(struct maze lab[MAX][MAX], int , int ,int , int , int , int , int );

void trouve_chemin_solution(struct maze lab[MAX][MAX], int, int, int, int);

int resolution_backtracking(struct maze lab[MAX][MAX], int, int, int, int, int, int);
