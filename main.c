// Sicherheitswarnungnen vermeiden
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// toupper()
#include <ctype.h>

#define TASK 2

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

    return 0;
}
#elif TASK == 2
int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        printf("Falsche Anzahl von Argumenten!\n");
        printf("Aufruf: %s <Eingabedateiname> <Ausgabedateiname> <Verschiebung>\n", argv[0]);
        return 1;
    }

    // Wandelt den Verschiebungswert in eine ganze Zahl um; ascii zu int
    int shift = atoi(argv[3]);

    if (shift < MIN_SHIFT || shift > MAX_SHIFT)
    {
        printf("Ungültiger Verschiebungswert! Erlaubte Werte sind 1 bis 25.\n");

        // return 1 wie in der main aus stdlib
        exit(EXIT_FAILURE);
    }

    // Öffnet die Eingabedatei im Lesemodus
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Kann Eingabedatei %s nicht öffnen!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Öffnet die Ausgabedatei im Schreibmodus
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Kann Ausgabedatei %s nicht öffnen!\n", argv[2]);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    // Liest die Eingabedatei Zeile für Zeile und schreibt die verschlüsselten Zeichen in die Ausgabedatei
    char ch = '\0';

    while ((ch = fgetc(input)) != EOF)
    {
        char encrypted_char = encrypt(ch, shift);
        fputc(encrypted_char, output);
    }

    fclose(input);
    fclose(output);

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
        // Buchstaben in ch und zieht A ab (-65) und au die zB 6 (G) rechnen wird dann shift rauf und dann mod Alphabet
        // um zu "rotieren"  Z=26 + shift 5 = 31 -> kein Buchstabe, sollte aber 5 sein, dort kommen wird durch mod hin,
        // denn wir bekommen dann den Rest 5 zurück und gehen somit auf den folgenden Buchstaben zb E und + A um
        // auf den richtigen ascii Wert zu kommen
        ch = ((ch - 'A') + shift) % ALPHABET_SIZE + 'A';
    }

    return ch;
}
//😜😈😈😈😈