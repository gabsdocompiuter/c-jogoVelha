#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// void menu();
void zeraJogo();
void novoJogo();
void mostraJogo();
void pegaJogada(int jogador);
char selecionaCaracter();

int fimJogo();
int houveEmpate();
int houveVitoria();

struct Jogada
{
    int vencedor;
    struct Jogada *prox;
};

struct Jogada * jogadaInicio = NULL;
struct Jogada * jogadaFim = NULL;

struct Jogada *getJogada(){
    return (struct Jogada*) malloc(sizeof(struct Jogada*));
}

char caracterJ1;
char caracterJ2;

int velha[3][3];
int jogoAtual = 0;

void limpaBuffer() {
	setbuf(stdin, NULL);
}

void addJogada(){
    if(jogadaInicio == NULL){
        jogadaInicio = getJogada();
        jogadaInicio->vencedor = jogoAtual;

        jogadaFim = jogadaInicio;
    }
    else{
        jogadaFim->prox = getJogada();
        jogadaFim->prox->vencedor = jogoAtual;
        jogadaFim = jogadaFim->prox;
    }
}

void mostrarJogos(){
    if(jogadaInicio == NULL){
        printf("Ainda não houveram jogos\n");
        system("pause");
        return;
    }

    struct Jogada *aux = jogadaInicio;
    int count = 1;
    int finalRelatorio = 0;

    do{
        printf("\n\nJogo %d, vencedor: ", count);
        if(aux->vencedor){
            printf("jogador %d\n\n", aux->vencedor);
        }
        else{
            printf("empate\n\n");

        }
        
        if(aux == jogadaFim) finalRelatorio++;
        aux = aux->prox;

        count++;
    } while(!finalRelatorio);

    system("pause");
}

void mostrarPorcentagens(){
    if(jogadaInicio == NULL){
        printf("Ainda não há informações para exibir\n");
        system("pause");
        return;
    }

    struct Jogada *aux = jogadaInicio;
    int count = 0;
    int finalJogadas = 0;

    int empates = 0;
    int vitoriasJ1 = 0;
    int vitoriasJ2 = 0;

    do{
        switch (aux->vencedor)
        {
            case 0:
                empates++;
                break;

            case 1:
                vitoriasJ1++;
                break;

            case 2:
                vitoriasJ2++;
                break;
        }
        
        count++;
        if(aux == jogadaFim) finalJogadas++;
        aux = aux->prox;
    } while(!finalJogadas);

    float rEmpate = (float)empates/count*100;
    float rJogdr1 = (float)vitoriasJ1/count*100;
    float rJogdr2 = (float)vitoriasJ2/count*100;

    printf("\n\nJogador 1: Vitória em %.2f dos jogos", rJogdr1);
    printf("\nJogador 2: Vitória em %.2f dos jogos", rJogdr2);
    printf("\nHouve empates em %.2f dos jogos\n\n", rEmpate);

    system("pause");
}

int menu(){
    system("cls");

    printf("Selecione uma das opções para continuar...");
    printf("\n1 - Jogar");
    printf("\n2 - Ver resultados");
    printf("\n3 - Ver porcentagens");
    printf("\n0 - Sair");
    printf("\nOpção escolhida: ");

    int aux;
    scanf("%d", &aux);
    while(aux < 0 || aux > 3){
        printf("Opção inválida! Tente novamente: ");
        scanf("%d", &aux);
    }

    return aux;
}

int main(){
    setlocale(LC_ALL, "portuguese");

    int opc;
    do{
        opc = menu();
        switch (opc)
        {
        case 1:
            novoJogo();
            addJogada();
            break;

        case 2:
            mostrarJogos();
            break;
        
        case 3:
            mostrarPorcentagens();
            break;

        default:
            break;
        }
    } while(opc != 0);

    printf("\n\n");
    system("pause");
    return 0;
}

void novoJogo(){
    zeraJogo();

    int fim = 0;
    int jogadas = 0;

    while(!fimJogo()){
        int jogador = jogadas % 2 == 0 ? 0 : 1;
        jogador++;

        mostraJogo();

        printf("\n\nJOGADOR %d\n", jogador);

        if (jogadas == 0)
            caracterJ1 = selecionaCaracter();

        if (jogadas == 1)
            caracterJ2 = selecionaCaracter();

        pegaJogada(jogador);

        jogadas++;
    }
    system("pause");
}

void zeraJogo(){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            velha[i][j] = 0;
        }
    }
}

void imprimeLinha1(){
    printf("\n       1       2       3");
}

void imprimeLinha2(){
    printf("\n    _______________________");
}

void imprimeLinha3(){
    printf("\n   |       |       |       |\n");
}

void imprimeLinha4(){
    printf("   |-------+-------+-------|");
}

void mostraJogo(){
    system("cls");

    imprimeLinha1();
    imprimeLinha2();
    imprimeLinha3();

    for (int i = 0; i < 3; i++)
    {
        printf(" %c ", i + 65);

        for (int j = 0; j < 3; j++)
        {
            char aux;

            switch (velha[i][j])
            {
                case 1:
                    aux = caracterJ1;
                    break;

                case 2:
                    aux = caracterJ2;
                    break;
            
                default:
                    aux = ' ';
                    break;
            }
            printf("|   %c   ", aux);
        }
        printf("|");

        if (i == 2) //última linha
        {
            printf("\n   |_______|_______|_______|");
        }
        else{
            imprimeLinha3();
            imprimeLinha4();
            imprimeLinha3();
        }
    }
}

char selecionaCaracter(){
    char aux;

    printf("\nSelecione um caracter para representá-lo no jogo: ");
    scanf("%s", &aux);
    limpaBuffer();
    
    return aux;
}

int fimJogo(){
    if(houveVitoria()) return 1;
    if(houveEmpate()) return 1;

    return 0;
}

int houveEmpate(){
    int countJogadas = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(velha[i][j] != 0){
                countJogadas++;
            }
        }
        
    }
    
    if(countJogadas == 9){
        mostraJogo();
        printf("\nAcabaram as jogadas e houve empate!\n");
        jogoAtual = 0;
        return 1;
    }

    return 0;
}

int houveVitoria(){
    int vitoria = 0;

    for (int i = 0; i < 3; i++)
    {
        //Verifica vitórias em linha reta (horizontal)
        if(!vitoria)
        if(velha[i][0] == velha[i][1] && velha[i][0] == velha[i][2]){
            vitoria = velha[i][0];
        }

        //Verifica vitórias em linha reta (vertical)
        if(!vitoria)
        if(velha[0][i] == velha[1][i] && velha[0][i] == velha[2][i]){
            vitoria = velha[0][i];
        }
    }

    if(!vitoria)
    if((velha[0][0] == velha[1][1] && velha[0][0] == velha[2][2])
    || (velha[0][2] == velha[1][1] && velha[0][2] == velha[2][0])){
        vitoria = velha[1][1];
    }

    if(vitoria){
        mostraJogo();
        printf("\nO jogador %d venceu!\n", vitoria);
        jogoAtual = vitoria;
    }
    
    return vitoria;
}

void pegaJogada(int jogador){
    char linha;
    int xJogada, yJogada;
    int jogadaFeita = 0;

    do{
        do{
            printf("Informe a linha na qual você quer jogar: ");
            scanf("%s", &linha);
            limpaBuffer();

            //Calcula o número da linha selecionada
            if(linha > 96) linha -= 33; // Diminui 33 do Código ASCI caso seja letra minúscula
            xJogada = linha - 64;
        } while(xJogada < 0 || xJogada > 3);
        
        do{
            printf("Informe a coluna na qual quer jogar: ");
            scanf("%d", &yJogada);
            limpaBuffer();

            yJogada--;
        } while(yJogada < 0 || yJogada > 3);

        if(velha[xJogada][yJogada] == 0){
            velha[xJogada][yJogada] = jogador;
            jogadaFeita = 1;
        }
        else{
            printf("\nJá foi feita uma jogada nessa posição!\n");
        }

    } while(!jogadaFeita);

}


//       1       2       3
//    _______________________
//   |       |       |       |
// A |   0   |   0   |   0   |
//   |       |       |       |
//   |-------+-------+-------|
//   |       |       |       |
// B |   0   |   0   |   0   |
//   |       |       |       |
//   |-------+-------+-------|
//   |       |       |       |
// C |   0   |   0   |   0   |
//   |_______|_______|_______|