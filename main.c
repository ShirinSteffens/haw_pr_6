// Sicherheitswarnungnen vermeiden
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TASK 1

#define ALPHABET_SIZE 26
#define MIN_SHIFT 1
#define MAX_SHIFT 25

// Funktionen deklarieren
char encrypt(char ch, int shift);

#if TASK == 1
int main(int argc, char* argv[])
{

    //  Aufgabe 1:

    //Ausgabe der Parameter
    for (int i = 0; i < argc; i++)
    {
        printf("Parameter %d: \"%s\"\n", i, argv[i]);
    }

    if (argc != 4)
    {
        printf("Falsche Anzahl von Argumenten!\n");
        printf("Aufruf: %s <Eingabedateiname> <Ausgabedateiname> <Verschiebung>\n", argv[0]);
        return 1;
    }

    // Wandelt den Verschiebungswert in eine ganze Zahl um
    int shift = atoi(argv[3]);
    if (shift < MIN_SHIFT || shift > MAX_SHIFT)
    {
        printf("Ungültiger Verschiebungswert! Erlaubte Werte sind 1 bis 25.\n");
        return 1;
    }

    // Öffnet die Eingabedatei im Lesemodus
    FILE* input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Kann Eingabedatei %s nicht öffnen!\n", argv[1]);
        return 1;
    }

    // Öffnet die Ausgabedatei im Schreibmodus
    FILE* output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Kann Ausgabedatei %s nicht öffnen!\n", argv[2]);
        fclose(input);
        return 1;
    }

    // Liest die Eingabedatei Zeile für Zeile und schreibt die verschlüsselten Zeichen in die Ausgabedatei
    char ch;
    while ((ch = fgetc(input)) != EOF);

    return 0;
}
#elif TASK == 2
int main(int argc, char const *argv[])
{
    return 0;
}
#elif TASK == 3
int main(int argc, char const *argv[])
{
    return 0;
}
#endif

// Verschlüsselt oder entschlüsselt ein gegebenes Zeichen nach dem Cäsar-Verschlüsselungsverfahren
// und gibt das resultierende Zeichen zurück. Wenn das Zeichen kein Buchstabe ist, wird es unverändert
// zurückgegeben.
char encrypt(char ch, int shift)
{
    if (isalpha(ch))
    {
        // Wandelt Kleinbuchstaben in Großbuchstaben um
        ch = toupper(ch);

        // Verschiebt das Zeichen um den angegebenen Wert
        ch = ((ch - 'A') + shift) % ALPHABET_SIZE + 'A';
    }
    return ch;
}
//😜😈😈😈😈