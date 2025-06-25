# Projet MIPP — Simulation de Labyrinthes en C

> Génération et résolution de **labyrinthes parfaits** (connexes et acycliques) à l’aide de  
> deux algorithmes de génération (Backtracking, Division récursive) et deux algorithmes de  
> résolution (Backtracking, Dijkstra).

- **Auteurs :** Doubli Hoda & Ait Taleb Assia (GM3)  
- **Encadrant :** M. Julien Saunier  
- **Date :** novembre 2023  

---

## 1 . Présentation

Un labyrinthe est modélisé comme un graphe non orienté ; lorsqu’il est parfait, son graphe
est un **arbre**.  
Le projet montre :

| Étape | Algorithme | Rôle |
|-------|------------|------|
| Génération | Backtracking | Creuse récursivement en profondeur sans revisiter de cellule |
| Génération | Division récursive | « Divide & Conquer » : coupe la grille puis relie les sous-grilles |
| Résolution | Backtracking | Trouve _un_ chemin de l’entrée à la sortie |
| Résolution | Dijkstra | Trouve _le plus court_ chemin (coût uniforme = 1) |

*(Dans un labyrinthe parfait, « un » chemin == « le plus court » ; Backtracking est donc
souvent plus rapide.)*

---

## 2 . Structure du code

```

src/
├── maze.h / maze.c          # structure Maze et helpers (creuse, candidats…)
├── gen\_backtracking.c       # génération Backtracking
├── gen\_division.c           # génération Division récursive
├── solve\_backtracking.c     # résolution Backtracking
├── solve\_dijkstra.c         # résolution Dijkstra
└── main.c                   # CLI : choisir algorithme, tailles, affichage

Makefile                     # compilation + tests + clean
rapport.pdf                  # compte-rendu détaillé (ce document)

````

La structure `Maze` mémorise :

```c
typedef struct {
    int N, S, W, E;          // murs (1 = fermé, 0 = ouvert)
    int back_visite;         // génération Backtracking
    int solve_visite;        // résolution Backtracking
    int distance;            // distance Dijkstra (-1 si inconnue)
    int solution;            // =1 si appartient au chemin solution
} Maze;
````

---

## 3 . Compilation & exécution

### 3.1 . Pré-requis

| Outil | Version testée |
| ----- | -------------- |
| GCC   | ≥ 11 (C 17)    |
| make  | GNU Make       |

### 3.2 . Build rapide

```bash
# À la racine du projet
make            # compile exécutable + éventuels tests
./bin/labyrinth # lance le programme (voir options)
```

* `make clean` supprime les objets et binaires.
* Les **tests unitaires** se trouvent sous `Tests/`; exécutez‐les avec `make tests`.

---

## 4 . Utilisation

Au lancement, la CLI demande :

1. Taille du labyrinthe (n lignes, m colonnes).
2. Algorithme de **génération** (Backtracking ou Division).
3. Algorithme de **résolution** (Backtracking ou Dijkstra).

Le programme affiche ensuite :

* Le labyrinthe généré (# = mur, . = passage).
* Le même labyrinthe avec le **chemin solution** annoté par `o`.
* Les temps d’exécution (génération & résolution).

---

## 5 . Performances observées

| Taille  | Génération Backtracking | Génération Division | Résolution Backtracking | Résolution Dijkstra |
| ------- | ----------------------- | ------------------- | ----------------------- | ------------------- |
| 20 × 20 | 0,00019 s               | ≈ 0 s               | 0,00006 s               | 0,00015 s           |
| 30 × 40 | 0,00038 s               | 0,00023 s           | 0,00018 s               | 0,00033 s           |

*Backtracking est plus lent à générer mais plus rapide à résoudre ; Division donne
des couloirs plus rectilignes.*

---

## 6 . Sources et inspirations

* Articles sur les **algorithmes de génération de labyrinthes** (division récursive, depth-first search).
* Cours et slides sur la **récursivité** et la **théorie des graphes**.
* Documentation officielle de l’**algorithme de Dijkstra**.
