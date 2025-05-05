#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RESET_COLOR   "\033[0m"
#define RED_COLOR     "\033[31m"
#define GREEN_COLOR   "\033[32m"
#define YELLOW_COLOR  "\033[33m"
#define BLUE_COLOR    "\033[34m"
#define MAGENTA_COLOR "\033[35m"
#define CYAN_COLOR    "\033[36m"

typedef struct {
    char nume[100], adresa[100], post[100], dataangajare[11], cnp[14];
    float salar;
} angajat;

angajat angajati[100];
int nrangajati = 0;

const char *nume_fisier = "angajat.txt";

void afisare_meniu();
void alegere_optiune();
void adaugare();
void afisare();
void stergere();
void cautare();
void actualizare();
void citire_din_fisier();
void salvare_in_fisier();

void afisare_meniu() {
    printf(RED_COLOR "Bine " GREEN_COLOR "ati " BLUE_COLOR "venit " MAGENTA_COLOR "in " CYAN_COLOR "Meniu " YELLOW_COLOR "principal\n" RESET_COLOR);
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
            case 1: adaugare(); break;
            case 2: afisare(); break;
            case 3: stergere(); break;
            case 4: cautare(); break;
            case 5: actualizare(); break;
            case 6:
                printf(RED_COLOR "La " YELLOW_COLOR "revedere! " GREEN_COLOR "Multumim " CYAN_COLOR "pentru " MAGENTA_COLOR "utilizare.\n" RESET_COLOR);
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
    while (fscanf(f, "%99[^,],%99[^,],%99[^,],%10[^,],%13[^,],%f\n",
        angajati[nrangajati].nume,
        angajati[nrangajati].adresa,
        angajati[nrangajati].post,
        angajati[nrangajati].dataangajare,
        angajati[nrangajati].cnp,
        &angajati[nrangajati].salar) == 6) {
        nrangajati++;
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
    if (sscanf(data, "%d.%d.%d", &zi, &luna, &an) != 3) return 0;
    if (luna < 1 || luna > 12) return 0;
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
    angajat nou;
    if (nrangajati >= 100) {
        printf(RED_COLOR "Limita de angajati a fost atinsa.\n" RESET_COLOR);
        return;
    }
    printf(YELLOW_COLOR "Nume si Prenume: " RESET_COLOR);
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
        if (!validare_dataangajare(nou.dataangajare))
            printf(RED_COLOR "Data invalida. Formatul corect este DD.MM.YYYY.\n" RESET_COLOR);
    } while (!validare_dataangajare(nou.dataangajare));

    do {
        printf(YELLOW_COLOR "Salariu: " RESET_COLOR);
        scanf("%f", &nou.salar);
        getchar();
        if (!validare_salar(nou.salar))
            printf(RED_COLOR "Salariul trebuie sa fie pozitiv!\n" RESET_COLOR);
    } while (!validare_salar(nou.salar));

    do {
        printf(YELLOW_COLOR "CNP: " RESET_COLOR);
        fgets(nou.cnp, sizeof(nou.cnp), stdin);
        nou.cnp[strcspn(nou.cnp, "\n")] = 0;
        if (!validare_cnp(nou.cnp))
            printf(RED_COLOR "CNP-ul " YELLOW_COLOR "nu " GREEN_COLOR "este " CYAN_COLOR "valid. " MAGENTA_COLOR "Trebuie " BLUE_COLOR "13 " RED_COLOR "cifre.\n" RESET_COLOR);
    } while (!validare_cnp(nou.cnp));

    angajati[nrangajati++] = nou;
    salvare_in_fisier();
    printf(GREEN_COLOR "Angajatul " CYAN_COLOR "a " YELLOW_COLOR "fost " BLUE_COLOR "adaugat " MAGENTA_COLOR "cu " RED_COLOR "succes.\n" RESET_COLOR);
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
        printf("Nume si Prenume: %s\n", angajati[i].nume);
        printf("Adresa: %s\n", angajati[i].adresa);
        printf("Post: %s\n", angajati[i].post);
        printf("Data angajare: %s\n", angajati[i].dataangajare);
        printf("CNP: %s\n", angajati[i].cnp);
        printf("Salariu: %.2f\n\n", angajati[i].salar);
    }
}

void stergere() {
    system("cls");
    char nume[100];
    int gasit = 0;
    printf(YELLOW_COLOR "Introduceti numele si prenumele angajatului de sters: " RESET_COLOR);
    fgets(nume, sizeof(nume), stdin);
    nume[strcspn(nume, "\n")] = 0;

    for (int i = 0; i < nrangajati; i++) {
        if (strcmp(angajati[i].nume, nume) == 0) {
            for (int j = i; j < nrangajati - 1; j++) angajati[j] = angajati[j + 1];
            nrangajati--;
            gasit = 1;
            printf(GREEN_COLOR "Angajatul %s a fost sters.\n" RESET_COLOR, nume);
            break;
        }
    }
    if (!gasit)
        printf(RED_COLOR "Angajatul %s nu a fost gasit.\n" RESET_COLOR, nume);
    salvare_in_fisier();
}

void cautare() {
    system("cls");
    char nume[100], post[100];
    int gasit = 0;
    printf(YELLOW_COLOR "Introduceti numele si prenumele (Enter pt a sari): " RESET_COLOR);
    fgets(nume, sizeof(nume), stdin);
    nume[strcspn(nume, "\n")] = 0;
    printf(YELLOW_COLOR "Introduceti postul: " RESET_COLOR);
    fgets(post, sizeof(post), stdin);
    post[strcspn(post, "\n")] = 0;

    for (int i = 0; i < nrangajati; i++) {
        if ((strlen(nume) == 0 || strcmp(nume, angajati[i].nume) == 0) &&
            (strlen(post) == 0 || strcmp(post, angajati[i].post) == 0)) {
            printf(GREEN_COLOR "Angajat gasit:\n" RESET_COLOR);
            printf("Nume si Prenume: %s\nAdresa: %s\nCNP: %s\nPost: %s\nData: %s\nSalariu: %.2f\n\n",
                angajati[i].nume, angajati[i].adresa, angajati[i].cnp,
                angajati[i].post, angajati[i].dataangajare, angajati[i].salar);
            gasit = 1;
        }
    }
    if (!gasit) printf(RED_COLOR "Niciun angajat nu corespunde.\n" RESET_COLOR);
    printf(CYAN_COLOR "Apasa Enter pentru a continua...\n" RESET_COLOR);
    getchar();
}

void actualizare() {
    system("cls");
    char nume[100];
    int gasit = 0;
    printf(YELLOW_COLOR "Introduceti numele angajatului de actualizat: " RESET_COLOR);
    fgets(nume, sizeof(nume), stdin);
    nume[strcspn(nume, "\n")] = 0;

    for (int i = 0; i < nrangajati; i++) {
        if (strcmp(angajati[i].nume, nume) == 0) {
            gasit = 1;
            printf("Nume si Prenume: ");
            fgets(angajati[i].nume, 100, stdin);
            angajati[i].nume[strcspn(angajati[i].nume, "\n")] = 0;
            printf("Adresa: ");
            fgets(angajati[i].adresa, 100, stdin);
            angajati[i].adresa[strcspn(angajati[i].adresa, "\n")] = 0;
            printf("Post: ");
            fgets(angajati[i].post, 100, stdin);
            angajati[i].post[strcspn(angajati[i].post, "\n")] = 0;
            printf("Data: ");
            fgets(angajati[i].dataangajare, 11, stdin);
            angajati[i].dataangajare[strcspn(angajati[i].dataangajare, "\n")] = 0;
            printf("Salariu: ");
            scanf("%f", &angajati[i].salar); getchar();
            printf("CNP: ");
            fgets(angajati[i].cnp, 14, stdin);
            angajati[i].cnp[strcspn(angajati[i].cnp, "\n")] = 0;
            printf(GREEN_COLOR "Actualizare realizata cu succes.\n" RESET_COLOR);
            break;
        }
    }
    if (!gasit)
        printf(RED_COLOR "Angajatul %s nu a fost gasit.\n" RESET_COLOR, nume);
    salvare_in_fisier();
}

int main() {
    alegere_optiune();
    return 0;
}
