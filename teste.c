#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
 
int menu();
void cadastro();
void editarUsuario();
void testeEmail();
int verificaEmail(char *email);
int buscarEmail();
void testeSexo();
void testeVacina();
void testeAltura();
void imprimirUsuario();
void idAutomatico();
int buscarUsuarioId();
void imprimirUsuarioId(int posicao);
void excluir();
void backupCadastro();
void restaurarBackup();
 
char nome[1000][100], funcaoEmail[100], email[100][100], sexo[1000][20], endereco[1000][100];
int intMenu, id[1000];
double altura[1000];
bool vacina[1000];
int contadorUsuario = 0;
// backup
char backupNome[1000][1000], backupEmail[100][100], backupSexo[20][100], backupEndereco[100][100];
double backupAltura[1000];
bool backupVacina[1000];
int backupContadorUsuario = 0;
//
int main(){
   srand(time(NULL));
   do{
       switch(menu()){
       case 1:
           cadastro();
           break;
       case 2:
           editarUsuario();
           break;
       case 3:
           excluir();
           break;
       case 4:
           imprimirUsuarioId(buscarUsuarioId());
           break;
       case 5:
           imprimirUsuarioId(buscarEmail());
           break;
       case 6:
           imprimirUsuario();
           break;
       case 7:
           backupCadastro();
           break;
       case 8:
           restaurarBackup();
           break;
       case 9:
           printf("\nSair ");
           break;
       default:
           printf(" \nExeculte o programa corretamente");
           break;
       }
   }while(intMenu != 9);
   return 0;
}
int menu(){
   printf(" \n\nMenu\n\n1 - Incluir usuário \n2 - Editar usuário \n3 - Excluir usuário \n4 - Buscar usuário pelo id \n5 - Buscar usuário pelo email");
   printf(" \n6 - Imprimir todos usuário cadastrados\n7 - Faça backup dos usuários cadastrado\n8 - Faça restauração dos dados\n9 - sair \n\n");
   scanf("%i", &intMenu);
   return intMenu;
}
void cadastro(){
   printf("\nDigite seu nome completo: ");
   getchar();
   fgets(nome[contadorUsuario], 100, stdin);
   testeSexo();
   testeEmail();
   printf("Digite seu endereço: ");
   fgets(endereco[contadorUsuario], 100, stdin);
   testeAltura();
   testeVacina();
   idAutomatico();
   printf("\nUsuário cadastrado - seu ID é: %d", id[contadorUsuario]);
   contadorUsuario++;
}
void editarUsuario(){
   printf("\nEditar usúario");
}
void excluir(){
   char escolha;
   int teste;
   int excluirEscolha;
   printf(" \nDigite a opção para excluir: \n\n1 - Exclusão por ID\n2 - Exclusão por email\n\n ");
   scanf("%d", &excluirEscolha);
   if(excluirEscolha == 1){
       teste = buscarUsuarioId();
   }
   else if(excluirEscolha == 2){
       teste = buscarEmail();
   }
   else{
       printf("Opção invalida");
       teste = -1;
   }
   imprimirUsuarioId(teste);
   if(teste >= 0){
       do{
           fflush(stdin);
           printf("\n\nDeseja realmente excluir o usuário ?  S - sim / N - não ");
           scanf("%c", &escolha);
           if(escolha == 'S' || escolha == 's'){
               for(int i = teste; i <= contadorUsuario; i++){
                   if(i != contadorUsuario){
                       strcpy(nome[i], nome[i + 1]);
                       strcpy(email[i], email[i + 1]);
                       strcpy(sexo[i], sexo[i + 1]);
                       strcpy(endereco[i], endereco[i + 1]);
                       altura[i] = altura[i + 1];
                       vacina[i] = vacina[i + 1];
                       id[i] = id[i + 1];
                   }else{
                       strcpy(nome[i], "");
                       strcpy(email[i], "");
                       strcpy(sexo[i], "");
                       strcpy(endereco[i], "");
                       altura[i] = 0;
                       vacina[i] = 0;
                       id[i] = 0;
                   }
               }
               contadorUsuario -= 1;
               printf(" Usuário removido\n");
           }
           else if(escolha == 'N' || escolha == 'n'){
               printf(" Operação cancelada\n");
           }
           else if(escolha != 'S' && escolha != 's' && escolha != 'N' && escolha != 'n'){
               printf(" Opção invalida");
           }
       }while(escolha != 'S' && escolha != 's' && escolha != 'N' && escolha != 'n');
   }
}
int verificaEmail(char *email){
   bool teste = 1;
   for(int i = 0; i <= 100; i++){
       if(email[i] == '@'){
           teste = 1;
           break;
       }
       else{
           teste = 0;
       }
   }
   if(teste == 0){
       printf("Digite seu email corretamente com @ \n");
   }
   return teste;
}
void testeEmail(){
   int teste;
   do{
       printf("Digite seu email: ");
       gets(email[contadorUsuario]);
       teste = verificaEmail(email[contadorUsuario]);
   }while(teste != 1);
}
int buscarEmail(){
   strcpy(funcaoEmail,"");
   int teste, posicao;
   do{
       printf("\nInsira o email do usuário: ");
       fflush(stdin);
       gets(funcaoEmail);
       teste = verificaEmail(funcaoEmail);
   }while(teste != 1);
   for(int i = 0; i <= 100; i++){
       if(strcmp (funcaoEmail, email[i]) == 0){
           posicao = i;
           break;
       }else{
           posicao = -1;
       }
   }
   if(posicao < 0){
       printf("\nEmail não cadastrado");
   }
   return posicao;
}

void testeSexo(){
   int sexoTeste;
   do{
       fflush(stdin);
       printf("Digite seu sexo: masculino, feminino ou não declarar): ");
       gets(sexo[contadorUsuario]);
       if(strcmp(sexo[contadorUsuario], "masculino") == 0 || strcmp(sexo[contadorUsuario], "feminino") == 0 || strcmp(sexo[contadorUsuario], "nao declarar") == 0){
           sexoTeste = 1;
       }
       else{
           sexoTeste = 0;
       }
       if(sexoTeste == 0){
           printf("Digite seu sexo corretamente\n");
       }
   }while(sexoTeste == 0);
}
void testeVacina(){
   do{
       printf("Tomou a vacina ? (Sim = 1 / Não = 0): ");
       scanf("%d", &vacina[contadorUsuario]);
       if(vacina[contadorUsuario] != 0 && vacina[contadorUsuario] != 1){
           printf("\nDigite as opções corretamente ");
       }
   }while(vacina[contadorUsuario] != 0 && vacina[contadorUsuario] != 1);
}
void testeAltura(){
   do{
       printf("Digite sua altura: ");
       scanf("%lf", &altura[contadorUsuario]);
       if(altura[contadorUsuario] > 2 || altura[contadorUsuario] < 1){
           printf("Digite uma altura válida para o programa\n");
       }
   }while(altura[contadorUsuario] > 2 || altura[contadorUsuario] < 1);
}
void imprimirUsuario(){
   char imprimir[10];
   for(int i = 0; i < contadorUsuario; i++){
       if(vacina[i] == 1){
           strcpy(imprimir, "sim");
       }
       else{
           strcpy(imprimir, "não");
       }
       printf(" \n Nome: %s Email: %s Sexo: %s\n Endereço: %s Altura: %.2lf\n Tomou a vacina ?: %s \n ID usuário: %d\n", nome[i], email[i], sexo[i], endereco[i], altura[i], imprimir, id[i]);
   }
}
void idAutomatico(){
   int idUsuario, teste = 0;
   do{
       idUsuario = rand();
       for(int i = 0; i < 1000; i++){
           if(idUsuario == id[i]){
               teste = 1;
               break;
           }
       }
   }while(teste == 1);
   id[contadorUsuario] = idUsuario;
}
int buscarUsuarioId(){
   int buscarUsuarioId, teste = 0, posicao;
   printf("\nDigite o número ID do usuário ");
   scanf("%d", &buscarUsuarioId);
   for(int i = 0; i < 1000; i++){
       if(buscarUsuarioId == id[i]){
           teste = 1;
           posicao = i;
           break;
       }
       else{
           posicao = -1;
       }
   }
   if(posicao < 0){
       printf(" \nid não encontrado");
   }
   return posicao;
}
void imprimirUsuarioId(int posicao){
   char imprimir[7];
   if(posicao >= 0){
       if(vacina[posicao] == 1){
           strcpy(imprimir, "sim");
       }
       else{
           strcpy(imprimir, "não");
       }
       printf(" \n Nome: %s Email: %s Sexo: %s\n Endereço: %s Altura: %.2lf\n Tomou a vacina ?: %s \n ID usuário: %d", nome[posicao], email[posicao], sexo[posicao], endereco[posicao], altura[posicao], imprimir, id[posicao]);
   }
}
void backupCadastro(){
   for(int i = 0; i < contadorUsuario; i++){
       strcpy(backupNome[i], nome[i]);
       strcpy(backupEmail[i], email[i]);
       strcpy(backupSexo[i], sexo[i]);
       strcpy(backupEndereco[i], endereco[i]);
       backupAltura[i] = altura[i];
       backupVacina[i] = vacina[i];
   }
   backupContadorUsuario = contadorUsuario;
   printf(" \nBackup Realizado com sucesso");
}
void restaurarBackup(){
   for(int i = 0; i < backupContadorUsuario; i++){
       strcpy(nome[i], "");
       strcpy(email[i], "");
       strcpy(sexo[i], "");
       strcpy(endereco[i], "");
       altura[i] = 0;
       vacina[i] = 0;
   }
   for(int i = 0; i < backupContadorUsuario; i++){
       strcpy(nome[i], backupNome[i]);
       strcpy(email[i], backupEmail[i]);
       strcpy(sexo[i], backupSexo[i]);
       strcpy(endereco[i], backupEndereco[i]);
       altura[i] = backupAltura[i];
       vacina[i] = backupVacina[i];
   }
   contadorUsuario = backupContadorUsuario;
   printf(" \nRestauração dos dados Realizado com sucesso");
}
 
/*   printf("Tomou a vacina ? (Sim = 1 / Não = 0): ");
   scanf("%d", &vacina[contadorUsuario]);
 
   for (int i = 0; i <= contadorUsuario; i++) {
 
       printf("%d", vacina[i]);
 
   } */
 

