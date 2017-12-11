#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include "Affichage.cc"

using namespace std;

void triFusion(int edge[][3], int m);

/* Engendre aléatoirement le tableau point.
* Complexité : O(n) */
void pointrandom(int n, coord point[]){
  srand(time(NULL));
  for(int i = 0; i < n; i++){
    point[i].abs = rand()%613;
    point[i].ord = rand()%793;
  }
}

/* Engendre le tableau edge de taille m * 3.
* Complexité : O(n*(n/2)) */
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

/* Trie le tableau edge, selon l'ordre croissant des valeurs de edge[k][2] (Tri à bulles).
* Complexité : O(m²) */
void tri(int m, int edge[][3]){
  bool trie = false;

  while(!trie){
    trie = true;
    for(int k = 0; k < m-1; k++){
      if(edge[k][2] > edge[k+1][2]){
        swap(edge[k], edge[k+1]);
        trie = false;
      }
    }
  }
}

/* Optimisation de l'algorithme composante.
* Complexité : O(m + n log(n)) */
void composantes_optimisees(int n, int m, int edge[][3], int comp[]){
  int t[n];
  vector<int> L[n];

  for(int x = 0; x < n; x++){ /*Pour tous les sommets*/
    comp[x] = x; /*comp(x) = x*/
    L[comp[x]].push_back(x);
    t[comp[x]] = 1;
  }

  for(int i = 0; i < m; i++){ /*Pour toutes les aretes*/
    if(comp[edge[i][0]] != comp[edge[i][1]]){
      if(t[comp[edge[i][0]]] > t[comp[edge[i][1]]]){
        swap(edge[i][0], edge[i][1]);
      }

      int aux = comp[edge[i][0]];
      t[comp[edge[i][1]]] += t[aux];

      while(!L[aux].empty()){
        comp[L[aux].back()] = comp[edge[i][1]];
        L[comp[edge[i][1]]].push_back(L[aux].back());
        L[aux].pop_back();
      }
    }
  }
}

/* Applique l'algorithme de Kruskal au tableau d'arêtes edge et construit le tableau arbre qui contient n-1 arêtes de l'arbre de distance minimum.
* Complexité : O(m log(n) + n²) */
void kruskal(int n, int edge[][3], int arbre[][2]){
  int comp[n]; int m = n*(n-1)/2;
  triFusion(edge, m); /* Exercice 6. Complexité : O(m log(n))*/
  for(int x = 0; x < n; x++){ /*Pour tous les sommets*/comp[x] = x; /*comp(x) = x*/}
  int x = 0;
  for(int i = 0; i < m; i++){ /*Pour toutes les aretes*/
    if(comp[edge[i][0]] != comp[edge[i][1]]){
      cout << "comp diff" << endl;
      int aux = comp[edge[i][0]];
      arbre[x][0] = edge[i][0];
      arbre[x][1] = edge[i][1];
      x++;
      for(int z = 0; z < n; z++){
        if(comp[z] == aux){
          comp[z] = comp[edge[i][1]];
        }
      }
    }
  }
}

void fusion(int edge[][3], int deb1, int fin1, int fin2){
  int table1[fin1-deb1+1][3];
  int deb2 = fin1+1;
  int cmp1 = deb1;
  int cmp2 = deb2;
  int i;

  for(i = deb1; i <= fin1; i++){
    table1[i-deb1][0] = edge[i][0];
    table1[i-deb1][1] = edge[i][1];
    table1[i-deb1][2] = edge[i][2];
  }

  for(i = deb1; i <= fin2; i++){
    if (cmp1 == deb2){
      break;
    }
    else if(cmp2 == (fin2+1)){
      edge[i][0] = table1[cmp1-deb1][0];
      edge[i][1] = table1[cmp1-deb1][1];
      edge[i][2] = table1[cmp1-deb1][2];
      cmp1++;
    }
    else if(table1[cmp1-deb1][2] < edge[cmp2][2]){
      edge[i][0] = table1[cmp1-deb1][0];
      edge[i][1] = table1[cmp1-deb1][1];
      edge[i][2] = table1[cmp1-deb1][2];
      cmp1++;
    }
    else{
      edge[i][0] = edge[cmp2][0];
      edge[i][1] = edge[cmp2][1];
      edge[i][2] = edge[cmp2][2];
      cmp2++;
    }
  }
}

void triFusionBis(int edge[][3], int deb, int fin){
  if(deb != fin){
    int milieu = (fin+deb)/2;
    triFusionBis(edge, deb, milieu);
    triFusionBis(edge, milieu+1, fin);
    fusion(edge, deb, milieu, fin);
  }
}

/* Tri fusion (tri plus efficace) */
void triFusion(int edge[][3], int m){
  if(m > 0){
    triFusionBis(edge, 0, m-1);
  }
}

int main(){
  int n;             //Le nombre de points.
  cout << "Entrer le nombre de points: ";
  cin >> n;
  int m=n*(n-1)/2;   // nombre d'arrêtes d'un graphe complet.
  coord point[n];   // Les coordonnees des points dans le plan.
  int edge[m][3];    // Les paires de points et le carre de leur longueur.
  int arbre[n-1][2] = {0}; // Les aretes de l’arbre de Kruskal.
  int comp[n];

  pointrandom(n, point); /* Exercice 1 */
  /* Affichage des points */
  for(int i = 0; i < n; i++){
    cout << "Point n° = " << i << " Abscisse : " << point[i].abs << " Ordonnée : " << point[i].ord << endl;
  }

  distances(n,m,point,edge); /* Exercice 2 */
  cout << "Apres distance " << endl;
  /* Affichage des arêtes */
  for(int i = 0; i < m; i++){
    cout << "Edge " << i << "-> 1er point : " << edge[i][0] << " Deuxieme point : " << edge[i][1] << " La distance : " << edge[i][2] << endl;
  }

  //tri(m,edge); /* Exercice 3 */
  kruskal(n, edge, arbre); /* Exercice 4 */

  /* Affichage des arêtes */
  cout << "\n\n Distances \n\n";
  for(int i = 0; i < m; i++){
    cout << "Edge " << i << "-> 1er point : " << edge[i][0] << " Deuxieme point : " << edge[i][1] << " La distance : " << edge[i][2] << endl;
  }

  /* Affichage des arêtes de l'arbre */
  for(int i = 0; i < m; i++){
    cout << "Arbre " << i << "-> 1er point : " << arbre[i][0] << " Deuxieme point : " << edge[i][1] << endl;
  }

  AffichageGraphique(n, point, arbre); /* Exercice 5 */

  return 0;
}
