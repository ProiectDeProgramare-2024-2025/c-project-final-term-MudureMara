#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nume[100], adresa[100],post[100],dataangajare[11],cnp[14];
    float salar;
} angajat;

angajat angajati[100];
int nrangajati = 0;

void afisare_meniu();
void alegere_optiune();
void adaugare();
void afisare();
void stergere();
void cautare();
void actualizare();
void citire_din_fisier();
void salvare_in_fisier();

const char *nume_fisier = "angajat.txt";


#define RESET_COLOR   "\033[0m"
#define RED_COLOR     "\033[31m"
#define GREEN_COLOR   "\033[32m"
#define YELLOW_COLOR  "\033[33m"
#define CYAN_COLOR    "\033[36m"

void afisare_meniu() {
    printf(GREEN_COLOR "  Meniu principal  \n" RESET_COLOR);
    printf("1. Adaugare angajat\n");
    printf("2. Afisare angajati\n");
    printf("3. Stergere angajat\n");
    printf("4. Cautare angajat\n");
    printf("5. Actualizare angajat\n");
    printf("6. Iesire\n");
}

void alegere_optiune() {
    citire_din_fisier();

    int optiune;

    do {
        system("cls");
        afisare_meniu();
        printf(CYAN_COLOR "Introdu optiune (1-6): " RESET_COLOR);
        scanf("%d", &optiune);
        getchar();

        switch(optiune) {
            case 1:
                adaugare();
                break;
            case 2:
                afisare();
                break;
            case 3:
                stergere();
                break;
            case 4:
                cautare();
                break;
            case 5:
                actualizare();
                break;
            case 6:
                printf(RED_COLOR "La revedere!\n" RESET_COLOR);
                break;
            default:
                printf(RED_COLOR "Optiune invalida. Va rugam alegeti o optiune valida.\n" RESET_COLOR);
        }

        if (optiune != 6) {
            printf(CYAN_COLOR "Apasati Enter pentru a continua...\n" RESET_COLOR);
            getchar();
        }

    } while (optiune != 6);

    salvare_in_fisier();
}

void citire_din_fisier() {
    FILE *f = fopen(nume_fisier, "r");
    if (f == NULL) {
        printf(RED_COLOR "Nu s-a putut deschide fisierul pentru citire!\n" RESET_COLOR);
        return;
    }

    printf(CYAN_COLOR "Citire din fisier: %s\n" RESET_COLOR, nume_fisier);


    while (fscanf(f, "%99[^,],%99[^,],%99[^,],%10[^,],%13[^,],%f\n",
                   angajati[nrangajati].nume,
                   angajati[nrangajati].adresa,
                   angajati[nrangajati].post,
                   angajati[nrangajati].dataangajare,
                   angajati[nrangajati].cnp,
                   &angajati[nrangajati].salar) == 6) {
        printf(CYAN_COLOR "Am citit angajat: %s\n" RESET_COLOR, angajati[nrangajati].nume);
        nrangajati++;
    }

    if (nrangajati == 0) {
        printf(RED_COLOR "Nu s-au citit angajați din fișier.\n" RESET_COLOR);
    }

    fclose(f);
}
void salvare_in_fisier() {
    FILE *f = fopen(nume_fisier, "w");
    if (f == NULL) {
        printf(RED_COLOR "Nu s-a putut deschide fisierul pentru scriere!\n" RESET_COLOR);
        return;
    }

    for (int i = 0; i < nrangajati; i++) {
        fprintf(f, "%s,%s,%s,%s,%s,%.2f\n",
                angajati[i].nume,
                angajati[i].adresa,
                angajati[i].post,
                angajati[i].dataangajare,
                angajati[i].cnp,
                angajati[i].salar);
    }

    fclose(f);
}

int validare_dataangajare(const char *data) {
    int zi, luna, an;
    if (sscanf(data, "%d.%d.%d", &zi, &luna, &an) != 3) {
        return 0;
    }
    if (luna < 1 || luna > 12) {
        return 0;
    }
    return 1;
}

int validare_cnp(const char *cnp) {
    if (strlen(cnp) != 13) return 0;
    for (int i = 0; i < 13; i++) {
        if (!isdigit(cnp[i])) return 0;
    }
    return 1;
}

int validare_salar(float salar) {
    return salar > 0;
}

void adaugare() {
    system("cls");
    printf(GREEN_COLOR "  Adaugare angajat  \n" RESET_COLOR);

    if (nrangajati >= 100) {
        printf(RED_COLOR "Limita de angajati a fost atinsa.\n" RESET_COLOR);
        return;
    }

    angajat nou;

    printf(YELLOW_COLOR "Nume: " RESET_COLOR);
    fgets(nou.nume, sizeof(nou.nume), stdin);
    nou.nume[strcspn(nou.nume, "\n")] = 0;

    printf(YELLOW_COLOR "Adresa: " RESET_COLOR);
    fgets(nou.adresa, sizeof(nou.adresa), stdin);
    nou.adresa[strcspn(nou.adresa, "\n")] = 0;

    printf(YELLOW_COLOR "Post: " RESET_COLOR);
    fgets(nou.post, sizeof(nou.post), stdin);
    nou.post[strcspn(nou.post, "\n")] = 0;

    do {
        printf(YELLOW_COLOR "Data angajare (DD.MM.YYYY): " RESET_COLOR);
        fgets(nou.dataangajare, sizeof(nou.dataangajare), stdin);
        nou.dataangajare[strcspn(nou.dataangajare, "\n")] = 0;
        if (!validare_dataangajare(nou.dataangajare)) {
            printf(RED_COLOR "Data nu este valida. Formatul corect este DD.MM.YYYY.\n" RESET_COLOR);
        }
    } while (!validare_dataangajare(nou.dataangajare));

    do {
        printf(YELLOW_COLOR "Salariu: " RESET_COLOR);
        scanf("%f", &nou.salar);
        getchar();
        if (!validare_salar(nou.salar)) {
            printf(RED_COLOR "Salariul trebuie sa fie un numar pozitiv!\n" RESET_COLOR);
        }
    } while (!validare_salar(nou.salar));

    do {
        printf(YELLOW_COLOR "CNP: " RESET_COLOR);
        fgets(nou.cnp, sizeof(nou.cnp), stdin);
        nou.cnp[strcspn(nou.cnp, "\n")] = 0;
        if (!validare_cnp(nou.cnp)) {
            printf(RED_COLOR "CNP-ul nu este valid. Trebuie sa fie exact 13 caractere numerice.\n" RESET_COLOR);
        }
    } while (!validare_cnp(nou.cnp));

    angajati[nrangajati] = nou;
    nrangajati++;
    salvare_in_fisier();

    printf(GREEN_COLOR "Angajatul a fost adaugat cu succes.\n" RESET_COLOR);
    getchar();
}

void afisare() {
    system("cls");
    if (nrangajati == 0) {
        printf(RED_COLOR "Nu exista angajati.\n" RESET_COLOR);
        return;
    }

    printf(GREEN_COLOR "Lista angajati:\n" RESET_COLOR);
    for (int i = 0; i < nrangajati; i++) {
        printf("Angajat %d:\n", i + 1);
        printf("Nume: %s\n", angajati[i].nume);
        printf("Adresa: %s\n", angajati[i].adresa);
        printf("Post: %s\n", angajati[i].post);
        printf("Data angajare: %s\n", angajati[i].dataangajare);
        printf("CNP: %s\n", angajati[i].cnp);
        printf("Salariu: %.2f\n\n", angajati[i].salar);
    }
}

void stergere() {
    system("cls");
    printf(GREEN_COLOR "  Stergere angajat  \n" RESET_COLOR);
    char nume[100];
    int gasit = 0;

    printf(YELLOW_COLOR "Introduceti numele angajatului de sters: " RESET_COLOR);
    fgets(nume, sizeof(nume), stdin);
    nume[strcspn(nume, "\n")] = 0;

    for (int i = 0; i < nrangajati; i++) {
        if (strcmp(angajati[i].nume, nume) == 0) {
            gasit = 1;
            for (int j = i; j < nrangajati - 1; j++) {
                angajati[j] = angajati[j + 1];
            }
            nrangajati--;
            printf(GREEN_COLOR "Angajatul %s a fost sters.\n" RESET_COLOR, nume);
            break;
        }
    }

    if (!gasit) {
        printf(RED_COLOR "Angajatul cu numele %s nu a fost gasit.\n" RESET_COLOR, nume);
    }

    salvare_in_fisier();
}

void cautare() {
    system("cls");
    printf(GREEN_COLOR "  Cautare angajat  \n" RESET_COLOR);
    char nume[100], post[100];
    int gasit = 0, potriviren, potrivirep;

    printf(YELLOW_COLOR "Introduceti numele angajatului de cautat(sau dati enter pentru a sari la post): " RESET_COLOR);
    fgets(nume, sizeof(nume), stdin);
    nume[strcspn(nume, "\n")] = 0;
    printf(YELLOW_COLOR "Introduceti postul angajatului de cautat: " RESET_COLOR);
    fgets(post, sizeof(post), stdin);
    post[strcspn(post, "\n")] = 0;

    for (int i = 0; i < nrangajati; i++) {
        potriviren = (strlen(nume) == 0 || strcmp(angajati[i].nume, nume) == 0);
        potrivirep = (strlen(post) == 0 || strcmp(angajati[i].post, post) == 0);

        if (potriviren && potrivirep) {
            gasit = 1;
            printf(GREEN_COLOR "Angajat gasit:\n" RESET_COLOR);
            printf("Nume: %s\n", angajati[i].nume);
            printf("Adresa: %s\n", angajati[i].adresa);
            printf("CNP: %s\n", angajati[i].cnp);
            printf("Post: %s\n", angajati[i].post);
            printf("Data angajare: %s\n", angajati[i].dataangajare);
            printf("Salariu: %.2f\n\n", angajati[i].salar);
        }
    }

    if (!gasit) {
        printf(RED_COLOR "Nu au fost gasiti angajati care corespund criteriilor.\n" RESET_COLOR);
    }

    printf(CYAN_COLOR "Pentru a continua, apasa Enter...\n" RESET_COLOR);
    getchar();
}

void actualizare() {
    system("cls");
    printf(GREEN_COLOR "  Actualizare angajat  \n" RESET_COLOR);
    char nume[100];
    int gasit = 0;

    printf(YELLOW_COLOR "Introduceti numele angajatului de actualizat: " RESET_COLOR);
    fgets(nume, sizeof(nume), stdin);
    nume[strcspn(nume, "\n")] = 0;

    for (int i = 0; i < nrangajati; i++) {
        if (strcmp(angajati[i].nume, nume) == 0) {
            gasit = 1;
            printf(YELLOW_COLOR "Introduceti noile detalii pentru angajatul %s:\n" RESET_COLOR, nume);
            printf("Nume: ");
            fgets(angajati[i].nume, sizeof(angajati[i].nume), stdin);
            angajati[i].nume[strcspn(angajati[i].nume, "\n")] = 0;

            printf("Adresa: ");
            fgets(angajati[i].adresa, sizeof(angajati[i].adresa), stdin);
            angajati[i].adresa[strcspn(angajati[i].adresa, "\n")] = 0;

            printf("Post: ");
            fgets(angajati[i].post, sizeof(angajati[i].post), stdin);
            angajati[i].post[strcspn(angajati[i].post, "\n")] = 0;

            printf("Data angajare: ");
            fgets(angajati[i].dataangajare, sizeof(angajati[i].dataangajare), stdin);
            angajati[i].dataangajare[strcspn(angajati[i].dataangajare, "\n")] = 0;

            printf("Salariu: ");
            scanf("%f", &angajati[i].salar);
            getchar();
            printf("CNP: ");
            fgets(angajati[i].cnp, sizeof(angajati[i].cnp), stdin);
            angajati[i].cnp[strcspn(angajati[i].cnp, "\n")] = 0;
            getchar();
            printf(GREEN_COLOR "Angajatul a fost actualizat cu succes.\n" RESET_COLOR);
            break;
        }
    }

    if (!gasit) {
        printf(RED_COLOR "Angajatul cu numele %s nu a fost gasit.\n" RESET_COLOR, nume);
    }

    salvare_in_fisier();
}

int main() {
    alegere_optiune();
    return 0;
}
