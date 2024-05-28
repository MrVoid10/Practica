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

typedef struct {
  int id;
  user client;
  int MarimeLista;
  comanda ListaComanda[MarimeMaximaProduse];
}tot;
/// VerificareEmail() - compileru face ravagii ca bla bla bla ca are erori, dar sunt mici warning-uri, la mine e pus compilarea pe padantic asa ca orce problema e eroare
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

// aici cu salvare si citire fisiere

int Scanare(tot toturi[]) {
  int i = 0;
  FILE *file = fopen("comenzi.txt", "r");
  if (file != NULL) {
    while (fread(&toturi[i], sizeof(tot), 1, file) == 1) {
      i++;
    }
    fclose(file);
  }
return i;}

void PrintTest(tot toturi[], int numElements) {
  for (int j = 0; j < numElements; j++) {
    printf("\nID[%d]: %d", j, toturi[j].id);
    printf("\nNume[%d]: %s", j, toturi[j].client.nume);
    printf("\nPrenume[%d]: %s", j, toturi[j].client.prenume);
    printf("\nEmail[%d]: %s", j, toturi[j].client.email);
    printf("\nTelefon[%d]: %s", j, toturi[j].client.telefon);
    printf("\nMarimeLista[%d]: %d", j, toturi[j].MarimeLista);
    for (int k = 0; k < toturi[j].MarimeLista; k++) {
      printf("\nProdus[%d][%d]: %d", j, k, toturi[j].ListaComanda[k].produsul);
      printf("\nBucata[%d][%d]: %d", j, k, toturi[j].ListaComanda[k].bucata);
      printf("\nPret[%d][%d]: %d", j, k, toturi[j].ListaComanda[k].pret);
    }
  }
}

void Citire(){
  tot toturi[100];
  int i = Scanare(toturi);
  PrintTest(toturi,i);
}

void Salvare(tot *totatedatele) {
  tot unu;
  memcpy(&unu, totatedatele, sizeof(tot)); 
  int ultima = -1;

  FILE *fi = fopen("ultimul.txt", "r");
  if(fi != NULL){
  fscanf(fi,"%i",&ultima);}
  fclose(fi);
  
  //printf("\nSalvare ID: %d", ultima);
  unu.id = ultima+1;

  // Deschidem fișierul "comenzi.txt"
  FILE *file = fopen("comenzi.txt", "a");
  if (file != NULL) {
    // Scriem structura "unu" în fișier
    fwrite(&unu, sizeof(unu), 1, file);
    fclose(file);
  }
  
  file = fopen("ultimul.txt", "w");
  fprintf(file,"%d",ultima+1);
  fclose(file);
}

void Client() {
  tot Toatedatele;
  Toatedatele.client = Logare();
  Meniu();
  printf("\nCate produse doriti să luati (limita de %d)?\nIntroduceți: ", MarimeMaximaProduse);
  scanf("%i", &Toatedatele.MarimeLista);
  while (Toatedatele.MarimeLista > MarimeMaximaProduse) {
    printf("Greșit, reintroduceți: ");
    scanf("%i", &Toatedatele.MarimeLista);
  }
  printf("\nIntroduceți ID-ul produsului și cantitatea (separate printr-un spațiu): \n");
  
  for (int i = 0; i < Toatedatele.MarimeLista; i++) {
    printf("[%d]: ",i+1);
    scanf("%i", &Toatedatele.ListaComanda[i].produsul);
    scanf("%i", &Toatedatele.ListaComanda[i].bucata);
    Toatedatele.ListaComanda[i].pret = PretProdusDupaId(Toatedatele.ListaComanda[i].produsul) * Toatedatele.ListaComanda[i].bucata;
  }

  Salvare(&Toatedatele);
  Citire(); // debug daca nu uit voi sterge
}

void Kurier(){
  Citire();
};

int main(){
  int Logarea=0;
  printf("logarea: 1 = Client ; 2 = Curier");
  scanf("%i",&Logarea);
  switch(Logarea){
    case 1:
      Client();
    break;

    case 2:
      Kurier();
    break;
  }
return 0;}
