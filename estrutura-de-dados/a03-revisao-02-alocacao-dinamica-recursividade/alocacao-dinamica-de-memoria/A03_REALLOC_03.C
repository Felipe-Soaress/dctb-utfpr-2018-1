
#include<stdio.h>
#include<stdlib.h>

/* Faz a remo��o de uma informa��o cadastrada.
   Remove qualquer valor, independente da posi��o */

int quantidade = 0, *idades = NULL;

int  cadastrar();
int  remover();
void listar();

int main(){
    int opcao;

    do {
        printf("\n Menu de opcoes");
        printf("\n ==============\n");
        printf("\n <1> Cadastrar Idade");
        printf("\n <2> Remover Idade");
        printf("\n <3> Listar Idades e Media");
        printf("\n <4> Sair");

        printf("\n\n Qual a opcao escolhida? ");
        fflush(stdin);
        if (scanf("%d", &opcao) == 0){
            opcao = -1; // O scanf nao leu nada, for�a entrar no default
        }

        switch (opcao){

            case 1:cadastrar();
                   break;

            case 2:remover();
                   break;

            case 3:listar();
                   break;

            case 4:free(idades); // Libera o vetor alocado din�micamente
                   exit(0);

            default: printf("\n\a Opcao invalida!\n");
        }
    }while(1);
}

int cadastrar(){

    int* novoBloco;

    printf("\n Cadastrando uma idade");
    printf("\n =====================");

    novoBloco = (int*) realloc(idades, (quantidade + 1) * sizeof(int));

    if (novoBloco == NULL){
        printf("\n\a Erro ao alocar dinamicamente memoria!\n");
        return 0;
    }

    if (novoBloco != idades){
       printf("\n Movimentou para um novo bloco de memoria.\n");
       free(idades);
       idades = novoBloco;
    }else{
       printf("\n Apenas aumentou o bloco de memoria atual.\n");
    }

    printf("\n Entre com a idade: ");
    fflush(stdin);
    scanf("%d", &idades[quantidade]);

    quantidade++;

    printf("\n Cadastrado realizado com sucesso!\n");

    return 1;
}

int remover(){

    int cont, posicao = 0;

    if (quantidade == 0){
        printf("\n\a Nenhuma idade foi cadastrada!\n");
        return 0;
    }

    printf("\n Removendo uma idade");
    printf("\n ===================");

    printf("\n Entre com a posicao da idade: ");
    fflush(stdin);
    scanf("%d", &posicao);

    if (posicao < 1 || posicao > quantidade){
       printf("\n\a Posicao invalida!\n");
       return 0;
    }

    posicao--; // Pois o usuario n�o considerou que a primeira posicao � zero

    // Remove mantendo a ordem //

    quantidade--; // J� atualizamos a quantidade, desprezando a �ltima posi��o que ser� apagada

    /* Caso existam valores ap�s o que ser� apagado, ent�o estes ser�o movdidos para frente
       uma posi��o, sobrescrevendo o que ser� apagado. */

    for(cont = posicao; cont < quantidade; cont++){
        idades[cont] = idades[cont+1];
    }

    if (quantidade >= 1){

        // Vai restar algu�m na mem�ria

        int* novoBloco;

        novoBloco = (int*) realloc(idades, quantidade * sizeof(int));

        if (novoBloco == NULL){
           printf("\n\a Erro ao alocar dinamicamente memoria!\n");
           return 0;
        }

        if (novoBloco != idades){
           printf("\n Movimentou para um novo bloco de memoria.\n");
           free(idades);
           idades = novoBloco;
        }else{
           printf("\n Apenas diminuiu o bloco de memoria atual.\n");
        }

    }else{
        // N�o vai restar ningu�m, libera todo o bloco

        printf("\n Liberou o bloco de memoria atual.\n");
        free(idades);
        idades = NULL; // Evitar erro no realloc usando um ponteiro com valor inv�lido de bloco
    }

    printf("\n Remocao realizada com sucesso!\n");

    return 1;
}

void listar(){

    int indice, soma = 0;

    if (quantidade == 0){
        printf("\n\a Nenhuma idade foi cadastrada!\n");
        return;
    }

    printf("\n Listando todas as idades");
    printf("\n ========================");

    for (indice = 0; indice < quantidade; indice++){
        printf("\n %3d - Idade: %3d", indice + 1, idades[indice]);
        soma += idades[indice];
    }

    printf("\n\n A media das idades eh %.2f", (float) soma / quantidade);
    printf("\n\n O vetor ocupa %d Bytes em memoria.\n", sizeof(int) * quantidade);
}
