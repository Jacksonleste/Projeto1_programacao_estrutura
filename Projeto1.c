/*
    Alunos: Jackson Jardel Gonçalves Leste e Diogo Santana Bandeira Moura 


*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
/* */
int menu();
void cadastrar();
void lerEmail(int pos);
void lerSexo(int pos);
void lerAltura(int pos);
void lerVacina(int pos);
void imprimeUsers();
void backup();
void restaurar();
void geraId();
void excluir();
int buscaId();
int buscaEmail();
int verificaEmail(char *email);
void imprimeUmUser(int posicao);
void editar();
int comparaEmail(int pos);
int stricmp(const char *a, const char *b);
void header(char *palavra);
void limpaTela();
void pause();
/* */

/* Variáveis globais */
char nome[1000][100], email[1000][100], sexo[1000][20], endereco[1000][100], buscarEmail[100];

double  altura[1000];
bool vacinabackup[1000];
int opcao, users=0, id[1000];


/* Backup */
char nomebackup[1000][100], emailbackup[1000][100], sexobackup[1000][20], enderecobackup[1000][100];

double  alturabackup[1000];
bool vacina[1000];

int usersbackup=0, idbackup[1000];

/* */

int main(void){
    srand(time(NULL));

    limpaTela();
    //limpaTela(); // limpar terminal
    //getchar(); // pausar o programa

    do{
    system("cls");

        switch (menu())
        {
        case 1:
            fflush(stdin);
            cadastrar();
            
            break;
        case 2:
            editar();
            break;
        case 3:
            excluir();
            break;
        case 4:
            // buscaId()
            limpaTela();
            header("BUSCAR USUARIO POR ID");
            imprimeUmUser(buscaId());
            pause();
            break;
        case 5:
            limpaTela();
            header("BUSCAR USUARIO POR EMAIL");
            imprimeUmUser(buscaEmail());
            pause();
            break;
        case 6:
            imprimeUsers();
            break;
        case 7:
            backup();
            break;
        case 8:
            restaurar();
            break;

        case 9:
            limpaTela();
            printf("Volte sempre!!!");
            pause();
            break;
        
        default:
            printf("Digite uma opcao valida!\n");
            break;
        }
    }while(opcao !=9);

    return 0;
}

void header(char *palavra){
    printf("-------------------------------------------\n");          
    printf("               %s\n", palavra);
    printf("-------------------------------------------\n");
}


int menu(){
    // limpaTela();
    printf("-------------------------------------------\n");          
    printf("               MENU\n");
    printf("-------------------------------------------\n");
    printf("(1) Inscever usuario. \n"); //Feito
    printf("(2) Editar um usuario. \n"); // 
    printf("(3) Excluir um usuario. \n"); // Feito
    printf("(4) Buscar um usuario pelo id. \n"); // Feito
    printf("(5) Buscar um usuario pelo email. \n"); // Feito
    printf("(6) Imprimir todos os usuarios cadastrados. \n"); //Feito
    printf("(7) Faca backup dos usuarios cadastrados. \n"); //Feito
    printf("(8) Restaurar dados do backup.\n"); // Feito
    printf("(9) Sair do programa.\n");

    printf("\nDigite o numero da opcao desejada: ");
    scanf("%d", &opcao);

    return opcao;

}


/* Cadastro */

void cadastrar(){
    if(users < 1000){
        limpaTela();
        header("CADASTRAR");
        geraId();

        fflush(stdin);
        printf("Insira seu nome completo: ");
        gets(nome[users]);

        do{
            lerEmail(users);
        }while(comparaEmail(users) == 0);

        lerSexo(users);

        fflush(stdin);
        printf("Insira seu endereco: ");
        gets(endereco[users]);

        lerAltura(users);

        lerVacina(users);

        limpaTela();
        printf("*\nUsuario cadastrado com sucesso!\nSeu id e: %d\n*\n", id[users]);
        pause();
        users ++;
    }else{
        printf("\nnumero maximo de usuarios cadastrados!\n\n");
    }
}

void geraId(){
    int idTeste, verifica=0;

    do{
        idTeste = rand();

        for(int c=0; c<1000; c++){
            if (idTeste == id[c]){
                verifica = 1;
                break;
            }
        }
    }while(verifica == 1);
    
    id[users] = idTeste;
}

int verificaEmail(char *email){
    int arroba;
    
    for(int c = 0; c <= 100; c++){

            if (email[c] == '@'){
                arroba = 1;
                break;
            }else{
                arroba = 0;
            }

        }
            if(arroba == 0){
            printf("erro! Lembre-se de colocar \"@\" !\n");
        }

        return arroba;
}

void lerEmail(int pos){
    int verifica, posicao;
    do{
        printf("Insira seu email: ");
        fflush(stdin);
        gets(email[pos]);

        verifica = verificaEmail(email[pos]);

    }while(verifica != 1);
}

int comparaEmail(int pos){
    int verifica;
    for(int c=0; c<users; c++){
            if(stricmp(email[pos], email[c]) == 0){
                verifica = 0;
                break;
            }else{
                verifica = 1;
            }
        }

    if(verifica == 0){
        printf("\nesse email ja esta cadastrado, nao podem ter dois cadastros com o mesmo email!\n\n");
    }

        return verifica;
}

void lerSexo(int pos){

    bool validacao = 0;

    do{ 
        fflush(stdin);
        printf("Insira seu sexo (masculino ou feminino): ");
        gets(sexo[pos]);

        if (stricmp(sexo[pos], "masculino") == 0 || stricmp(sexo[pos], "feminino") == 0){
            validacao = 1;
        }else{
            validacao = 0;
        }

        if (validacao != 1){
            printf("Opcao invalida, digite masculino ou feminino.\n");
        }

    }while(validacao != 1);
}

void lerAltura(int pos){
    do{
        printf("Insira sua altura (m): ");
        scanf("%lf", &altura[pos]);
        if(altura[pos] > 2 || altura[pos] < 1){
            printf("digite uma altura entre 1m e 2m\n");
        }
    }while(altura[pos] > 2 || altura[pos] < 1);
}

void lerVacina(int pos){

    do{
        printf("Voce tomou a vacina (1=Sim / 0=Nao)? ");
        scanf("%x", &vacina[pos]);

        if (vacina[pos] != 1 && vacina[pos] != 0){
            printf("Opcao Invalida, Digite 1 ou 0!\n");
        }
    } while(vacina[pos] != 1 && vacina[pos] != 0);
}

/* Editar usuário */

void editar(){
    char escolha;
        int pos, editarEscolha, alterar;
        editarEscolha;
            limpaTela();
            header("EDITAR USUARIO");
            printf("\n1- Buscar por id; \n2- Buscar por email.\nDigite o numero da opcao desejada: ");
            scanf("%d", &editarEscolha);
            if(editarEscolha == 1){
                pos = buscaId();
            } else if(editarEscolha == 2){
                pos = buscaEmail();
            }else{
                limpaTela();
                printf("Opcao invalida!\n");

                pause();
                pos = -1;

            }
        limpaTela();
        header("EDITAR USUARIO");

        imprimeUmUser(pos);

        if(pos >= 0){
            do{
                fflush(stdin);
                printf("\nDeseja editar esse usuario (S/N)? ");
                scanf("%c", &escolha);

                if(escolha == 's' || escolha == 'S'){

                    limpaTela();
                    header("EDITAR USUARIO");

                    printf("1 - Nome;\n");
                    printf("2 - Email;\n");
                    printf("3 - Sexo;\n");
                    printf("4 - Endereço;\n");
                    printf("5 - Altura;\n");
                    printf("6 - Vacina;\n");
                    printf("insira o numero da informacao do usuario voce deseja alterar: ");
                    scanf("%d", &alterar);

                    switch (alterar)
                    {
                    case 1:
                        fflush(stdin);
                        printf("Insira seu nome completo: ");
                        gets(nome[pos]);
                        break;

                    case 2:
                        lerEmail(pos);
                        break;
                
                    case 3:
                        lerSexo(pos);
                        break;
                
                    case 4:
                        fflush(stdin);
                        printf("Insira seu endereco: ");
                        gets(endereco[pos]);
                        break;

                    case 5:
                        lerAltura(pos);
                        break;

                    case 6:
                        lerVacina(pos);
                        break;
                    default:
                        printf("\nOpcao invalida!\n");

                        pause();
                        break;
                    
                }
                    limpaTela();
                    printf("informacao alterada com sucesso!\n");
                    pause();
                    
                }else if (escolha == 'n' || escolha == 'N'){
                    limpaTela();
                    printf("Operacao de edicao Cancelada!\n");
                    pause();
                }else if(escolha != 's' && escolha != 'S' && escolha != 'n' && escolha != 'N'){
                    printf("Opcao invalida! tente novamente.\n");
                }
            } while(escolha != 's' && escolha != 'S' && escolha != 'n' && escolha != 'N');
        }
}

/* Excluir usuário */

    void excluir(){
        char escolha;
        int pos, excluirEscolha;
            limpaTela();
            header("EXCLUIR USUARIO");
            printf("\n1- Buscar por id; \n2- Buscar por email.\nDigite o numero da opcao desejada: ");
            scanf("%d", &excluirEscolha);
            if(excluirEscolha == 1){
                pos = buscaId();
            } else if(excluirEscolha == 2){
                pos = buscaEmail();
            }else{
                limpaTela();
                printf("Opcao invalida!\n");
                pause();
                pos = -1;

            }
        limpaTela();
        header("EXCLUIR USUARIO");

        imprimeUmUser(pos);
        if(pos >= 0){
            do{
                fflush(stdin);
                printf("\nDeseja excluir esse usuario (S/N)? ");
                scanf("%c", &escolha);

                if(escolha == 's' || escolha == 'S'){

                    for(int c=pos; c<=users ;c++){
                        
                        if(c != users){
                            strcpy(nome[c], nome[c+1]);
                            strcpy(email[c], email[c+1]);
                            strcpy(sexo[c], sexo[c+1]);
                            strcpy(endereco[c], endereco[c+1]);
                            altura[c] = altura[c+1];
                            vacina[c] = vacina[c+1];
                            id[c] = id[c+1];                            
                        }else{

                            strcpy(nome[c], "");
                            strcpy(email[c], "");
                            strcpy(sexo[c], "");
                            strcpy(endereco[c], "");
                            altura[c] = 0;
                            vacina[c] = 0;
                            id[c] = 0;
                        }
                    }

                    users -= 1;
                    limpaTela();
                    printf("Usuario removido com sucesso!\n");
                    pause();
                    
                }else if (escolha == 'n' || escolha == 'N'){
                    limpaTela();
                    printf("Operacao de exlusao Cancelada!\n");
                    pause();
                }else if(escolha != 's' && escolha != 'S' && escolha != 'n' && escolha != 'N'){
                    printf("Opcao invalida! tente novamente.\n");
                }
            } while(escolha != 's' && escolha != 'S' && escolha != 'n' && escolha != 'N');
        }
    }

/* Busca usuário pelo id*/
    int buscaId(){
        int buscarId, posicao;

        printf("Digite o numero do Id do usuario: ");
        scanf("%d", &buscarId);

        
        for(int c=0; c<1000; c++){
                if (buscarId == id[c]){
                    posicao = c;
                    break;
                }else{
                    posicao = -1;
                }
        }

        if (posicao < 0){
            limpaTela();
            printf("Id nao encontrado!\n");
            pause();
        }


        return posicao;
    }

int buscaEmail(){
    strcpy(buscarEmail, "");
    int verifica, posicao;
    do{

        printf("Digite o email do usuario: ");
        fflush(stdin);
        gets(buscarEmail);

        verifica = verificaEmail(buscarEmail);

    }while(verifica != 1);

    for (int c=0; c <=100; c++){

        if(stricmp(buscarEmail, email[c]) == 0){
            posicao = c;
            break;
        }else{
            posicao = -1;
        }
    }

    if (posicao < 0){
        limpaTela();
        printf("Email nao encontrado\n");
        pause();
    }

    return posicao;
    
}


void imprimeUmUser(int posicao){
    
    if(posicao >= 0){
    
        char imprimeVacina[5];

        printf("-------------------------------------------------------------------------------------------------");

            if (vacina[posicao] == 1){
                strcpy(imprimeVacina, "sim");
            } else{
                strcpy(imprimeVacina, "nao");
            }  
            printf("\nId: %d \nNome: %s\nEmail: %s\nSexo: %s\nEndereco: %s\nAltura: %.2lfm\nVacinado: %s\n", id[posicao], nome[posicao], email[posicao], sexo[posicao], endereco[posicao], altura[posicao], imprimeVacina);
        printf("-------------------------------------------------------------------------------------------------\n");
    }
}

/* Imprime Usuários */

void imprimeUsers(){
    limpaTela();
    header("LISTA DE USUARIOS CADASTRADOS");
    if (users != 0){

        char imprimeVacina[5];

        printf("-------------------------------------------------------------------------------------------------");
        for (int c=0; c < users; c++){

            if (vacina[c] == 1){
                strcpy(imprimeVacina, "sim");
            } else{
                strcpy(imprimeVacina, "nao");
            }  
            printf("\nId: %d \nNome: %s\nEmail: %s\nSexo: %s\nEndereco: %s\nAltura: %.2lfm\nVacinado: %s\n", id[c], nome[c], email[c], sexo[c], endereco[c], altura[c], imprimeVacina);
            printf("-------------------------------------------------------------------------------------------------\n");
        }
    } else{
        limpaTela();
        printf("\nNao ha nenhum usuario cadastrado!\n");
    }
    pause();
}

/* Fazer Backup */

    void backup(){
        for (int c=0; c<users; c++){

            strcpy(nomebackup[c], nome[c]);
            strcpy(emailbackup[c], email[c]);
            strcpy(sexobackup[c], sexo[c]);
            strcpy(enderecobackup[c], endereco[c]);
            alturabackup[c] = altura[c];
            vacinabackup[c] = vacina[c];
            idbackup[c] = id[c];
        }
        usersbackup = users;

        limpaTela();
        printf("Backup realizado Com sucesso!\n");
        pause();
    }

/* Restaurar Dados */
    void restaurar(){
        
        for(int c=0; c < users; c++){
            strcpy(nome[c], "");
            strcpy(email[c], "");
            strcpy(sexo[c], "");
            strcpy(endereco[c], "");
            altura[c] = 0;
            vacina[c] = 0;
            id[c] = 0;
        }

        for (int c=0; c<users; c++){
            strcpy(nome[c], nomebackup[c]);
            strcpy(email[c], emailbackup[c]);
            strcpy(sexo[c], sexobackup[c]);
            strcpy(endereco[c], enderecobackup[c]);
            altura[c] = alturabackup[c];
            vacina[c] = vacinabackup[c];
            id[c] = idbackup[c];
        }
        users = usersbackup;

        limpaTela();
        printf("dados restaurados com sucesso!\n");
        pause();
    }


  void limpaTela(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else
    
    #endif
  }

  void pause(){
      printf("\nPressione ENTER para continuar..."); fflush(stdin); getchar();
  }