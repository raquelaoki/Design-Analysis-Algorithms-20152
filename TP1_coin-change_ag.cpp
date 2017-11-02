// Raquel Aoki ---Trabalho Pratico 1 -- 14/10

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main (int argsnum, char** argsvalues ) {
    // Lendo arquivo foes
    //ifstream file1("foes.txt");
    ifstream file1(argsvalues[1]);
    istream_iterator<int> start(file1), end;
    vector<int> foes(start, end);

    // Lendo arquivo levels
    //ifstream file2("levels.txt");
    ifstream file2(argsvalues[2]);
    istream_iterator<int> start2(file2), end2;
    vector<int> levels(start2, end2);

    //inicializando as variáveis
    int total, nivel,aux,j;
    vector<int> inimigos_selecionados;
    ofstream output;
    output.open ("output.txt");

    for(int i=0; i< levels.size();i++){
        total = 0;
        nivel = levels[i];
        j = foes.size()-1;
        while(j>=0 & nivel!=0){ // faz enquanto tem inimigos para percorrer e o nivel da fase é diferente de 0
            if(nivel>=foes[j]){
                aux = nivel/foes[j];
                total = total + aux;
                nivel=nivel-aux*foes[j];
                for(int k=1; k<=aux;k++) inimigos_selecionados.push_back(foes[j]);
            }
            j--;
        }
        output << total<< " ";
        for(int k=inimigos_selecionados.size()-1; k>=0;k--) output<< inimigos_selecionados[k]<< " ";
        output <<"\n";
        inimigos_selecionados.clear();
    }
    output.close();

}

