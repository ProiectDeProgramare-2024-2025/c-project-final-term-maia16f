#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include <conio.h>

#define rosu     "\033[31m"
#define verde   "\033[32m"
#define galben  "\033[33m"
#define albastru    "\033[38;5;153m"
#define resetare   "\033[0m"
#define roz "\033[38;5;205m"
#define mov "\033[38;5;93m"

#define MAX_MESE 50
#define MESE_FILE "mese.txt"
#define REZERVARI_FILE "rezervari.txt"

typedef struct {
    char mesa[100];
    char cemasa[100];
    int nr;
    int capacitate;
    int disponibile;
} Masa;

typedef struct {
    char mesa[100];
    char cemasa[100];
    int nr_masa;
    char ora_inceput[20];
    char zi_sapt[20];
    char data_inceput[20];
   } Rezervare;

Masa mese[MAX_MESE];
Rezervare rezervari[MAX_MESE];

int nr_mese = 0;
int nr_rezervari = 0;

void load_mese() {
    FILE *file = fopen(MESE_FILE, "r");
    if (!file) return;

    while (fscanf(file, "%s %s %d %d %d", mese[nr_mese].mesa, mese[nr_mese].cemasa,
                  &mese[nr_mese].nr, &mese[nr_mese].capacitate, &mese[nr_mese].disponibile) != EOF) {
        nr_mese++;
    }

    fclose(file);
}



void save_mese() {
    FILE *file = fopen(MESE_FILE, "w");
    if (!file) return;

    for (int i = 0; i < nr_mese; i++) {
        fprintf(file, "%s %s %d %d %d\n", mese[i].mesa, mese[i].cemasa,
                mese[i].nr, mese[i].capacitate, mese[i].disponibile);
    }

    fclose(file);
}

void load_rezervari() {
    FILE *file = fopen(REZERVARI_FILE, "r");
    if (!file) return;

    while (fscanf(file, "%s %s %d %s %s %s",
                   rezervari[nr_rezervari].mesa,
                   rezervari[nr_rezervari].cemasa,
                   &rezervari[nr_rezervari].nr_masa,
                   rezervari[nr_rezervari].ora_inceput,
                   rezervari[nr_rezervari].zi_sapt,
                   rezervari[nr_rezervari].data_inceput) == 6) {
        nr_rezervari++;
    }

    fclose(file);
}

void save_rezervari() {
    FILE *file = fopen(REZERVARI_FILE, "w");
    if (!file) return;

    for (int i = 0; i < nr_rezervari; i++) {
        fprintf(file, "%s %s %d %s %s %s\n", rezervari[i].mesa, rezervari[i].cemasa,
                rezervari[i].nr_masa, rezervari[i].ora_inceput, rezervari[i].zi_sapt,
                rezervari[i].data_inceput);
    }

    fclose(file);
}

void afisare_meniu(){
 printf("\n-----------------------------------\n");
 printf(" Meniu Rezervare Restaurant\n" resetare );
 printf("-----------------------------------\n");
 printf("1. Adauga sau sterge masa cu o anumita capacitate\n");
 printf("2. Afiseaza toate mesele\n");
 printf("3. Afiseaza rezervari existente\n");
 printf("4. Cauta masa libera\n");
 printf("5. Rezervare masa\n");
 printf("6. Stergere rezervare\n");
 printf("7. Iesire\n");

}

void adauga_sterge(Masa mese[], int *nr_mese)
{
  int ok, capacitate;
  printf("\n------------------------------------------------\n");
  printf(" Adauga sau sterge masa cu o anumita capacitate\n");
  printf("------------------------------------------------\n");
  printf("Introduceti capacitatea: \n");
  scanf("%d", &capacitate);
  printf("Introduceti 1 daca vreti sa adaugati o masa sau 0 in caz contrar \n");
  scanf("%d", &ok);
  if (ok == 1) {
    printf("Sa adaugat o masa cu o capacitate de %d\n", capacitate);

    strcpy(mese[*nr_mese].mesa, "Masa");
    strcpy(mese[*nr_mese].cemasa, "Noua");
    mese[*nr_mese].nr = *nr_mese + 1;
    mese[*nr_mese].capacitate = capacitate;
    mese[*nr_mese].disponibile = 1;
    (*nr_mese)++;
    save_mese();
  } else {
    int c=0;
    for(int i=0;i<*nr_mese;i++)
    {
        if(mese[i].capacitate == capacitate)
        {
            for(int j=i;j<*nr_mese-1;j++)
                mese[j]=mese[j+1];
            (*nr_mese)--;
            c=1;
            printf("O masa cu capacitatea "galben"%d"resetare" a fost stearsa.\n", capacitate);
            save_mese();
            break;
        }
    }
    if(c==0)
        printf("Nu a fost gasita masa cu capacitatea "galben"%d.\n"resetare,capacitate);
  }
}


void afisare_mese(Masa mese[], int nr_mese) {
    printf("\n-----------------------------------\n");
    printf("Afiseaza toate mesele disponibile\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < nr_mese; i++) {
        printf(roz "%s %s" resetare ", Numar: "albastru"%d"resetare", Capacitate: "galben"%d"resetare ", Disponibilitate: "verde"%d\n"resetare,
               mese[i].mesa, mese[i].cemasa, mese[i].nr, mese[i].capacitate, mese[i].disponibile);
    }
    printf("\n");
}

void afisare_rezervari(Rezervare rezervari[], int nr_rezervari) {
    printf("\n-----------------------------------\n");
    printf("Lista Rezervari\n");
    printf("-----------------------------------\n");

    if (nr_rezervari == 0) {
        printf("Nu exista rezervari inregistrate.\n");
    } else {
        for (int i = 0; i < nr_rezervari; i++) {
            printf("Masa: "roz"%s %s"resetare", Numar Masa: "albastru"%d\n"resetare, rezervari[i].mesa, rezervari[i].cemasa, rezervari[i].nr_masa);
            printf("Ora: "mov"%s"resetare", Ziua: "verde"%s"resetare", Data: "galben"%s\n"resetare, rezervari[i].ora_inceput, rezervari[i].zi_sapt, rezervari[i].data_inceput);
            printf("-----------------------------------\n");
        }
    }
}

void cauta_masa_capacitate(Masa mese[], int nr_mese) {
    printf("\n--------------------\n");
    printf("Cauta masa libera\n");
    printf("--------------------\n");
    int capacitate;
    printf("Introduceti capacitate: \n");
    scanf("%d", &capacitate);
    printf("Mese gasite cu capacitatea minima "galben"%d:\n"resetare, capacitate);
    int ok = 0;
    for (int i = 0; i < nr_mese; i++) {
        if (mese[i].capacitate >= capacitate && mese[i].disponibile > 0) {
            printf("Numar masa: "albastru"%d" resetare", Capacitate: "galben"%d\n"resetare, mese[i].nr, mese[i].capacitate);
            ok = 1;
        }
    }
    if (ok == 0) {
        printf("Nu s-a gasit masa cu capacitatea ceruta.\n");
    }
}
int este_ora_valida(const char* ora) {
    int h, m;
    if (sscanf(ora, "%d:%d", &h, &m) != 2)
        return 0;
    if (h < 0 || h > 23 || m < 0 || m > 59)
        return 0;
    return 1;
}
int este_zi_valida(const char* zi) {
    const char* zile_valide[] = {"Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(zi, zile_valide[i]) == 0)
            return 1;
    }
    return 0;
}
int este_data_valida(const char* data) {
    int zi, luna, an;
    if (sscanf(data, "%d/%d/%d", &zi, &luna, &an) != 3)
        return 0;
    if (an < 2025 || an > 2100 || luna < 1 || luna > 12 || zi < 1)
        return 0;

    int zile_in_luna[] = {31, (an % 4 == 0 && (an % 100 != 0 || an % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (zi > zile_in_luna[luna - 1])
        return 0;

    return 1;
}

 void efectueaza_rezervare(Masa mese[], int nr_mese) {
    printf("\n-----------------\n");
    printf(" Rezervare masa\n");
    printf("-----------------\n");
    Rezervare rezervare;
    char buf[100];
    int succes = 0;

    while (!succes) {
        printf("Introduceti numarul mesei pe care doriti sa o rezervati: ");
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d", &rezervare.nr_masa) == 1 && rezervare.nr_masa > 0) {
            succes = 1;
        } else {
            printf(rosu"Eroare"resetare": Introduceti un numar valid pozitiv pentru masa.\n");
        }
    }

    int ora, minut;
    succes = 0;
    while (!succes) {
        printf("Introduceti ora de inceput (format hh:mm): ");
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d:%d", &ora, &minut) == 2 &&
            ora >= 0 && ora <= 23 && minut >= 0 && minut <= 59) {
            sprintf(rezervare.ora_inceput, "%02d:%02d", ora, minut);
            succes = 1;
        } else {
            printf(rosu"Eroare"resetare": Ora invalida. Trebuie sa fie intre 00:00 si 23:59.\n");
        }
    }

    const char* zile_valide[] = {"Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica"};
    succes = 0;
    while (!succes) {
        printf("Introduceti ziua saptamanii (ex: Luni): ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = 0;

        for (int i = 0; i < 7; i++) {
            if (strcmp(buf, zile_valide[i]) == 0) {
                strcpy(rezervare.zi_sapt, buf);
                succes = 1;
                break;
            }
        }
        if (!succes) {
            printf(rosu"Eroare"resetare": Ziua introdusa nu este valida.\n");
        }
    }

    int zi, luna, an;
    succes = 0;
    while (!succes) {
        printf("Introduceti data (format dd/mm/yyyy): ");
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d/%d/%d", &zi, &luna, &an) == 3 &&
            zi >= 1 && zi <= 31 && luna >= 1 && luna <= 12 && an >= 2024) {
            sprintf(rezervare.data_inceput, "%02d/%02d/%04d", zi, luna, an);
            succes = 1;
        } else {
            printf(rosu"Eroare"resetare": Data invalida.\n");
        }
    }

    int c = 0;
    for (int i = 0; i < nr_mese; i++) {
        if (mese[i].nr == rezervare.nr_masa && mese[i].disponibile > 0) {
            strcpy(rezervare.mesa, mese[i].mesa);
            strcpy(rezervare.cemasa, mese[i].cemasa);
            mese[i].disponibile--;
            c = 1;
            break;
        }
    }

    if (c == 0) {
        printf(rosu"Eroare"resetare": Masa nu a fost gasita sau este deja rezervata.\n");
        return;
    }

    rezervari[nr_rezervari++] = rezervare;
    save_rezervari();
    save_mese();

    printf("\n------ Detaliile rezervarii ------\n");
    printf("Masa numarul: "albastru"%d\n"resetare, rezervare.nr_masa);
    printf("Ora rezervarii: "mov"%s\n"resetare, rezervare.ora_inceput);
    printf("Ziua rezervarii: "roz"%s\n"resetare, rezervare.zi_sapt);
    printf("Data: "galben"%s\n"resetare, rezervare.data_inceput);
    printf("Felicitari, rezervarea mesei a fost efectuata cu succes!\n");
}


void anuleaza_rezervare(Masa mese[], int nr_mese)
{
    int nr_masa;
    printf("\n-------------------------\n");
    printf("Stergere rezervare\n");
    printf("-------------------------\n");
    printf("Introduceti numarul mesei a carei rezervare doriti sa o anulati: ");
    scanf("%d", &nr_masa);
    while(getchar() != '\n');
    int c = 0;
    for (int i = 0; i < nr_rezervari; i++) {
        if (rezervari[i].nr_masa == nr_masa) {
            c = 1;
            for (int j = 0; j < nr_mese; j++) {
                if (mese[j].nr == nr_masa) {
                    mese[j].disponibile++;
                    break;
                }
            }
            for (int k = i; k < nr_rezervari - 1; k++) {
                rezervari[k] = rezervari[k + 1];
            }
            nr_rezervari--;
         FILE *f = fopen(REZERVARI_FILE, "w");
if (f == NULL) {
    printf(rosu"Eroare"resetare" la deschiderea fisierului pentru rescriere!\n");
    return;
}

for (int idx = 0; idx < nr_rezervari; idx++) {
    fprintf(f, "%s %s %d %s %s %s\n",
        rezervari[idx].mesa,
        rezervari[idx].cemasa,
        rezervari[idx].nr_masa,
        rezervari[idx].ora_inceput,
        rezervari[idx].zi_sapt,
        rezervari[idx].data_inceput
    );
}

fclose(f);


            printf("Rezervarea a fost stearsa cu succes.\n");
            break;
        }
    }
    if (!c) {
        printf("Nu a fost gasita o rezervare pentru aceasta masa.\n");
    }
}

void sterge_ecran()
{
    system("cls");
}
int main() {
    load_mese();
    load_rezervari();

    int optiune;

    do {
        afisare_meniu();
        printf("Introduceti numarul optiunii dorite: ");
        scanf("%d", &optiune);
        while(getchar() != '\n');

        switch (optiune) {
            case 1: {
                sterge_ecran();
                adauga_sterge(mese, &nr_mese);
                printf("\nPentru a reveni la meniul anterior apasati orice tasta");

                getch();
                sterge_ecran();
                break;
            }
            case 2:
                {
                sterge_ecran();
                afisare_mese(mese, nr_mese);
                printf("\nPentru a reveni la meniul anterior apasati orice tasta");

                getch();
                sterge_ecran();
                break;
            }
            case 3:
                {
                sterge_ecran();
                afisare_rezervari(rezervari, nr_rezervari);
                printf("\nPentru a reveni la meniul anterior apasati orice tasta");

                getch();
                sterge_ecran();
                break;
            }
            case 4:
                 {
                sterge_ecran();
                cauta_masa_capacitate(mese, nr_mese);
                printf("\nPentru a reveni la meniul anterior apasati orice tasta");

                getch();
                sterge_ecran();
                break;}

            case 5:{
                sterge_ecran();
                efectueaza_rezervare(mese, nr_mese);
                printf("\nPentru a reveni la meniul anterior apasati orice tasta");

                getch();
                sterge_ecran();
                break;
            }
            case 6:{
                sterge_ecran();
                anuleaza_rezervare(mese, nr_mese);
                printf("\nPentru a reveni la meniul anterior apasati orice tasta");

                getch();
                sterge_ecran();
                break;
            }
            case 7: {
                sterge_ecran();
                printf("O zi buna si va mai asteptam!!\n");
                break;
            }
            default:
                printf("Optiune invalida. Va rugam sa incercati din nou.\n");
        }
    } while (optiune != 7);

    return 0;
}
