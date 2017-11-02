  // Raquel Yuri da Silveira Aoki
  // Trabalho Final de PAA 2015/2	


    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <algorithm>    

    using namespace std;

    ofstream outfile("max_subgraph_heuristica.txt");

    void clique_k_recursiva(vector<int> cand, int k,
            vector<int> caminho,int passo,vector< vector<int> > &cliques,vector< vector<int> > &candidatos_restantes, vector<vector<int> > graph) {
            caminho.push_back(passo);
            if(k==1){
                cliques.push_back(caminho);
                candidatos_restantes.push_back(cand);
                //cout<< "tamanho do caminho acrescentado:  "<< cand.size()<< " quantidade de caminhos "<< candidatos_restantes.size() <<endl;

            }
            else{
                if(cand.size()!=0){ // se  iguial a zero nao faz nada
                    vector <int> novo_cand;
                    for(int l=0;l<cand.size();l++){
                        novo_cand.clear();
                        for(int m=l; m<cand.size(); m++){
                            if(binary_search (graph[cand[l]].begin(), graph[cand[l]].end(),cand[m])){
                                novo_cand.push_back(cand[m]);
                            }
                        }
                        clique_k_recursiva(novo_cand,k-1,caminho,cand[l],cliques,candidatos_restantes, graph);
                    }
                }
            }
    }

int calcula_mediana(vector<vector<int> > vetor){
  int mediana;
  int comprimento = vetor.size();
  vector <int> tamanhos;
  for(int i=0; i< vetor.size();i++) tamanhos.push_back(vetor[i].size());
  sort(tamanhos.begin(), tamanhos.end());
  if (comprimento % 2 == 0){
      mediana = (tamanhos[comprimento/2 - 1] + tamanhos[comprimento/2]) / 2;
  }
  else {
      mediana = tamanhos[comprimento/ 2];
  }
  return mediana;
}


    int main(int argc, char *argsvalues[]){

        //INICIALIZAÇÃO
        cout << "Clique Algorithm." << endl;
        int n,m,i, j, edge;
        //infile >> n;

        //ifstream infile1("g1_03.txt");
        //ifstream infile2("g2_03.txt");

        ifstream infile1(argsvalues[1]);
        ifstream infile2(argsvalues[2]);


        infile1>> n;
        infile2>> m;

        vector<vector<int> > graph, graph_aux;
        vector<int> row, row_aux;;
        int k;

        int v1, v2, c1=0, c2=0,ii,jj, vertice;
        vector<int> valor1, valor2;

        for(i=0;i<n*n;i++){
            infile1>>v1;
            valor1.push_back(v1);
        }
        int cont = 0;
        for(i=0;i<n*n;i++){
            if(cont==n){
                graph_aux.push_back(row_aux);
                row_aux.clear();
                cont=0;
            }
            if(valor1[i]==1){
                row_aux.push_back(i);
            }
            cont++;
        }


        for(i=0;i<m*m;i++){
            infile2>>v2;
            valor2.push_back(v2);
        }

        for(i=0; i< n ;i++){
            for(j=0;j< m ;j++){
                row.clear();
                //cout<< "linha "<<(i%n)*m + (j%m)<< "--> ";
                c1 = n*i+i;
                for(ii=i*n;ii< (i+1)*n ; ii++){
                v1 = valor1[ii];
                    c2 = m*j+j;
                    for(jj=j*m;jj<(j+1)*m;jj++){
                        vertice = (ii%n)*m + (jj%m);
                        v2 = valor2[jj];
                        if(ii!=c1 & jj != c2){
                            if((v1 == 1 & v2==1)||(v1==0 & v2==0)) {
                                row.push_back(vertice);
                               // cout<< vertice << " "; // " (" << v1 <<","<<v2<<")";
                            }
                        }
                        //if(jj==c2) c2 = c2 + m + 1;
                    }
                    //if(ii==c1) c1 = c1 + n + 1;
                }
                graph.push_back(row);
                //cout<< endl;
            }
        }

        cout << "Graph has n = " << n*m << " vertices." << endl;
        outfile<< "Graph has n = " << n*m << " vertices." << endl;

       /* cout<< "tamanho grafo real: " << graph.size()<<endl;
        cout<< "imprimindo grafo: \n";
        for(int i=0;i<graph.size();i++){
            cout<< "Vertice "<< i<< " --> ";
            for(int j=0;j<graph[i].size();j++){
                cout<< graph[i][j]<< " ";
            }
            cout<< endl;

        }*/


        k = calcula_mediana(graph_aux);
        cout<< " k inicial: "<< k<< endl;
        outfile<< " k inicial: "<< k<< endl;
        vector<int>caminho, candidatos;
        vector< vector<int> > cliques,cliques_aux, candidatos_restantes,candidatos_restantes_aux;
        int mediana;
        bool terminar=true;



        candidatos.clear();
        cliques_aux.clear();
        int aux3, cont1,passo;
        vector <int> novo_candidatos;
        bool maiores_primeiro = true;
        while(terminar){
            for(int aux=0;aux< graph.size();aux++){
            caminho.clear();
            candidatos.clear();
            for(int aux2=0;aux2< graph[aux].size();aux2++){
                if(graph[aux][aux2]>aux){
                candidatos.push_back(graph[aux][aux2]);
                }
            }
            clique_k_recursiva(candidatos,k,caminho,aux,cliques,candidatos_restantes,graph);
            }
        // enquanto não achar um clique de k, diminuir k/2 e continuo a procurar
            if(cliques.size()>0){
                terminar=false;
            }
            else{
                k = k/2;
            }
        }


              //1) clique e candidatos restantes viram 0
              //2) preciso refinar minha candidatos
              //3) o caminho se mantem


        cout<< "cliques encontrados: "<< cliques.size();
        outfile<< "cliques encontrados: "<< cliques.size()<< endl;

       // cout << " candidatos restantes : "<< candidatos_restantes.size() << endl;

        // tenta aumentar de k para k+1
        terminar = true;
        while(terminar){
            cliques_aux.clear();
            candidatos_restantes_aux.clear();
            cliques_aux = cliques;
            candidatos_restantes_aux = candidatos_restantes;
            cliques.clear();

            candidatos_restantes.clear();
            mediana = calcula_mediana(candidatos_restantes_aux);
            aux3=0;
            cont1=0;
            while( cont1< (cliques_aux.size()/2+1)){
                if(candidatos_restantes_aux[aux3].size()> mediana & maiores_primeiro){
                    for(int l=0;l<candidatos_restantes_aux[aux3].size();l++){
                        novo_candidatos.clear();
                        for(int m=l; m<candidatos_restantes_aux[aux3].size(); m++){
                            if(binary_search (graph[candidatos_restantes_aux[aux3][l]].begin(), graph[candidatos_restantes_aux[aux3][l]].end(),candidatos_restantes_aux[aux3][m])){
                                novo_candidatos.push_back(candidatos_restantes_aux[aux3][m]);
                            }
                        }

                       // cout<< "novo_candidato.size  "<< novo_candidatos.size()<< " passo: "<< candidatos_restantes_aux[aux3][l]<< endl;

                        clique_k_recursiva(novo_candidatos,1,cliques_aux[aux3],candidatos_restantes_aux[aux3][l],cliques,candidatos_restantes,graph);
                    }
                    cont1++;
                }
                aux3++;
                if(aux3==cliques_aux.size()){
                    maiores_primeiro=false;
                   aux3=0;
                }
                if(candidatos_restantes_aux[aux3].size()== mediana & !maiores_primeiro){
                    for(int l=0;l<candidatos_restantes_aux[aux3].size();l++){
                        novo_candidatos.clear();
                        for(int m=l; m<candidatos_restantes_aux[aux3].size(); m++){
                            if(binary_search (graph[candidatos_restantes_aux[aux3][l]].begin(), graph[candidatos_restantes_aux[aux3][l]].end(),candidatos_restantes_aux[aux3][m])){
                                novo_candidatos.push_back(candidatos_restantes_aux[aux3][m]);
                            }
                        }
                        clique_k_recursiva(novo_candidatos,1,cliques_aux[aux3],candidatos_restantes_aux[aux3][l],cliques,candidatos_restantes,graph);
                    }
                    cont1++;
                }


            }


            //cout<< "contador "<< cont1 << " quantidade de cliques: "<< cliques.size()<<endl;
            //cout<< "tamnho caminhos: ";
            //for(int t=0; t<cliques.size(); t++) cout<< cliques[t].size()<<" ";
            //cout<< endl;

            if(cliques.size()==1){ //tenho sometne um clique máximo
                terminar=false;
            }
            else if(cliques.size()==0){// nao tenho clique de tamanho k+1, continuar com o de k que tinh
                terminar=false;
                cliques = cliques_aux;
                candidatos_restantes = candidatos_restantes_aux;
            }
            else{
                 cliques_aux.clear();
                candidatos_restantes_aux.clear();
            }
        }
            cout<< endl;
            outfile<<endl;

        for(int n=0;n < cliques.size();n++){
            cout<< n<<".clique tamanho "<< cliques[n].size() << " -->";
            outfile << n<<".clique tamanho "<< cliques[n].size() << " -->";
                for(int nn=0;nn< cliques[n].size();nn++){
                    cout<< cliques[n][nn]<< " ";
                    outfile<< cliques[n][nn]<< " ";

                }
            cout<< endl;
            outfile<<endl;
        }

    }
