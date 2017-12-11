#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

const int n = 6;//5 pour le début; //6 pour la fermeture transitive
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

void fermeture_transitive(int arc[][n],int fermeture[][n]){

  // Initialisation
  for(int i = 0; i < n; i++){
    for(int j=0; j < n; j++){
      fermeture[i][j] = arc[i][j]; // Il y a forcément un chemin entre les sommets reliés de le matrice arc
    }
  }

  for(int k=0; k < n; k++){
    for(int i=0; i < n; i++){
      for(int j=0; j < n; j++ ){
        // Si fermeture[i][j] initialisé à 1, fermeture_transitive[i][j] reste 1.
        // Si fermeture[i][j] initialisé à 0 MAIS qu'il existe (fermeture[i][k] == 1) ET(fermeture[k][j] == 1)  alors fermeture[i][j] devient 1
          fermeture[i][j] = fermeture[i][j] || (fermeture[i][k] && fermeture[k][j]);
        }
    }
  }

  // Affichage
  std::cout << "Matrice fermeture : " << '\n';
  for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
          cout << fermeture[i][j] << " ";
      }
      cout << endl;
  }
  cout << endl;
}

void graphe_oriente_random(int n, int longueur[][100]){
  srand(time(NULL)); int voisin1, voisin2;
  for(int i = 0; i < n; i++){
    do{
      voisin1 = rand()%n;
      voisin2 = rand()%n;
    } while(voisin2 == voisin1 || voisin1 == i || voisin2 == i);

    longueur[i][voisin1] = 1;
    longueur[i][voisin2] = 1;
  }
}

void compfortconnexe(int fermeture[][n]){
    vector<int> comp[n];
    //int comp[n];
    for(int x = 0; x < n; x++){ /*Pour tous les sommets*/
      comp[x].push_back(x); /* comp(x) = x */
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j <n;j++){
            if(fermeture[i][j] && fermeture[j][i] && i!=j){
                while(!comp[i].empty()){
                    int aux = comp[i].back();
                    comp[j].push_back(aux);
                    comp[i].pop_back();

                }
            }
        }
    }

    cout << "Composantes fortement connexes : {";
    for(int i =0; i < n;i++){
        if(comp[i].size() !=0){
            cout << "{";
            for(int j =0; j < comp[i].size();j++){
                cout << comp[i][j];
                if(comp[i][j+1]){
                    cout << ",";
                }
            }
            cout << "}";
            if(!comp[i+1].empty()){
                cout << ",";
            }
        }
    }
    cout << "}" << endl;

}

int main(){

  // int longueur[n][n]={{0,2,inf,4,inf}, //Les longueurs des arcs.
  //                     {inf,0,2,inf,inf},   //long[i][j]=inf si l'arc ij n'existe pas
  //                     {inf,inf,0,2,inf},
  //                     {inf,-3,inf,0,2},
  //                     {2,inf,inf,inf,0}};
  int dist[n][n];

  //Le tableau des distances.
  int chemin[n][n];                    //Le tableau de la premiere etape du chemin de i a j.

  int longueur[n][n] = {0};

  //graphe_oriente_random(n, longueur);

  /* Affichage */
  // for(int i = 0; i < 100; i++){
  //   for(int j = 0; j < 100; j++){
  //     cout << longueur[i][j];
  //   }cout << endl;
  // }

//  floyd_warshall(longueur, dist, chemin);

//  int i, j;
//  cout << "Entrer le départ : ";
//  cin >> i;

//  cout << "Entrer la destination : ";
//  cin >> j;

//  itineraire(i, j, chemin);

  int arc[n][n]={{0,0,0,1,0,1},//La matrice d'adjacence du graphe oriente D.
  {1,0,1,1,0,0},
  {0,0,0,1,0,0},
  {0,0,0,0,1,1},
  {0,0,1,0,0,1},
  {0,0,1,0,0,0}};
  int fermeture[n][n];         // La matrice de la fermeture transitive de D.

  fermeture_transitive(arc,fermeture);
  compfortconnexe(fermeture);

  return 0;
}

/* Exercice 1 : Montpellier Saint-Roch - Paris Gare de Lyon ; Paris Gare du Nord - Calais Frethun ; Calais Frethun - Calais Ville*/
