#define _CRT_SECURE_NO_WARNINGS
/*
Realizzare un programma in linguaggio C per registrare le cartoline scambiate tra un gruppo di amici
(massimo 20 amici).
L’elenco delle cartoline è memorizzato in un ﬁle di testo, composto da un numero imprecisato di linee,
 ciascuna delle quali contiene tre elementi: 
- il nome del mittente
- il nome del destinatario 
- il nome della località da cui la cartolina è stata inviata. 
I nomi degli amici e delle località sono da intendersi privi di spazi e lunghi al massimo 30 caratteri ciascuno.
Il programma riceve come primo parametro il nome del ﬁle di testo, mentre il
secondo parametro può essere la stringa new oppure la stringa find.
Il comando new richiede ulteriori tre parametri, corrispondenti ai nomi degli
amici e della località e deve aggiungere tali informazioni in coda al ﬁle. 
Il programma deve segnalare con un messaggio errore l’eventuale tentativo di re-introdurre una cartolina identica ad una già esistente.
Il comando find è invece seguito da un solo ulteriore parametro corrispondente
al nome di un amico. 
In questo caso il programma deve stampare l’elenco degli amici che hanno spedito cartoline all’amico speciﬁcato e le località corrispondenti.

*/

//  Preprocessore   //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define OFFSET 3

// Strutture dati   //
typedef struct
{
    char nomeMittente[30];
    char nomeDestinatario[30];
    char localitaMittente[30];
} Cartolina;

// main con parametri   //
int main(int argc, char *argv[])
{
    FILE *fp;
    Cartolina c[MAX];

    fp = fopen("cartoline.txt", "r+");
    if (fp == NULL)
    {
        printf("ERRORE apetura file!\n");
        system("pause");
        exit(1);
    }

    printf("FILE aperto '%s' \n", argv[1]);

    if (strcmp(argv[2], "new") == 0)
    {
        printf("\nCOMANDO --> new\nINSERIRE TRE NUOVE CARTOLINE:\n");
        for (int i = 0; i < OFFSET; i++)
        {
            printf("CARTOLINA N' %d: \n", i + 1);
            printf("Nome mittente: ");
            scanf("%s*%c", c[i].nomeMittente);
            printf("Nome destinatario: ");
            scanf("%s*%c", c[i].nomeDestinatario);
            printf("Nome localita' di partenza: ");
            scanf("%s*%c", c[i].localitaMittente);
            putchar('\n');

            // check elemeti doppi  //
            rewind(fp);
            Cartolina d;
            while (!feof(fp))
            {
                fscanf(fp, "%s %s %s", d.nomeMittente, d.nomeMittente, d.localitaMittente);
                if (strcmp(c[i].nomeMittente, d.nomeMittente) == 0 && strcmp(c[i].nomeDestinatario, d.nomeDestinatario) == 0 && strcmp(c[i].localitaMittente, d.localitaMittente) == 0)
                {
                    printf("Catolina gia' esistente! \n");
                    exit(1);
                }
            }

            //  aggiungo cartoline  //
            fseek(fp, 0, SEEK_END);
            fprintf(fp, "%s\t%s\t%s\n", c[i].nomeMittente, c[i].nomeDestinatario, c[i].localitaMittente);
        }
    }
    else if ((strcmp(argv[2], "find") == 0))
    {
        printf("%s\n", argv[3]);
        rewind(fp);
        while (!feof)
        {
            fscanf(fp, "%s %s %s", c[0].nomeMittente, c[0].nomeDestinatario, c[0].localitaMittente);
            if (strcmp(c[0].nomeDestinatario, argv[3]) == 0)
            {
                printf("\n LEttere inviate a %s : \n", argv[3]);
                printf("%s \n", c[0].nomeMittente);
            }
        }
    }

    fclose(fp);
    system("pause");
    return EXIT_SUCCESS;
}