#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

/* Engendre aléatoirement le tableau edge en tirant au hasard chacune de ses entrées.
* Complexité : O(2m) */
void grapherandom(int n, int m, int edge[][2]){
  for(int i = 0; i < m; i++){ /* Pour toutes les arêtes */
    cout << "{";
    for(int j = 0; j < 2; j++){ /* Pour chacun des sommets de l'arête */
      edge[i][j] = rand()%n;
      /* On attribue un nombre au hasard entre 0 et le nombre de sommets */
      cout << edge[i][j]; /* On affiche */
      if(j != 1){
        cout << ",";
      }
    }
    cout << "}";
  }
  cout << endl;
}

/* Calcule les entrées du tableau comp de telle sorte que comp[i] = comp[j] si et seulement si i et j appartiennent à la même composante connexe de G.
* Complexité : O(n²) */
void composantes(int n, int m, int edge[][2], int comp[]){
  for(int x = 0; x < n; x++){ /*Pour tous les sommets*/
    comp[x] = x; /* comp(x) = x */
  }
  for(int i = 0; i < m; i++){ /*Pour toutes les aretes*/
    if(comp[edge[i][0]] != comp[edge[i][1]]){
      int aux = comp[edge[i][0]];

      for(int z = 0; z < n; z++){
        if(comp[z] == aux){
          comp[z] = comp[edge[i][1]]; /* comp(z) = comp(y) */
        }
      }
    }
  }

  for(int i = 0; i < n; i++){ /* Affichage */
    cout << "Numéro de composante à la fin : " << comp[i] << endl;
  }
}

/* Ecrit le nombre de points isolés de G (i.e les composantes de taille 1) et les nombres de composantes des autres tailles, dans l'ordre croissant.
* Complexité : O(n) */
void ecrituretailles(int n, int comp[]) {
  int occ[n] = {0};
  int taille[n+1] = {0};

  /* On calcule le nombre d'occurence de i dans comp[i] */
  for(int i = 0; i < n; i++){
    occ[comp[i]]++;
  }

  // /* Affichage des occurences */
  // for(int i = 0; i < n; i++){
  //   cout << "occ[" << i << "]: " << occ[i] << endl;
  // }

  /* On compte combien il y a de composantes de taille i (en filtrant les zéros) */
  for(int i = 0; i < n; i++) {
    if(occ[i] != 0) {
      taille[occ[i]+1]++;
    }
  }

  /* /* Affichage des tailles */
  // for(int i = 0; i < n; i++){
  //   cout << "taille[" << i << "]: " << taille[i+1] << endl;
  // }

  for(int i = 0; i < n; i++) {
    if(taille[i+1] != 0){
      if(i == 1){
        cout << "Il y a " << taille[i+1] << " point(s) isolés " << endl;
      }
      else{
        if(taille[i+1] > 1){
          cout << "Il y a " << taille[i+1] << " composante(s) de taille " << i << endl;
        }
        else{
          cout << "Il y a 1 composante de taille " << i << endl;
        }
      }
    }
  }
}

/* Optimisation de l'algorithme composante.
* Complexité : O(m + n log(n)) */
void composantes_optimisees(int n, int m, int edge[][2], int comp[]){
  int t[n];
  vector<int> L[n];

  for(int x = 0; x < n; x++){ /*Pour tous les sommets*/
    comp[x] = x; /*comp(x) = x*/
    L[comp[x]].push_back(x);
    t[comp[x]] = 1;
  }

  for(int i = 0; i < m; i++){ /*Pour toutes les arêtes*/
    if(comp[edge[i][0]] != comp[edge[i][1]]){
      if(t[comp[edge[i][0]]] > t[comp[edge[i][1]]]){
        swap(edge[i][0], edge[i][1]);
      }

      int aux = comp[edge[i][0]];
      t[comp[edge[i][1]]] += t[aux];

      while(!L[aux].empty()){ /* Complexité : O(n log(n)) */
        comp[L[aux].back()] = comp[edge[i][1]];
        L[comp[edge[i][1]]].push_back(L[aux].back());
        L[aux].pop_back();
      }
    }
  }
}

int main(){
  srand(time(NULL));

  int n;     // Nombre de sommets.
  int m;     // Nombre d'aretes.
  cout << "Entrer le nombre de sommets:";
  cin >> n;
  cout << "Entrer le nombre d'aretes:";
  cin >> m;
  int edge[m][2];    // Tableau des aretes.
  int comp[n];       // comp[i] est le numero de la composante contenant i.*/

  grapherandom(n, m, edge); /* Exercice 1 */
  composantes(n, m, edge, comp); /* Exercice 2 */
  ecrituretailles(n, comp); /* Exercice 3 */
  composantes_optimisees(n, m, edge, comp); /* Exercice 4 */

  return EXIT_SUCCESS;
}
