// Raquel Aoki -- Trabalho Pratico 1 -- 14/10 
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;



void forcabruta(int nivel, vector<int> inimigos, int num_foes, int& menor_num_foes,
    bool &solucao, vector<int> &menor_conjunto_inimigos,vector<int> conjunto_inimigos ){

    for(int i=inimigos.size()-1; i >=0 ;i--){
        int subnivel = nivel - inimigos[i];
	/*Retorna Verdadeiro caso o nivel ainda seja diferente de 0 (mais inimigos podem ser selecionados) 
	e caso a quantidade de inimigos dessa possivel solucao ainda seja menor que o menor numero de inimigos ja encontrado.*/	
	bool teste;
    	if(subnivel<0) teste=false;
    	else if(solucao && subnivel>0 && (num_foes+1>=menor_num_foes)) teste=false;
    	else teste=true;
    
	if(teste){
            if(subnivel==0){
                //encontrada uma solucao
                if(solucao == false || num_foes+1 < menor_num_foes){
                    // a nova solucao é a melhor
                    menor_num_foes = num_foes+1;
                    menor_conjunto_inimigos = conjunto_inimigos;
                    menor_conjunto_inimigos[i]++;
                    solucao=true;
                }
            }
            else{
                //continua a procurar a solucao
                vector<int> novo_conjunto_inimigos = conjunto_inimigos;
                novo_conjunto_inimigos[i]+=1;
                forcabruta(subnivel, inimigos,num_foes+1, menor_num_foes,solucao,menor_conjunto_inimigos, novo_conjunto_inimigos );
            }
        }
    }
}

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

    // variaveis
    int menor_num_foes, num_foes, nivel;
    bool solucao;
    vector<int> menor_conjunto_foes;

    for(int j = 0; j<levels.size(); j++){
        // inicializando as variaveis
        menor_num_foes=-1;
        num_foes=0;
        solucao=false;
        nivel = levels[j];
        for(int i=0; i<foes.size();i++)  menor_conjunto_foes.push_back(0);

        /* chama funcao que modifica o valor de menor_num_foes que eh o menor valor de inimigos para aquela fase
        e modifica o vector menor_conjunto_foes, que é um vetor com o tamanho da quantiadade de inimigos e que
        eh incrementado o valor na posicao i a cada vez que o inimigo[i] é selecionado.
        */
	
        forcabruta(nivel, foes, num_foes, menor_num_foes, solucao,menor_conjunto_foes,menor_conjunto_foes);

        output << menor_num_foes<< " ";
        for (int i = 0; i<menor_conjunto_foes.size() ;i++){
            if (menor_conjunto_foes[i] != 0) {
		for(int j=0; j<menor_conjunto_foes[i];j++){                
		    output << foes[i] << " ";
                }
            }
        }
	menor_conjunto_foes.clear();
        output<< "\n";

    }
    output.close();

}


