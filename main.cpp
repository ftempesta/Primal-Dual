#include <iostream>
#include <fstream>

using namespace std;

void imprime_vetor(int tamanho, int *vetor){
    for(int i = 0; i < tamanho; i++){
        cout << vetor[i] << " ";
    }
    cout << endl;
}

void imprime_matriz(int linha, int coluna, int **matriz){
    for (int i = 0; i < linha; i++){
		for (int j = 0; j < coluna; j++)
			cout << matriz[i][j] << " ";
        cout << endl;
	}
	cout << endl;
}


int main() {
    ifstream file("input.txt");

    //quantidade de vétices
    int n = 0;
    file >> n;
    //quantidade de conjuntos
    int m = 0;
    file >> m;
    //vetor de custos
    int *custo = new int[m]();
    for(int j = 0; j < m; j++){
        file >> custo[j];
    }
    //matriz de incidência
    int **N = new int*[n];       // cria primeiro as linhas
    for(int i = 0; i < n; i++)
        N[i] = new int[m];       //cria as colunas
    //Recebe matriz de incidência do arquivo
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++)
			file >> N[i][j];
	}
	imprime_matriz(n, m, N);
	//cria vetor de vertices escolhidos
	int *vertices = new int[n]();
    //cria vetor de conjuntos escolhidos
    int *conjuntos = new int[m]();
    //cria vetor x solução
    int *x = new int[n]();
    //cria variável auxiliar para guardar o conjunto escolhido
    int conjunto_escolhido;
    //cria variavel para armazenar o peso máximo que o conjunto suporta
    int peso_max;
    int k;
	for(int i = 0; i < n; i++){
	bool escolhe = false;
        if(vertices[i] != 1){
            int menor_custo = 99999999;
            for(int j = 0; j < m; j++){
                if(N[i][j] == 1){
                    if(custo[j] <= menor_custo){
                        menor_custo = custo[j];
                        x[i] = menor_custo;
                        conjunto_escolhido = j;
                        escolhe = true;
                    }
                }
            }
        }
        if(escolhe){
            conjuntos[conjunto_escolhido] = 1;
            peso_max = 0;
            for(k = 0; k < n; k++){
                if(N[k][conjunto_escolhido] == 1){
                    vertices[k] = 1;
                    peso_max += x[k];
                    if(peso_max <= custo[conjunto_escolhido])
                        continue;
                    else{
                        peso_max = peso_max - x[k];
                        x[k] = x[k] - peso_max;
                    }
                }
            }

        }
        cout << "y = ";
        imprime_vetor(m, conjuntos);
        cout<<"x = ";
        imprime_vetor(n, x);
        cout<<endl;
        cout<<endl;
    }
    int custo_total = 0;
    for(int j = 0; j < m; j++){
        if(conjuntos[j] == 1){
            custo_total += custo[j];
        }
    }
    cout << custo_total;
    return 0;
}
