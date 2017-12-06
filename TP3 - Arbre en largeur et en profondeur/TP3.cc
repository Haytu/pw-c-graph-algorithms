#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <queue>
#include <math.h>
#include "Affichage.cc"

using namespace std;

/* Détermine si a est voisin de b ou non */
bool present(int a, int b, vector<int> voisins[]){
    for(int i = 0; i < voisins[b].size(); i++){
        if(voisins[b][i] == a){
            return true;
        }
    }
    return false;
}

/* Engendre aléatoirement les listes de voisins d'un graphe aléatoire de n sommets et m arêtes */
void voisinstrandom(int n, int m, vector<int>voisins[]){
    srand(time(NULL));
    int a, b;

    for(int i = 0; i < m; i++){
        do{
            a = rand()%n;
            b = rand()%n;
        } while(a == b || present(a, b, voisins)); /* On répète s'il y a une boucle ou arête déjà existante entre deux sommets*/

        voisins[a].push_back(b);
        voisins[b].push_back(a);
    }
}

/* Affiche la liste des voisins de tous les sommets */
void affichage_voisins(int n, vector<int> voisins[]){
    for(int i = 0; i < n; i++){
        cout << "Voisins de " << i << " : ";
        for(int j = 0; j < voisins[i].size(); j++){
            cout << voisins[i][j];

            if(voisins[i].size() > 1){
                cout << ", ";
            }
        }
        cout << endl;
    }
}

/* Effectue un parcours en largeur. */
void parcourslargeur(int n, vector<int>voisins[], int niveau[], int ordre[], int pere[], int arbre[][2]){
    int x = 0;
    int dv[n] = {0}; /* Sommets déjà vus */

    for(int i = 0; i < n; i++){
        niveau[i] = -1;
    }

    for(int i = 0; i < n-1; i++){
        arbre[i][0] = -1;
        arbre[i][1] = -1;
    }

    queue<int>AT[n]; /* FIFO  AT*/ int t;
    srand(time(NULL)); int racine = rand()%n; /* Le sommet racine au hasard */
    dv[racine] = 1; ordre[racine] = 1; pere[racine] = racine; niveau[racine] = 0; /* La racine */
    AT->push(racine);
    cout << "Racine : " << racine << endl;
    t = 2;

    while(AT->size() != 0){
        int aux = AT->front();
        AT->pop();
        for(int i = 0; i < voisins[aux].size(); i++){
            if(dv[voisins[aux].at(i)] == 0){
                dv[voisins[aux].at(i)] = 1;
                AT->push(voisins[aux].at(i));
                ordre[voisins[aux].at(i)] = t; t++;
                pere[voisins[aux].at(i)] = aux;
                niveau[voisins[aux].at(i)] = niveau[aux]+1;
                arbre[x][0] = aux;
                arbre[x][1] = voisins[aux].at(i);
                cout << "--------------" << endl;
                cout << "Sommet i: " << voisins[aux].at(i) << endl;
                cout << "Ordre: " << ordre[voisins[aux].at(i)] << endl;
                cout << "Niveau: " << niveau[voisins[aux].at(i)] << endl;
                cout << "Pere: " << pere[voisins[aux].at(i)] << endl;
                cout << "Aux : " << aux << endl;
                cout << "Voisin aux : " << voisins[aux].at(i) << endl;
                x++;
            }
        }
    }
}

/* Ecrit le nombre de sommets dans chaque niveau, et le nombre de sommets qui ne sont pas joignable à partir de 0. */
void ecritureniveaux(int n, int niveau[]){
    int occ[n] = {0}; int cpt = 0;

    for(int i = 0; i < n; i++){
        if(niveau[i] != -1){
            occ[niveau[i]] = occ[niveau[i]]+1;
        }
        else{
            cpt++;
        }
    }

    for(int i = 0; i < n; i++){
        if(occ[i] != 0){
            cout << "Il y a " << occ[i] << " sommet(s) au niveau " << i << endl;
        }
    }
    cout << "Il y a " << cpt << " sommet(s) qui ne sont pas de la composante de la racine" << endl;
}

/* Convertit une matrice d'arêtes en tableau de voisins, pour un certain seuil de distance d'arête */
void edgeToVoisins(int n, int m, int edge[][3], vector<int> voisins[], int seuil){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(edge[j][0] == i){
                if(edge[j][2] < seuil){
                    voisins[i].push_back(edge[j][1]);
                    voisins[edge[j][1]].push_back(i);
                }
            }
         }
    }
}

/* Engendre aléatoirement le tableau point */
void pointrandom(int n, coord point[]){
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        point[i].abs = rand()%613;
        point[i].ord = rand()%793;
    }
}

/* Engendre le tableau edge de taille m * 3 */
void distances(int n, int m, coord point[], int edge[][3]){
    int k = 0;
    for(int i = 0; i < n; i++){
        for(int j = n-1; j > i; j--){
            edge[k][0] = i;
            edge[k][1] = j;
            int dist_abs = pow(point[edge[k][1]].abs - point[edge[k][0]].abs, 2);
            int dist_ord = pow(point[edge[k][1]].ord - point[edge[k][0]].ord, 2);
            edge[k][2] = sqrt(dist_abs + dist_ord); /* Carré de la distance euclidienne */
            k++;
        }
    }
}

/* Effectue un parcours en profondeur */
void parcoursprofondeur(int n, vector<int>voisins[], int debut[], int fin[], int pere[], int niveau[]){
    int dv[n] = {0}; /* Sommets deja vus */
    vector<int>AT[n]; int t;

    for(int i = 0; i < n; i++){
        niveau[i] = -1;
    }

    srand(time(NULL)); int racine = rand()%n; /* Le sommet racine au hasard */
    dv[racine] = 1; debut[racine] = 1; pere[racine] = racine; /* La racine */
    cout << "racine = " << racine << " dv[racine] = " << dv[racine] << " debut[racine] = " << debut[racine] << " pere[racine] = " << pere[racine] << endl;
    niveau[racine] = 0; AT->push_back(racine);
    t = 2;

    while(AT->size() != 0){
        int x = AT->back();
        if(voisins[x].size() == 0){
            AT->pop_back();
            fin[x] = t; t++;
        }
        else{
            int y = voisins[x].back();
            voisins[x].pop_back();
            if(dv[y] == 0){
                dv[y] = 1;
                AT->push_back(y);
                debut[y] = t; t++; pere[y] = x;
                niveau[y] = niveau[x] + 1;
            }
        }
    }

    for(int i = 0; i < n; i++){
        cout << "-------" << endl;
        cout << "Sommet i: " << i << endl;
        if(niveau[i] > -1) cout << "Niveau: " << niveau[i] << endl;
        if(pere[i] > -1) cout << "Pere: " << pere[i] << endl;
        if(debut[i] > 0) cout << "Debut: " << debut[i] << endl;
        if(fin[i] > 0) cout << "Fin: " << fin[i] << endl;
    }
}

int main(){
    int n;             //Le nombre de sommets.
    int m;             // Le nombre d'aretes.
    cout << "Entrer le nombre de sommets: ";
    cin >> n;
    /* cout << "Entrer le nombre d'aretes: "; */
    /* cin >> m; */
    m=n*(n-1)/2;   // Le nombre de paires de points.

    vector<int> voisins[n];	// Les listes des voisins.
    int pere[n] = {-1};      // L'arbre en largeur.
    int ordre[n];           // L'ordre de parcours.
    int niveau[n];          // Le niveau du point.
    int debut[n] = {0};
    int fin[n] = {0};
    int edge[m][3];
    coord point[n];
    int arbre[n-1][2];

    //voisinstrandom(n, m, voisins); /* Exercice 1 */
    //affichage_voisins(n, voisins);

    //ecritureniveaux(n, niveau); /* Exercice 3 */

    //parcoursprofondeur(n, voisins, debut, fin, pere, niveau); /* Exercice 4 */

    pointrandom(n, point); /* TP2 */
    distances(n, m, point, edge); /* TP2 */
    edgeToVoisins(n, m, edge, voisins, 50);

    parcourslargeur(n, voisins, niveau, ordre, pere, arbre); /* Exercice 2 & 5*/
    /* Affichage de l'ordre */
    for(int i = 0; i < n; i++){
          cout << "Ordre : " << ordre[i] << endl;
    }

    ecritureniveaux(n, niveau); /* Exercice 3 */

    AffichageGraphique(n, point, arbre); /* Exercice 5 */

    return 0;
}
