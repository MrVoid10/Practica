#include <stdio.h>
#include <string.h>

#define EmailSize 64
#define NumPrenumSize 32
#define TelefonSize 10
#define MarimeMinimaTelefon 7
#define MarimeMaximaProduse 10

typedef struct {
  char nume[NumPrenumSize];
  char prenume[NumPrenumSize];
  char email[EmailSize];
  char telefon[TelefonSize];
}user;

typedef struct {
  int produsul;
  int bucata;
  int pret;
}comanda;

int VerificareEmail(const char (*email)[EmailSize]) {
  char *p_atChar = strchr(email, '@');// daca are un '#'
  if (p_atChar == NULL) { 
    return 1;}

  if (p_atChar == email || *(p_atChar + 1) == '\0') {// Sa nu fie pus la urma '@'
    return 1;}

  char *p_dotChar = strchr(p_atChar, '.');// sa fie cel putin un '.' dupa @
  if (p_dotChar == NULL) {
    return 1;}

  if (p_dotChar == p_atChar + 1) {// sa fie cel putin un caracter intre '@' si '.' precum o litera
    return 1;}

  if (p_atChar != email && (*(p_atChar - 1) == '.' || *(p_atChar + 1) == '.')) { // se verivica daca la '@' se incepe sau se termina cu un '.'
    return 1;}

  if (*(p_dotChar + 1) == '\0' || *(p_dotChar + 1) == '.') {// se verifica domeniul dupa '@' daca se incepe sau termina cu '.'
    return 1;}

  return 0; //0 este pentru totul corect
}

int VerificareNumar(const char (*telefon)[TelefonSize]){
  if((*telefon)[0] != '0'){
    return 1;}
  int marime = strlen(telefon);
  if(marime < MarimeMinimaTelefon){
    return 1;}
  return 0;
}

int PretProdusDupaId(int id){
  switch(id){
    case 1:
      return 5;
    break;
    case 2:
      return 6;
    break;
    case 3:
      return 7;
    break;
    default:
      return 0;
  }
};

void Salvare(user *Client,comanda (*ListaComanda)[MarimeMaximaProduse],int *MarimeLista){
  int ultima;
  
  FILE *file = fopen("ultimul.txt","r");
  fread(ultima,sizeof(ultima),1,file);
  fclose(file);
  
  printf("%d",ultima);

  file = fopen("comenzi.txt","a");
  fwrite(ultima+1,sizeof(ultima),1,file);
  fwrite(Client,sizeof(Client),1,file);
  fwrite(MarimeLista,sizeof(MarimeLista),1,file);
  fwrite(ListaComanda,sizeof(ListaComanda),MarimeLista,file);
  fclose(file);
  
  file = fopen("ultimul.txt","w");
  fwrite(ultima+1,sizeof(ultima),1,file);
  fclose(file);
}

void Citire(){
  int id;
  user Client;
  comanda ListaComanda[MarimeMaximaProduse];
  int MarimeLista;

  FILE *file;
  
  printf("%d",id);

  file = fopen("comenzi.txt","r");
  fread(id,sizeof(id),1,file);
  fread(Client,sizeof(Client),1,file);
  fread(MarimeLista,sizeof(MarimeLista),1,file);
  fread(ListaComanda,sizeof(ListaComanda),MarimeLista,file);
  fclose(file);
  
  printf("%d",id);
}

user Logare(){
  user temp;
  printf("Introduceti numele: ");
  scanf("%31s",temp.nume);
  printf("Introduceti prenumele: ");
  scanf("%31s",temp.prenume);
  
  printf("Introduceti emailul: ");
  scanf("%63s",temp.email);
  while(VerificareEmail(&temp.email)){
    printf("Gresit\n Reintroduceti emailul: ");
    scanf("%63s",temp.email);
  }

  printf("Introduceti numarul de telefon: ");
  scanf("%9s",temp.telefon);
  while(VerificareNumar(&temp.telefon)){
    printf("Gresit\n Reintroduceti numarul: ");
    scanf("%9s",temp.telefon);
  }
  
return temp;}

void Meniu(){
  printf("\n\nMeniul\n");
  printf("1: Produs 1 | pret 5 per buc \n");
  printf("2: Produs 2 | pret 6 per buc \n");
  printf("3: Produs 3 | pret 7 per buc \n");
}

void Client(){
  user client = Logare();
  int numproduse;
  printf("\n%s",client.nume);
  printf("\n%s",client.prenume);
  printf("\n%s",client.email);
  printf("\n%s",client.telefon);
  Meniu();
  printf("\nCate produse doriti sa luati, limita de %d\nIntroduceti: ",MarimeMaximaProduse);
  scanf("%i",&numproduse);
  while(numproduse > MarimeMaximaProduse){
    printf("Gresit, Reintroduceti: ");
    scanf("%i",&numproduse);
  }
  comanda Lista[numproduse];
  printf("\nIntroduceti id la produs dupa un spatiu si catul: ");
  
  for(int i=0;i< numproduse;i++){// produsele , buc , pret incarcat
    scanf("%i",&Lista[i].produsul);
    scanf("%i",&Lista[i].bucata);
    Lista[i].pret = PretProdusDupaId(Lista[i].produsul) * Lista[i].bucata;
  }

  for(int i=0;i< numproduse;i++){// produsele , buc , pret arat
    printf("\n%d\n%d\n%d\n",Lista[i].produsul,Lista[i].bucata,Lista[i].pret);
  }
  Salvare(&client,&Lista,&numproduse);
  Citire();
};

void Kurier(){};

int main(){
  int Logarea=0;
  printf("logarea: 0 = Client ; 1 = Curier");
  scanf("%i",&Logarea);
  switch(Logarea){
    case 0:
      Client();
    break;

    case 1:
      Kurier();
    break;
  }
  


return 0;}
