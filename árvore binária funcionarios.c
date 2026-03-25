#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Criação da struct funcionário
typedef struct Funcionario {
	int matricula;
	char nome[100];
	char cargo[100];
	float salario;
	struct Funcionario *esq, *dir;
} Funcionario;


//Função para criação de um novo funcionário
Funcionario* cadastrarFuncionario(int matricula, char nome[], char cargo[], float salario ){
	//Validação da matrícula
	while (matricula < 1 || matricula > 9999) {
		printf("Matrícula inválida, tende novamente!(Deve ter no máximo 4 digitos.)");
		scanf("%d", &matricula);
	}
	Funcionario* novo = (Funcionario*) malloc(sizeof(Funcionario));
	novo->matricula = matricula;
	//Armazenamento de nome e cargo utilizando strcpy(Copia o valor de um array de caracteres para outro)
	strcpy(novo->nome, nome);
	strcpy(novo->cargo, cargo);
	novo->salario = salario;
	novo->esq = novo->dir = NULL;
	return novo;
}

//Função para inserção de funcionários na árvore.
Funcionario* inserirFuncionario(Funcionario* raiz, int matricula, char nome[], char cargo[], float salario) {
	//Quando o nó é nulo, cadastra um novo funcionário
	if (raiz == NULL){
		return cadastrarFuncionario(matricula, nome, cargo, salario);
	}
	//Caso o nó não seja nulo, checa a matrícula, se for menor vai para a esquerda, se for maior, vai para a direita
	if (matricula < raiz->matricula){
		raiz->esq = inserirFuncionario(raiz->esq, matricula, nome, cargo, salario);
	} else {
		raiz->dir = inserirFuncionario(raiz->dir, matricula, nome, cargo, salario);
	}
	
	return raiz;
}

//Função para buscar funcionário específico
Funcionario* buscarFuncionario(Funcionario* raiz, int matricula){
	//Caso a raiz seja nula, retorna mensagem de falha e valor NULL;
	if (raiz == NULL){
		printf("\nFuncionario não encontrado!\n");
		return NULL;
	}
	//Caso a matrícula seja equivalente a matrícula da raiz, retorna a raiz
	if (matricula == raiz->matricula){
		return raiz;
	//Caso a matrícula seja menor que a matrícula da raiz, checa a matrícula da esquerda
	} else if (matricula < raiz->matricula){
		return buscarFuncionario(raiz->esq, matricula);
	//Caso a matrícula seja maior que a matrícula da raiz, checa a matrícula da direita
	} else {
		return buscarFuncionario(raiz->dir, matricula);
	}
}

//Função para atualizar cargo de um funcionário específico
void atualizarCargo(Funcionario* raiz, int matricula, char cargo[]){
	//Tenta buscar funcionário pela matrícula
	Funcionario* funcionario = buscarFuncionario(raiz, matricula);
	//Caso o funcionário seja encontrado com sucesso, atualiza o cargo
	if (funcionario != NULL){
		strcpy(funcionario->cargo, cargo);
		printf("\nCargo atualizado com sucesso!\n");
	}
}

//Função para atualizar salário de um funcionário específico
void atualizarSalario(Funcionario* raiz, int matricula, float salario){
	//Tenta buscar funcionário pela matrícula
	Funcionario* funcionario = buscarFuncionario(raiz, matricula);
	//Caso o funcionário seja encontrado com sucesso, atualiza o salário
	if (funcionario != NULL){
		funcionario->salario = salario;
		printf("\nSalario atualizado com sucesso!\n");
	}
}

//Função para listar todos os funcionários
void listarFuncionarios(Funcionario* raiz) {
	if(raiz != NULL){
		//Mostra informações do funcionário raiz
		printf("\nNome: %s", raiz->nome);
		printf("\nMatricula: %d", raiz->matricula);
		printf("\nCargo: %s", raiz->cargo);
		printf("\nSalario: R$: %.2f\n", raiz->salario);
		
		//Chama a função novamente para os funcionários à esquerda e à direita
		listarFuncionarios(raiz->esq);
		listarFuncionarios(raiz->dir);		
	}
	
}

int main(){
	Funcionario* raiz = NULL;
	
	//Inserção de 2 funcionários
	raiz = inserirFuncionario(raiz, 1, "Gustavo Stacoviaki", "Desenvolvedor de Software", 12000);
	raiz = inserirFuncionario(raiz, 2, "Guilherme Grassi", "Faxineiro", 500);
	
	
	//Listagem de funcionários
	printf("Lista de funcionarios: \n");
	listarFuncionarios(raiz);
	
	//Alterando cargos
	atualizarCargo(raiz, 1, "Faxineiro");
	atualizarCargo(raiz, 2, "Cliente");
	
	//Alterando salário
	atualizarSalario(raiz, 1, 500);
	atualizarSalario(raiz, 2, 0);
	
	//Funcionários atualizados
	printf("\nLista de funcionarios: \n");
	listarFuncionarios(raiz);
	
	//Buscar um funcionário
	
	Funcionario* fun = buscarFuncionario(raiz, 1);
	
	if(fun != NULL){
		printf("\nFuncionario encontrado:\n Nome: %s\n Cargo: %s", fun->nome, fun->cargo);
	}
	
}

