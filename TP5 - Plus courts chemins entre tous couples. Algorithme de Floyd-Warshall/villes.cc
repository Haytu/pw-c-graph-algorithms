#include <iostream>
#include <vector>
#include "Affichage.cc"

using namespace std;
//typedef struct coord{int abs; int ord;} coord;

void floyd_warshall(int longueur[41][41], int dist[41][41], int chemin[41][41]){
  int infini = 10000;
  /* Initialisation */
  for(int i = 0; i < 41; i++){
    for(int j = 0; j < 41; j++){
      if(longueur[i][j] != infini){
        dist[i][j] = longueur[i][j];
        chemin[i][j] = j; /* P[][] dans le cours */
      }
      else{
        dist[i][j] = infini;
        chemin[i][j] = -1;
      }
    }
  }

  /* Affichage */
  cout << "M" << endl;
  for(int i = 0; i < 41; i++){
    for(int j = 0; j < 41; j++){
      cout << dist[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  cout << "P" << endl;
  for(int i = 0; i < 41; i++){
    for(int j = 0; j < 41; j++){
      cout << chemin[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  for(int k = 0; k < 41; k++){
    for(int i = 0; i < 41; i++){
      for(int j = 0; j < 41; j++){
        if(dist[i][j] > dist[i][k] + dist[k][j]){ /* k est un raccourci de i à j */
          dist[i][j] = dist[i][k] + dist[k][j];
          chemin[i][j] = chemin[i][k];
        }
      }
    }

    /* Affichage */
    cout << k << " est un raccourci ? :" << endl << endl;
    cout << "M" << endl;
    for(int i = 0; i < 41; i++){
      for(int j = 0; j < 41; j++){
        cout << dist[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;

    cout << "P" << endl;
    for(int i = 0; i < 41; i++){
      for(int j = 0; j < 41; j++){
        cout << chemin[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
}

void itineraire(int i, int j, int chemin[41][41], char Villes[41][20], int itineraire_arbre[2][2]){
  if(chemin[i][j] != -1){
    if(i == chemin[i][j] || j == chemin[i][j]){
      cout << "L'itineraire est : " << Villes[i] << " " << Villes[j] << endl;
      itineraire_arbre[0][0] = i;
      itineraire_arbre[0][1] = j;
    }
    else{
      cout << "L'itineraire est : " << Villes[i] << " " << Villes[chemin[i][j]] << " " << Villes[j] << endl;
      itineraire_arbre[0][0] = i;
      itineraire_arbre[0][1] = chemin[i][j];
      itineraire_arbre[1][0] = chemin[i][j];
      itineraire_arbre[1][1] = j;
    }
  }
  else{
    cout << "Il n'y a pas de tel chemin entre " << Villes[i] << " et " << Villes[j] << endl;
  }
}

int main(){

  const int infini = 10000;

  char Villes[41][20]={"Amiens", "Angouleme", "Avignon", "Bayonne", "Bilbao", "Bordeaux", "Bourges", "Brest", "Brive", "Bruxelles", "Caen", "Cahors", "Clermont-Ferrand", "Dijon", "Geneve", "Grenoble", "Lille", "Limoges", "Luxembourg", "Lyon", "Marseille", "Millau", "Montpellier", "Mulhouse", "Nancy", "Nantes", "Nice", "Orleans", "Paris", "Perpignan", "Poitiers", "Reims", "Rennes", "Rodez", "Rouen", "Saint-Etienne", "Strasbourg", "Toulouse", "Tours", "Troyes", "Valence"};

  coord Position[41]={{282,84},{180,334},{412,443},{140,455},{80,480},{165,389},{304,253},{14,150},{249,365},{380,15},{182,117},{258,412},{322,322},{408,231},{470,287},{464,359},{324,32},{242,332},{470,60},{405,306},{433,480},{339,440},{365,461},{497,208},{453,148},{116,233},{515,460},{277,194},{296,146},{329,505},{208,271},{369,119},{120,175},{330,410},{228,101},{383,339},{508,152},{227,466},{220,230},{363,179},{408,377}};

  int Kilometre[41][41];
  int dist[41][41];
  int chemin[41][41];

  for(int i=0;i<41;i++){
    for(int j=0;j<41;j++){
      Kilometre[i][j]=infini;
    }
    Kilometre[i][i]=0;
  }

  Kilometre[0][34]=120; Kilometre[0][28]=130;
  Kilometre[0][31]=180; Kilometre[0][16]=140;

  Kilometre[1][30]=130;  Kilometre[1][17]=110;
  Kilometre[1][8]=170;  Kilometre[1][5]=120;

  Kilometre[2][40]=140;  Kilometre[2][22]=90;
  Kilometre[2][20]=90;

  Kilometre[3][5]=180;  Kilometre[3][37]=300;
  Kilometre[3][4]=70;

  Kilometre[4][3]=70;

  Kilometre[5][1]=120; Kilometre[5][8]=200; Kilometre[5][11]=230;
  Kilometre[5][37]=241; Kilometre[5][3]=180;

  Kilometre[6][27]=121; Kilometre[6][39]=240; Kilometre[6][13]=250;
  Kilometre[6][12]=190; Kilometre[6][38]=230;

  Kilometre[7][32]=240;

  Kilometre[8][11]=101; Kilometre[8][17]=100; Kilometre[8][1]=170;
  Kilometre[8][5]=200; Kilometre[8][33]=140;

  Kilometre[9][16]=110; Kilometre[9][31]=230; Kilometre[9][18]=210;

  Kilometre[10][34]=130; Kilometre[10][38]=260; Kilometre[10][32]=180;

  Kilometre[11][21]=180; Kilometre[11][8]=101; Kilometre[11][5]=230;
  Kilometre[11][37]=110; Kilometre[11][33]=105;

  Kilometre[12][6]=190; Kilometre[12][19]=210; Kilometre[12][35]=150;
  Kilometre[12][17]=230; Kilometre[12][33]=270;

  Kilometre[13][19]=200; Kilometre[13][23]=221; Kilometre[13][24]=220;
  Kilometre[13][39]=180; Kilometre[13][6]=250; Kilometre[13][14]=200;

  Kilometre[14][15]=145; Kilometre[14][19]=150; Kilometre[14][13]=200;

  Kilometre[15][26]=340; Kilometre[15][20]=270; Kilometre[15][40]=90;
  Kilometre[15][19]=150; Kilometre[15][14]=145;

  Kilometre[16][0]=140; Kilometre[16][31]=196; Kilometre[16][9]=110;

  Kilometre[17][30]=120; Kilometre[17][1]=110; Kilometre[17][8]=100;
  Kilometre[17][12]=230;

  Kilometre[18][31]=218; Kilometre[18][36]=220; Kilometre[18][9]=210;
  Kilometre[18][24]=200;

  Kilometre[19][40]=150; Kilometre[19][35]=80; Kilometre[19][12]=210;
  Kilometre[19][13]=200; Kilometre[19][14]=150; Kilometre[19][15]=150;

  Kilometre[20][22]=170; Kilometre[20][2]=90; Kilometre[20][26]=200;
  Kilometre[20][15]=270;

  Kilometre[21][37]=190; Kilometre[21][11]=180; Kilometre[21][22]=110;
  Kilometre[21][33]=60;

  Kilometre[22][29]=150; Kilometre[22][37]=240; Kilometre[22][21]=110;
  Kilometre[22][2]=90; Kilometre[22][20]=170; Kilometre[22][40]=200;

  Kilometre[23][13]=221; Kilometre[23][24]=170; Kilometre[23][36]=120;

  Kilometre[24][36]=160; Kilometre[24][23]=170; Kilometre[24][13]=220;
  Kilometre[24][31]=240; Kilometre[24][18]=200;

  Kilometre[25][32]=110; Kilometre[25][38]=210; Kilometre[25][30]=220;

  Kilometre[26][20]=200; Kilometre[26][15]=340;

  Kilometre[27][6]=121; Kilometre[27][39]=200; Kilometre[27][28]=132;
  Kilometre[27][38]=120;

  Kilometre[28][0]=130; Kilometre[28][34]=131; Kilometre[28][27]=132;
  Kilometre[28][39]=181; Kilometre[28][31]=140;

  Kilometre[29][37]=210; Kilometre[29][22]=150;

  Kilometre[30][25]=220; Kilometre[30][38]=100; Kilometre[30][17]=120;
  Kilometre[30][1]=130;

  Kilometre[31][24]=240; Kilometre[31][28]=140; Kilometre[31][39]=130;
  Kilometre[31][0]=180; Kilometre[31][16]=196; Kilometre[31][9]=230;
  Kilometre[31][18]=218;

  Kilometre[32][10]=180; Kilometre[32][38]=250; Kilometre[32][7]=240;
  Kilometre[32][25]=110;

  Kilometre[33][35]=200; Kilometre[33][40]=225; Kilometre[33][21]=60;
  Kilometre[33][8]=140; Kilometre[33][11]=105; Kilometre[33][12]=270;

  Kilometre[34][0]=120; Kilometre[34][28]=131; Kilometre[34][10]=130;

  Kilometre[35][12]=150; Kilometre[35][19]=80; Kilometre[35][40]=120;
  Kilometre[35][33]=200;

  Kilometre[36][23]=120; Kilometre[36][24]=160; Kilometre[36][18]=220;

  Kilometre[37][3]=300; Kilometre[37][5]=241; Kilometre[37][11]=110;
  Kilometre[37][21]=190; Kilometre[37][22]=240; Kilometre[37][29]=210;

  Kilometre[38][10]=260; Kilometre[38][32]=250; Kilometre[38][25]=210;
  Kilometre[38][30]=100; Kilometre[38][27]=120; Kilometre[38][6]=230;

  Kilometre[39][31]=130; Kilometre[39][28]=181; Kilometre[39][27]=200;
  Kilometre[39][6]=240; Kilometre[39][13]=180;

  Kilometre[40][2]=140; Kilometre[40][15]=90; Kilometre[40][35]=120;
  Kilometre[40][19]=150; Kilometre[40][33]=225; Kilometre[40][22]=200;

  floyd_warshall(Kilometre, dist, chemin);

  int i, j;
  cout << "Entrer le départ : ";
  cin >> i;

  cout << "Entrer la destination : ";
  cin >> j;

  int itineraire_arbre[41][2] = {0};
  itineraire(i, j, chemin, Villes, itineraire_arbre);

  AffichageGraphique(41, Position, itineraire_arbre);

}
