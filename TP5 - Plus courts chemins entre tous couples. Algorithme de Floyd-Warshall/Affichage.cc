#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef struct coord{
  int abs; int ord;
} coord;

void AffichageGraphique(int n, coord point[], int arbre[][2]){
  ofstream output;
  output.open("Resultat.ps", ios::out);
  output << "%!PS-Adobe-3.0" << endl;
  output << "%%BoundingBox: 0 0 612 792" << endl;
  output << endl;

  for(int i = 0; i < n; i++){
    output << point[i].abs << " " << point[i].ord << " 3 0 360 arc" << endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;
    output << "stroke"<<endl;
    output << endl;
  }

  output << endl;

  for(int i = 0; i < n; i++){
    if(arbre[i][0] != 0 && arbre[i][1] != 0){
      output << point[arbre[i][0]].abs << " " << point[arbre[i][0]].ord << " moveto" << endl;
      output << point[arbre[i][1]].abs << " " << point[arbre[i][1]].ord << " lineto" << endl;
      output << "stroke" << endl;
      output << endl;
    }
  }

  output << "showpage";
  output << endl;
}
