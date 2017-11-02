// Raquel Aoki - TP2 - Grafos -

/*Practical Activity of the class Design and Analysis of Algorithm master level at UFMG 2015/2.

Problem with N-Puzzle and A-star.

Heuristics:
    Manhattan Distance
    Hamming Distance
    Euclidian Distance*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iterator>
#include<map>

using namespace std;

class a_star {
    private:
        struct tree_node{
		   tree_node* parent; // de ibde ele veio
		   char caminho; // d: direita, e:esquerda, c:acima, b:baixo
           	   vector<int> state;
		   int cost; //custo
		   int index; // onde esta o _
		   int distance; // distancia
        };
	vector<tree_node*> stack; //pilha de prioridade
        map <long long int, int > configuracoes;
        tree_node* root;
	bool success;


    public:
        struct comparandoponteiros{
            bool operator()(const tree_node* l, const tree_node* r) {
            return l->cost < r->cost;
            }
        };
        a_star() { root = NULL; }
        // vector<int*> mergesort();
        bool isEmpty() const { return root==NULL; }
        void construindo(vector<int>,vector<int>,int,int);
        void inserir(tree_node*,vector<int>,int,int);
	void movendo(tree_node*, tree_node*, char,int);
	void print(tree_node*,int);
	void checkSuccess(tree_node*,vector<int> ,int);
	int h1(tree_node*,vector<int> );//distancia de manhatan
	int h2(tree_node*,vector<int> );
        int h3(tree_node*,vector<int> );
};

void a_star::construindo(vector<int> inicial,vector<int> final,int n, int heu) {

    // inicializacao do primeiro nó
	tree_node* t1 = new tree_node;
	for (int i=0; i<(signed)inicial.size(); i++)
		t1->state.push_back(inicial[i]);
	t1->cost = h1(t1, final);
	t1->distance = 1;
	t1->parent = NULL;
    t1->caminho='z';
    //guardando a posicao do _ (que foi armazenado como 0)
	for (int i=0; i<n; i++) {
		if (inicial[i] == 0) {
			t1->index = i;
		}
	}

    // inicializando a fila
	if(isEmpty()) {
		root = t1;
		stack.push_back(root);
	}

    //inicializando a variavel sucess e criando o tree corrente
	success = false;
	tree_node* curr;


    // para o hash
    long long int config=0,vezes10=1;
    int j = 10,aux;
    for(int k = 0; k< n*n; k++){
        aux = t1->state[k]/10;
        if(aux>1) {
            config = config+t1->state[k]*vezes10*j;
            vezes10=vezes10*10*j;
        }
        else{
            config = config+t1->state[k]*vezes10;
            vezes10=vezes10*10;
        }
    }
    configuracoes[config]= t1->cost;


	while (stack.size() > 0) { // enquanto a filha nao estiver vazia
	    int min=0;
	    tree_node* min2;
	    for(int i=1;i<stack.size();i++){
            if((stack[min]->cost)>(stack[i]->cost)){
                min=i;
            }
        }
        min2= stack[0];
        stack[0]=stack[min];
        stack[min]=min2;
		curr = stack.front(); // arvore corrente é o primeiro da pilha
		stack.erase(stack.begin()); // tira esse elemento da pilha
		inserir(curr,final,n, heu); // insere ele
	}
}

void a_star::inserir(tree_node* curr,vector<int> final,int n, int heu) {

 // cria um no para cada caminho possível
        tree_node* t1 = new tree_node;
        tree_node* t2 = new tree_node;
        tree_node* t3 = new tree_node;
        tree_node* t4 = new tree_node;

        movendo(curr, t1, 'u',n);
        movendo(curr, t2, 'r',n);
        movendo(curr, t3, 'l',n);
        movendo(curr, t4, 'd',n);

        t1->caminho = 'u';
        t2->caminho = 'r';
        t3->caminho = 'l';
        t4->caminho = 'd';


        t1->distance = curr->distance + 1;
        t2->distance = curr->distance + 1;
        t3->distance = curr->distance + 1;
        t4->distance = curr->distance + 1;

        switch (heu) {
                case 1 :
                    t1->cost = h1(t1,final) + t1->distance;
                    t2->cost = h1(t2,final) + t2->distance;
                    t3->cost = h1(t3,final) + t3->distance;
                    t4->cost = h1(t4,final) + t4->distance;
                    break;
                case 2 :
                    t1->cost = h2(t1,final) + t1->distance;
                    t2->cost = h2(t2,final) + t2->distance;
                    t3->cost = h2(t3,final) + t3->distance;
                    t4->cost = h2(t4,final) + t4->distance;
                    break;
                 case 3 :
                    t1->cost = h3(t1,final) + t1->distance;
                    t2->cost = h3(t2,final) + t2->distance;
                    t3->cost = h3(t3,final) + t3->distance;
                    t4->cost = h3(t4,final) + t4->distance;
                    break;
        }

        //transformando o vetor em key

        long long int config1=0,config2=0,config3=0,config4=0,vezes1=1,vezes2=1,vezes3=1,vezes4=1;
        int j = 10,aux1,aux2,aux3,aux4;
        for(int k = 0; k< n*n; k++){
            aux1 = t1->state[k]/10;
            aux2 = t2->state[k]/10;
            aux3 = t3->state[k]/10;
            aux4 = t4->state[k]/10;
         //t1
        if(aux1>1) {
            config1 = config1+t1->state[k]*vezes1*j;
            vezes1=vezes1*10*j;
        }
        else{
            config1 = config1+t1->state[k]*vezes1;
            vezes1=vezes1*10;
        }
        //t2
        if(aux2>1) {
            config2 = config2+t2->state[k]*vezes2*j;
            vezes2=vezes2*10*j;
        }
        else{
            config2 = config2+t2->state[k]*vezes2;
            vezes2=vezes2*10;
        }
        //t3
        if(aux3>1) {
            config3 = config3+t3->state[k]*vezes3*j;
            vezes3=vezes3*10*j;
        }
        else{
            config3 = config3+t3->state[k]*vezes3;
            vezes3=vezes3*10;
        }
        //t4
        if(aux4>1) {
            config4 = config4+t4->state[k]*vezes4*j;
            vezes4=vezes4*10*j;
        }
        else{
            config4 = config4+t4->state[k]*vezes4;
            vezes4=vezes4*10;
        }
        }

        ///////// testa se é uma nova configuracao, se nao, testa se tem valor menor que a anterior
        // 1
        if(t1->state.size() >0){
            if (configuracoes.find(config1) == configuracoes.end() ) { //
                configuracoes[config1]= t1->cost;
            }
            else {
                    t1->state.clear();
            }
        }
        // 2
        if(t2->state.size() >0){
            if (configuracoes.find(config2) == configuracoes.end() ) { //
                configuracoes[config2]= t2->cost;
            }
            else {
                    t2->state.clear();
            }
        }
        // 3
        if(t3->state.size() >0){
            if (configuracoes.find(config3) == configuracoes.end() ) { //
                configuracoes[config3]= t3->cost;
            }
            else {
                    t3->state.clear();
            }
        }
          // 4
        if(t4->state.size() >0){
            if (configuracoes.find(config4) == configuracoes.end() ) { //
                configuracoes[config4]= t4->cost;
          }
            else {
                    t4->state.clear();
            }
        }


        t1->parent = curr;
        t2->parent = curr;
        t3->parent = curr;
        t4->parent = curr;

         // checando se a solucao foi encontrada
        bool	pass1 = true, pass2 = true, pass3 = true, pass4 = true;

        for (int i=0; i<final.size(); i++) {
            if (t1->state.size() > 0){
                if (t1->state[i] != final[i])
                    pass1 = false;
            }
            else
                pass1 = false;
            if (t2->state.size() > 0) {
                if (t2->state[i] != final[i])
                    pass2 = false;
            }
            else
                pass2 = false;
            if (t3->state.size() > 0) {
                if (t3->state[i] != final[i])
                    pass3 = false;
            }
            else
                pass3 = false;
            if (t4->state.size() > 0) {
                if (t4->state[i] != final[i])
                    pass4 = false;
            }
            else
                pass4 = false;
        }

        // se a solucao foi encontrada imprimri
        if (pass1) {
            success = true;
            print(t1,n);

        }
        else if (pass2) {
            success = true;
            print(t2,n);
       }
        else if (pass3) {
            success = true;
             print(t3,n);
      }
        else if (pass4) {
            success = true;
            print(t4,n);
	}

	if (success) {
        //cout<< "expansao: "<< stack.size()<<endl;
		while (!stack.empty())
			stack.erase(stack.begin());
	}

    // caso o link* (caminho acima) ainda esteja liberado e t* seja um caminho válido é acrescentado se não, é deletado
    else{
        if (t1->state.size() > 0){
            stack.push_back(t1);
        }
        else
            delete t1;
        if (t2->state.size() > 0) {
            stack.push_back(t2);
        }
        else
            delete t2;
        if (t3->state.size() > 0) {
            stack.push_back(t3);
        }
        else
            delete t3;
        if (t4->state.size() > 0){
            stack.push_back(t4);
        }
        else
            delete t4;
    }
 }
//manhatan distance
int  a_star::h1(tree_node* t,vector<int> final) {

	int cost = 0, tamanho =sqrt(final.size());
    int divisao1,divisao2;
    // nao conta o elemento 0
	for (int i=0; i<(signed)t->state.size(); i++) {
        if(t->state[i]!=0){
            if (t->state[i]%tamanho!=final[i]%tamanho) {
                cost=cost+abs((final[i]%tamanho)-(t->state[i]%tamanho)); //custo deslocamento horizontal
            }
            divisao1 = t->state[i]/tamanho;
            divisao2 = i/tamanho;
            if(divisao1!=divisao2){
                cost=cost+abs(divisao1-divisao2); //custo deslocamento horizontal
            }
        }
        else{
            cost= cost;
        }
	}
	return cost;
}

//Hamming distance
int  a_star::h2(tree_node* t,vector<int> final) {
	int cost = 0;

	for (int i=0; i<(signed)t->state.size(); i++) {
		if ((t->state[i] != final[i]) & t->state[i] != 0) {
			cost++;
		}
	}

	return cost;
}

//euclidean distance
int  a_star::h3(tree_node* t,vector<int> final) {

	int cost = 0, tamanho =sqrt(final.size());
    int divisao1,divisao2, aux1, aux2;
    // nao conta o elemento 0
	for (int i=0; i<(signed)t->state.size(); i++) {
        if(t->state[i]!=0){
            aux1= (t->state[i]%tamanho - final[i]%tamanho)*(t->state[i]%tamanho - final[i]%tamanho);
            divisao1 = t->state[i]/tamanho;
            divisao2 = i/tamanho;
            aux2=sqrt(aux1+(divisao1-divisao2)*(divisao1-divisao2));
            cost= cost+aux2;
        }
        else{
            cost= cost;
        }
	}
	return cost;
}


void a_star::movendo(tree_node* curr, tree_node* t, char direction, int n) {
	int temp, index;
	bool badMove = false;

    //localiza o _ (no caso, 0)
	for (int i=0; i<(signed)curr->state.size(); i++) {
		if (curr->state[i] == 0) {
			index = i;
		}
		t->state.push_back(curr->state[i]);
	}
	t->index = index;

	if (curr->distance > 2) { // pq 2
		if (index == curr->parent->index) {
			badMove = true;
		}
	}
	switch (direction) {
		case 'u' :
			if ((index > (n-1)) && (!badMove)) {
				temp = t->state[index];
				t->state[index] = t->state[index-n];
				t->state[index-n] = temp;
			}
			else
				t->state.erase(t->state.begin(), t->state.end());
			break;
		case 'r' :
			if ((index%n != (n-1)) && (!badMove)) {

				temp = t->state[index];
				t->state[index] = t->state[index+1];
				t->state[index+1] = temp;
			}
			else
				t->state.erase(t->state.begin(), t->state.end());
			break;
		case 'd' :
			if ((index < (n*n-n)) && (!badMove)) {
				temp = t->state[index];
				t->state[index] = t->state[index+n];
				t->state[index+n] = temp;
			}
			else
				t->state.erase(t->state.begin(), t->state.end());
			break;
		case 'l' :
			if ((index%n != 0) && (!badMove)) {
				temp = t->state[index];
				t->state[index] = t->state[index-1];
				t->state[index-1] = temp;
			}
			else
				t->state.erase(t->state.begin(), t->state.end());
			break;
	}
}


void a_star::print(tree_node* t,int n) {
	ofstream fout ("output.txt");

	vector<tree_node*> v;
	vector<char> passeio;
	while (t != NULL) {
		v.push_back(t);
		passeio.push_back(t->caminho);
        t = t->parent;
	}

	fout<< v.size()-1 <<endl;
	//cout<< v.size()-1 <<endl;

	for(int j=v.size()-1;j>=0;j--){
        switch (passeio[j]) {
            case 'u' :
             //   cout<< "acima\n";
                fout<< "acima\n";
                break;
            case 'd' :
             //   cout<< "abaixo\n";
                fout<< "abaixo\n";
                break;
            case 'l' :
             //   cout<< "esquerda\n";
                fout<< "esquerda\n";
                break;
            case 'r' :
              //  cout<< "direita\n";
                fout<< "direita\n";
                break;
        }
	}
	fout.close();
}


int main(int argsnum, char** argsvalues ) {

    a_star b;

    int heuristica = 1; // 1 distancia de manhatan; 2 distancia de hamming ; 3 distancia euclidiana
    //ifstream file1("input7.txt");
    ifstream file1(argsvalues[1]);

    string content;
    int n;
    bool primeiro=true;

    vector<int> inicial, final;

    while(file1 >> content) {
        if(primeiro){
            n = atoi(content.c_str());
             primeiro= false;
        }
       else {
            if( content=="_" ) content = "0";
            inicial.push_back(atoi(content.c_str()));
       }
    }
    for(int i=0; i < n*n;i++) final.push_back(i);

    //testando se tem solucao
   int inversoes = 0,linha=n-1;
    bool tem_solucao = true;

    for (int i = 0; i < n*n-1 ; i++){
        if(inicial[i]==0) linha=(i/n);
        else {
        for (int j = i+1; j < n*n; j++)
             if (inicial[i] > inicial[j]& inicial[j]!=0)
                  inversoes++;
        }
    }

    if((n%2==1 & inversoes%2==1) || (n%2==0 & (inversoes+linha)%2==1) ) tem_solucao=false;


    // testamdp se o tabuleiro ja esta pronto
    if(tem_solucao) {
        bool ok=true;
        int i=0;
        while(ok & i<n*n){
            if(inicial[i]!=final[i])
                ok = false;
            i++;
        }
        if(ok){
            ofstream fout ("output.txt");
            fout << "0";
            fout.close();
        }
        else{
            b.construindo( inicial,final,n,heuristica);
        }
    }
    else{
        ofstream fout ("output.txt");
        fout << "Sem solução";
        fout.close();
    }

}
