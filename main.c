#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "main.h"

int randint(int a, int b){ //Cette fonction nous renvoie un entier aleatoire entre a compris et b compris.
	return a + rand()%(b-a+1);
}

void init_lab(struct maze lab[MAX][MAX], int n, int m){
	for(int x=0; x<n; ++x){
		for(int y=0; y<m; ++y){
			lab[x][y].N=1;
			lab[x][y].S=1;
			lab[x][y].W=1;
			lab[x][y].E=1;
			lab[x][y].backtracking_visiter=0;
			lab[x][y].resolution_visiter=0;
			lab[x][y].distance=-1;
			lab[x][y].solution=0;
		}
	}
}

void affiche_lab(struct maze lab[MAX][MAX], int n, int m){
	for(int x=0; x<n; ++x){
		for(int y=0; y<m; ++y){
			if(lab[x][y].N==1){
				printf("##");
			}else{
				if (x>0 && lab[x-1][y].solution==1 && lab[x][y].solution==1){
					printf("#o");	
				}else{
					printf("#.");
				}
			}
		}
		printf("#\n");
		
		for(int y=0; y<m; ++y){
			if(lab[x][y].W==1){
				if(lab[x][y].solution==1){
					printf("#o");
				}else{
					printf("#.");
				}
			}else{
				if(lab[x][y].solution==1){
					if (y>0 && lab[x][y-1].solution==1){
						printf("oo");
					}else{
						printf(".o");
					}
				}else{
					printf("..");
				}
			}
		}
		printf("#\n");
	}
	for(int y=0; y<m; ++y){
		printf("##");
	}
	printf("#\n");
}

void creuse(struct maze lab[MAX][MAX], int x1, int y1, int x2, int y2){
	if(x2==x1-1 && y2==y1){
		lab[x1][y1].N=0;
		lab[x2][y2].S=0;
	}
	if(x2==x1+1 && y2==y1){
		lab[x1][y1].S=0;
		lab[x2][y2].N=0;
	}
   if(x2==x1 && y2==y1-1){
		lab[x1][y1].W=0;
		lab[x2][y2].E=0;
	}
	if(x2==x1 && y2==y1+1){
		lab[x1][y1].E=0;
		lab[x2][y2].W=0;
	}
}

int candidat_visite(struct maze lab[MAX][MAX], int n, int m, int x, int y, int xcandidat[4], int ycandidat[4]){
	int nombre_candidat = 0;
	if(x>0 && lab[x-1][y].backtracking_visiter==0){
		xcandidat[nombre_candidat] = x-1;
		ycandidat[nombre_candidat] = y;
		++nombre_candidat;
	} 
	if(x<n-1 && lab[x+1][y].backtracking_visiter==0){
		xcandidat[nombre_candidat] = x+1;
		ycandidat[nombre_candidat] = y;
		++nombre_candidat;
	}
	if(y>0 && lab[x][y-1].backtracking_visiter==0){
		xcandidat[nombre_candidat] = x;
		ycandidat[nombre_candidat] = y-1;
		++nombre_candidat;
	}
	if(y<m-1 && lab[x][y+1].backtracking_visiter==0){
		xcandidat[nombre_candidat] = x;
		ycandidat[nombre_candidat] = y+1;
		++nombre_candidat;
	}
	return nombre_candidat;
}

int candidat_chemin(struct maze lab[MAX][MAX], int n, int m, int x, int y, int xcandidat[4], int ycandidat[4]){
	int nombre_candidat = 0;
	if(x>0 && lab[x][y].N == 0){
		xcandidat[nombre_candidat] = x-1;
		ycandidat[nombre_candidat] = y;
		++nombre_candidat;
	} 
	if(x<n-1 && lab[x][y].S == 0){
		xcandidat[nombre_candidat] = x+1;
		ycandidat[nombre_candidat] = y;
		++nombre_candidat;
	}
	if(y>0 && lab[x][y].W == 0){
		xcandidat[nombre_candidat] = x;
		ycandidat[nombre_candidat] = y-1;
		++nombre_candidat;
	}
	if(y<m-1 && lab[x][y].E == 0){
		xcandidat[nombre_candidat] = x;
		ycandidat[nombre_candidat] = y+1;
		++nombre_candidat;
	}
	return nombre_candidat;
}

int candidat_visite_chemin(struct maze lab[MAX][MAX], int n, int m, int x, int y, int xcandidat[4], int ycandidat[4]){
	int nombre_candidat = 0;
	if(x>0 && lab[x-1][y].resolution_visiter == 0 && lab[x][y].N == 0){
		xcandidat[nombre_candidat] = x-1;
		ycandidat[nombre_candidat] = y;
		++nombre_candidat;
	} 
	if(x<n-1 && lab[x+1][y].resolution_visiter == 0 && lab[x][y].S == 0){
		xcandidat[nombre_candidat] = x+1;
		ycandidat[nombre_candidat] = y;
		++nombre_candidat;
	}
	if(y>0 && lab[x][y-1].resolution_visiter == 0 && lab[x][y].W == 0){
		xcandidat[nombre_candidat] = x;
		ycandidat[nombre_candidat] = y-1;
		++nombre_candidat;
	}
	if(y<m-1 && lab[x][y+1].resolution_visiter == 0 && lab[x][y].E == 0){
		xcandidat[nombre_candidat] = x;
		ycandidat[nombre_candidat] = y+1;
		++nombre_candidat;
	}
	return nombre_candidat;
}

void backtracking(struct maze lab[MAX][MAX], int n, int m, int xdepart, int ydepart){
	lab[xdepart][ydepart].backtracking_visiter = 1;
	int xcandidat[4], ycandidat[4];
	int nombre_candidat = candidat_visite(lab, n, m, xdepart, ydepart, xcandidat, ycandidat);
	while(nombre_candidat != 0){
		int candidat_au_hasard = randint(0, nombre_candidat-1);
		creuse(lab, xdepart, ydepart, xcandidat[candidat_au_hasard], ycandidat[candidat_au_hasard]);
		backtracking(lab, n, m, xcandidat[candidat_au_hasard], ycandidat[candidat_au_hasard]);
		nombre_candidat = candidat_visite(lab, n, m, xdepart, ydepart, xcandidat, ycandidat);
	}
}

void backtracking_sans_boucle(struct maze lab[MAX][MAX], int n, int m, int xdepart, int ydepart){
	lab[xdepart][ydepart].backtracking_visiter = 1;
	int xcandidat[4], ycandidat[4];
	int nombre_candidat = candidat_visite(lab, n, m, xdepart, ydepart, xcandidat, ycandidat);
	if(nombre_candidat != 0){
		int candidat_au_hasard = randint(0, nombre_candidat-1);
		creuse(lab, xdepart, ydepart, xcandidat[candidat_au_hasard], ycandidat[candidat_au_hasard]);
		backtracking(lab, n, m, xcandidat[candidat_au_hasard], ycandidat[candidat_au_hasard]);
		nombre_candidat = candidat_visite(lab, n, m, xdepart, ydepart, xcandidat, ycandidat);
		if(nombre_candidat != 0){
			int candidat_au_hasard = randint(0, nombre_candidat-1);
			creuse(lab, xdepart, ydepart, xcandidat[candidat_au_hasard], ycandidat[candidat_au_hasard]);
			backtracking(lab, n, m, xcandidat[candidat_au_hasard], ycandidat[candidat_au_hasard]);
			nombre_candidat = candidat_visite(lab, n, m, xdepart, ydepart, xcandidat, ycandidat);
			if(nombre_candidat != 0){
				int candidat_au_hasard = randint(0, nombre_candidat-1);
				creuse(lab, xdepart, ydepart, xcandidat[candidat_au_hasard], ycandidat[candidat_au_hasard]);
				backtracking(lab, n, m, xcandidat[candidat_au_hasard], ycandidat[candidat_au_hasard]);
				nombre_candidat = candidat_visite(lab, n, m, xdepart, ydepart, xcandidat, ycandidat);
				if(nombre_candidat != 0){
					int candidat_au_hasard = randint(0, nombre_candidat-1);
					creuse(lab, xdepart, ydepart, xcandidat[candidat_au_hasard], ycandidat[candidat_au_hasard]);
					backtracking(lab, n, m, xcandidat[candidat_au_hasard], ycandidat[candidat_au_hasard]);
					nombre_candidat = candidat_visite(lab, n, m, xdepart, ydepart, xcandidat, ycandidat);
				}
			}
		}
	}
}

void division(struct maze lab[MAX][MAX], int nmin, int mmin, int nmax, int mmax){
	if(nmin != nmax || mmin != mmax){
		int RD = randint(1,nmax-nmin+mmax-mmin);
		if(RD <= nmax-nmin){
			int nnew = randint(nmin,nmax-1);
			int colonne_creuse = randint(mmin,mmax);
			creuse(lab, nnew, colonne_creuse, nnew+1, colonne_creuse);
			division(lab, nmin, mmin, nnew, mmax);
			division(lab, nnew+1, mmin, nmax, mmax);
			
		}else{
			int mnew = randint(mmin,mmax-1);
			int ligne_creuse = randint(nmin,nmax);
			creuse(lab, ligne_creuse, mnew, ligne_creuse, mnew+1);
			division(lab, nmin, mmin, nmax, mnew);
			division(lab, nmin, mnew+1, nmax, mmax);
		}
	}
}

//initialise la distance
void init_lab_distance(struct maze lab[MAX][MAX], int n, int m ,int x0, int y0, int xfin, int yfin, int p){
	if(lab[x0][y0].distance>p || lab[x0][y0].distance==-1){
		lab[x0][y0].distance=p;
		if(x0 != xfin || y0 != yfin){
			int xcandidat[4], ycandidat[4];
			int nombre_candidat = candidat_chemin(lab, n, m, x0, y0, xcandidat, ycandidat);
			for(int i=0;i<nombre_candidat;++i){
				init_lab_distance(lab, n, m, xcandidat[i], ycandidat[i], xfin, yfin, p+1);
			}
		}
	}
}

void trouve_chemin_solution(struct maze lab[MAX][MAX], int n, int m, int x, int y){
	lab[x][y].solution=1;
	if(lab[x][y].distance > 0){
		int xcandidat[4], ycandidat[4];
		int nombre_candidat=candidat_chemin(lab, n, m, x, y, xcandidat, ycandidat);
		for(int i=0;i<nombre_candidat;++i){
			if((lab[xcandidat[i]][ycandidat[i]]).distance == lab[x][y].distance-1){
				trouve_chemin_solution(lab, n, m, xcandidat[i], ycandidat[i]);
			}
		}
	}
}


int resolution_backtracking(struct maze lab[MAX][MAX], int n, int m, int x0, int y0, int xfin, int yfin){
	lab[x0][y0].resolution_visiter = 1;
	int xcandidat[4], ycandidat[4];
	int nombre_candidat = candidat_visite_chemin(lab, n, m, x0, y0, xcandidat, ycandidat);
	if((nombre_candidat == 0) || (x0 == xfin && y0 == yfin)){
		if(x0 == xfin && y0 == yfin){
			lab[x0][y0].solution = 1;
			return 1;
		}else{
			return 0;
		}
	}else{	
		for(int i = 0; i<nombre_candidat; ++i){
			if(resolution_backtracking(lab,n,m,xcandidat[i],ycandidat[i],xfin,yfin)==1){
				lab[x0][y0].solution = 1;
				return 1;
			}
		}
		return 0;
	}
}

int main(){
	int n = 5, m = 5, choix, choix1;
	srand(time(NULL));
	struct maze lab[MAX][MAX];
	init_lab(lab,n,m);
	
	printf("Choisissez une option de génération de labyrinthe:\n");
    printf("1. Backtracking\n");
    printf("2. Division\n");
    
    printf("Entrez votre choix (1 ou 2) : ");
    scanf("%d", &choix);
    
    printf("Choisissez une option de résolution de labyrinthe:\n");
    printf("1. Backtracking\n");
    printf("2. Dijkstra\n");
    
    printf("Entrez votre choix (1 ou 2) : ");
    scanf("%d", &choix1);
    
    if (choix == 1 && choix1 == 1) {
        clock_t Gen1 = clock();
        backtracking_sans_boucle(lab,n, m, 0,0);
        //backtracking(lab,n,m,0,0);
        clock_t Gen2 = clock();
        double sec = ((double) (Gen2 - Gen1))/ CLOCKS_PER_SEC ;
        printf("Labyrinthe généré avec la méthode de Backtracking fait en %f sec: \n", sec);
        affiche_lab(lab,n,m);
        
        clock_t Res1 = clock();
        int solution_trouvee = resolution_backtracking(lab, n, m, 0, 0, n-1, m-1);
		clock_t Res2 = clock();
		double sec1 = ((double) (Res2 - Res1))/ CLOCKS_PER_SEC;
        printf("Labyrinthe généré avec la méthode de Backtracking fait en %f sec: \n", sec1);
        if (solution_trouvee) {
        // Afficher la solution si elle a été trouvée
			affiche_lab(lab,n,m);
		} else {
			printf("Aucune solution n'a été trouvée.\n");
		}
	
    } else if (choix == 2 && choix1 == 2) {
        clock_t Gen1 = clock();
        division(lab,0,0,n-1,m-1);
        clock_t Gen2 = clock();
        double sec = ((double) (Gen2 - Gen1)/ CLOCKS_PER_SEC);
        printf("\n Labyrinthe généré avec la méthode de Division fait en %f sec: \n", sec);
        affiche_lab(lab,n,m);
        
        clock_t Res1 = clock();
        init_lab_distance(lab, n, m , 0, 0, n-1, m-1, 0);
		trouve_chemin_solution(lab, n, m, n-1, m-1);
        clock_t Res2 = clock();
        double sec1 = ((double) (Res2 - Res1)/ CLOCKS_PER_SEC);
        printf("Labyrinthe résolu avec la méthode de Dijkstra fait en %f sec: \n", sec1);
        affiche_lab(lab,n,m);
        
    } else if (choix == 1 && choix1 == 2) {
		clock_t Gen1 = clock();
		backtracking_sans_boucle(lab,n, m, 0,0);
        //backtracking(lab,n,m,0,0);
        clock_t Gen2 = clock();
        double sec = ((double) (Gen2 - Gen1)/ CLOCKS_PER_SEC);
        printf("Labyrinthe généré avec la méthode de Backtracking fait en %f sec: \n", sec);
        affiche_lab(lab,n,m);
        
        clock_t Res1 = clock();
        init_lab_distance(lab, n, m,0, 0, n-1, m-1, 0);
        trouve_chemin_solution(lab, n, m, n-1, m-1);
        clock_t Res2 = clock();
        double sec1 = ((double) (Res2 - Res1)/ CLOCKS_PER_SEC);
        printf("Labyrinthe résolu avec la méthode de Dijkstra fait en %f sec: \n", sec1);
        affiche_lab(lab,n,m);
        
    } else if (choix == 2 && choix1 == 1) {
		clock_t Gen1 = clock();
        division(lab,0,0,n-1,m-1);
        clock_t Gen2 = clock();
        double sec = ((double) (Gen2 - Gen1)/ CLOCKS_PER_SEC);
        printf("\n Labyrinthe généré avec la méthode de Division fait en %f sec: \n", sec);
        affiche_lab(lab,n,m);
        
        clock_t Res1 = clock();
        int solution_trouvee = resolution_backtracking(lab, n, m, 0, 0, n-1, m-1);
        if (solution_trouvee) {
        // Afficher la solution si elle a été trouvée
			affiche_lab(lab,n,m);
			clock_t Res2 = clock();
			double sec1 = ((double) (Res2 - Res1)/ CLOCKS_PER_SEC);
        printf("Labyrinthe résolu avec la méthode de Backtracking fait en %f sec: \n", sec1);
		} else {
			printf("Aucune solution n'a été trouvée.\n");
		}
        
    }
    
    
	
	return EXIT_SUCCESS;
}
