#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;
typedef struct coord{int abs; int ord;} coord;

void pointrandom(int n, coord point[]){
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        point[i].abs = rand()%613;
        point[i].ord = rand()%793;
    }
}

void voisins(int n, int dmax, coord point[], vector<int> voisin[]){
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            int dist_abs = pow(point[j].abs - point[i].abs, 2);
            int dist_ord = pow(point[j].ord - point[i].ord, 2);
            int distance_euclidienne = sqrt(dist_abs + dist_ord);
            if(distance_euclidienne <= dmax){
                voisin[i].push_back(j);
                voisin[j].push_back(i);
            }
        }
    }
}

void AffichageGraphe(int n, coord point[], vector<int> voisin[]){
    ofstream output;
    output.open("Graphe.ps", ios::out);
    output << "%!PS-Adobe-3.0" << endl;
    output << "%%BoundingBox: 0 0 612 792" << endl;
    output << endl;
    for(int i=0;i<n;i++)
    {output << point[i].abs << " " << point[i].ord << " 3 0 360 arc" <<endl;
        output << "0 setgray" <<endl;
        output << "fill" <<endl;
        output << "stroke"<<endl;
        output << endl;
    }
    output << endl;
    for(int i=0; i<n; i++){
        while(!voisin[i].empty()){
            output << point[i].abs << " " << point[i].ord<< " moveto" << endl;
            output << point[voisin[i].back()].abs << " " << point[voisin[i].back()].ord<< " lineto" << endl;
            output << "stroke" << endl;
            output << endl;
            voisin[i].pop_back();
        }
    }
    output << "showpage";
    output << endl;
}

void AffichageGraphiqueArbre(int n, coord point[], int arbre[][2])       // Cree le fichier Exemple.ps qui affiche
// les points et l'arbre de Kruskal.
{ofstream output;
    output.open("Arbre.ps",ios::out);
    output << "%!PS-Adobe-3.0" << endl;
    output << "%%BoundingBox: 0 0 612 792" << endl;
    output << endl;
    for(int i=0;i<n;i++)
    {output << point[i].abs << " " << point[i].ord << " 3 0 360 arc" <<endl;
        output << "0 setgray" <<endl;
        output << "fill" <<endl;
        output << "stroke"<<endl;
        output << endl;
    }
    output << endl;
    for(int i=0;i<n-1;i++)
    {output << point[arbre[i][0]].abs << " " << point[arbre[i][0]].ord
                << " moveto" << endl;
        output << point[arbre[i][1]].abs << " " << point[arbre[i][1]].ord
                << " lineto" << endl;
        output << "stroke" << endl;
        output << endl;
    }
    output << "showpage";
    output << endl;
}

int distanceMinimum(int n, int d[], int traite[], int mini){
    int indice = 0;

    for(int i = 0; i < n; i++){
        if(mini > d[i] && traite[i] == 0){
            mini = d[i];
            indice = i;
        }
    }
    return indice;
}

int longueur(int x, int y, coord point[]){
    int dist_abs = pow(point[y].abs - point[x].abs, 2);
    int dist_ord = pow(point[y].ord - point[x].ord, 2);
    return sqrt(dist_abs + dist_ord);
}

/* Algorithme de Dijkstra. */
void dijkstra(int n, vector<int> voisin[], coord point[], int pere[]){
    int d[n]; int racine = 0; int traite[n] = {0};

    for(int i = 0; i < n; i++){
        pere[i] = -1;
        d[i] = 2147483647; /* +infini */
    }
    pere[racine] = racine; d[racine] = 0;

    for(int j = 0; j < n; j++){
        int mini = 2147483647;
        int x = distanceMinimum(n, d,traite,mini);
        cout << "x" << " " << x << endl;
        if(x != 2147483647){
            traite[x] = 1;

            for(int i = 0; i < voisin[x].size(); i++){
                int y = voisin[x].at(i);
                cout << "y : " << y << endl;
                int l = longueur(x, y, point);
                cout << "d[y] avant " << d[y] << endl;
                if((traite[y] == 0) && (d[y] > d[x] + l)){ /* x est un raccourci pour atteindre y */
                    d[y] = d[x] + l;
                    cout << "d[y] apres " << d[y] << endl;
                    pere[y] = x;
                }
            }
       }
    }
}

/* Remplit le tableau arbre avec toutes les arêtes ipere[i]. */
void construireArbre(int n, int arbre[][2], int pere[]){
    int k = 0; // Zero voisins

    for(int i = 0; i < n; i++){
        if(pere[i] > -1){
            arbre[i][0] = i;
            arbre[i][1] = pere[i];
            k++;
        }
    }
}

int main(){
    int n = 50;                   //Le nombre de points.
    int m;                   //Le nombre d aretes.
    cout << "Entrer le nombre de points: ";
    cin >> n;

    int dmax=50;             // La distance jusqu'a laquelle on relie deux points.

    vector<int> voisin[n];   // Les listes de voisins.
    coord point[n];         // Les coordonnees des points.

    int d[n];                // La distance a la racine.
    int arbre[n-1][2];       // Les aretes de l'arbre de Dijkstra.
    int pere[n];             // La relation de filiation de l'arbre de Dijkstra.

    pointrandom(n, point); /* Exercice 1 */
    voisins(n, dmax, point, voisin);
    //AffichageGraphe(n, point, voisin); /* Exercice 2 */

    dijkstra(n, voisin, point, pere); /* Exercice 3 */
    construireArbre(n, arbre, pere); /* Exercice 4 */
    AffichageGraphiqueArbre(n, point, arbre); /* Exercice 5 */

    for(int i = 0; i < n; i++){
        if(pere[i] != -1){
            cout << "Père de " << i << ": " << pere[i] << endl;
        }
    }
    return 0;
}
