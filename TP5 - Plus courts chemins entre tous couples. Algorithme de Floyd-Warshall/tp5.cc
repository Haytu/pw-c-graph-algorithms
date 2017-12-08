#include <iostream>
#include <vector>
#include "villes.cc"

using namespace std;

const int n=5;
const int inf=9999;                    //La valeur infinie.    

void floyd_warshall(int longueur[][n], int dist[][n], int chemin[n][n]){

    /* Initialisation */
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(longueur[i][j] != inf){
                dist[i][j] = longueur[i][j];
                chemin[i][j] = j; /* P[][] dans le cours */
            }
            else{
                dist[i][j] = inf;
                chemin[i][j] = -1;
            }
        }
    }

    /* Affichage */
    cout << "M" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "P" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << chemin[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){ /* k est un raccourci de i à j */
                    dist[i][j] = dist[i][k] + dist[k][j];
                    chemin[i][j] = chemin[i][k];
                }
            }
        }

        /* Affichage */
        cout << k << " est un raccourci ? :" << endl << endl;
        cout << "M" << endl;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << dist[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        cout << "P" << endl;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << chemin[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void itineraire(int i, int j, int chemin[][n]){
    if(chemin[i][j] != -1){
        if(i == chemin[i][j] || j == chemin[i][j]){
            cout << "L'itineraire est : " << i << " " << j << endl;
        }
        else{
            cout << "L'itineraire est : " << i << " " << chemin[i][j] << " " << j << endl;
        }
    }
    else{
        cout << "Il n'y a pas de tel chemin entre " << i << " et " << j << endl;
    }
}

int main(){

    int longueur[n][n]={{0,2,inf,4,inf}, //Les longueurs des arcs.
                        {inf,0,2,inf,inf},   //long[i][j]=inf si l'arc ij n'existe pas
                        {inf,inf,0,2,inf},
                        {inf,-3,inf,0,2},
                        {2,inf,inf,inf,0}};
    int dist[n][n];

    //Le tableau des distances.
    int chemin[n][n];                    //Le tableau de la premiere etape du chemin de i a j.

//    floyd_warshall(longueur, dist, chemin);

//    int i, j;
//    cout << "Entrer le départ : ";
//    cin >> i;

//    cout << "Entrer la destination : ";
//    cin >> j;

//    itineraire(i, j, chemin);
    return 0;
}


/* Pour le calcul de la fermeture transitive:

const int n=6;
int arc[n][n]={{0,0,0,1,0,1},//La matrice d'adjacence du graphe oriente D.
               {1,0,1,1,0,0},
               {0,0,0,1,0,0},
               {0,0,0,0,1,1},
               {0,0,1,0,0,1},
               {0,0,1,0,0,0}};
int fermeture[n][n];         // La matrice de la fermeture transitive de D.

*/

/* Exercice 1 : Montpellier Saint-Roch - Paris Gare de Lyon ; Paris Gare du Nord - Calais Frethun ; Calais Frethun - Calais Ville*/
