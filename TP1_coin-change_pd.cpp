// Raquel Aoki ---Trabalho Pratico 1 -- 14/10


#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

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

    // arquivo de output
    ofstream output;
    output.open ("output.txt");
    int nivel;


    for(int k =0; k<levels.size();k++){
        vector<int> n_fases(levels[k]+ 1,10000); // vetor para memorizacao
        vector<int> inimigos(levels[k] + 1); // vetor para guardar os inimigos
        n_fases[0] = 0;
        nivel = levels[k];

        for(int i = 1; i < nivel + 1; i++){   // para todos os niveis de 0 at� o nivel da fase
            for(int j =0;j<foes.size(); j++){ /* sera subtraido o valor de todos os inimigos
                se o nivel � maior que o ranking do inimigo e a quantidade de inimigos do nivel da fase
                menos o inimigo[j]+1 � menor que a quantidade de inimigos do nivel, entao essa se torna
                a melhor solucao */
                if(i >= foes[j] && (1 + n_fases[i-foes[j]]) < n_fases[i]){
                    n_fases[i] = 1 + n_fases[i - foes[j]];
                    inimigos[i] = j;
                }
            }
        }
        output<< n_fases[nivel]<< " ";// pega na memoria
        while(nivel){
            output<<foes[inimigos[nivel]]<<" "; //o vetor inimigos guarda a posicao dos inimigos no vetor foes
            nivel = nivel- foes[inimigos[nivel]];
        }
        output <<"\n";
        n_fases.clear();
        inimigos.clear();
    }
}
