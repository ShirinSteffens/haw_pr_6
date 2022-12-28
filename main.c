
//Preprozessorkommandos
// Sicherheitswarnungnen vermeiden
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
// toupper()
#include <string.h>
// isalpha()
#include <ctype.h>
#include <stdbool.h>

#define TASK 3

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
    // Vier argumente sind erforderlich
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

    // fgetc liest einen Buchstaben und speichert diesen in ch
    // danach überprüft er ob der Buchstabe EndofFile ist, falls nein wird der Buchstabe verschlüsselt
    while ((ch = fgetc(input)) != EOF)
    {
        // ch wird verschlüsselt
        char encrypted_char = encrypt(ch, shift);
        // verschlüsselter Buchstabe wird in Output geschrieben
        fputc(encrypted_char, output);
    }

    fclose(input);
    fclose(output);

    printf("Datei wurde verschlüsselt.\n");

    return 0;
}
#elif TASK == 3
// Funktion zum Suchen eines bestimmten Werts in einem int-Vektor
int *find_int(int value, int* vec, int vec_len);

int main()
{
    // Beispielvektor mit int-Elementen
    int vec[] = {1, 2, 3, 4, 5, 1, 2, 3};
    // Dadurch brechenen wir 8
    int vec_len = sizeof(vec) / sizeof(vec[0]);

    // Elemente des Vektors anzeigen
    printf("Elements of the vector: ");
    for (int i = 0; i < vec_len; i++)
    {
        printf("%d ", vec[i]);
    }
    printf("\n");

    // Anwender zur Eingabe eines Werts auffordern
    int value;
    bool repeat = true;

    do
    {
        // Frage Zahl vom User ab
        printf("Enter a value to search for: ");
        int ret_val = scanf("%d", &value);

        if (ret_val != 1)
        {
            printf("Bitte eine Zahl eingeben.\n");
            exit(EXIT_FAILURE);
        }

        // Aufruf von find_int(), um die Positionen des Werts im Vektor zu finden
        int *pos = find_int(value, vec, vec_len);

        // Falls gefunden, dann ist pos ein pointer
        // Falls nicht, dann ist pos NULL
        while (pos != NULL)
        {
            // Wenn der Wert gefunden wurde, die Position anzeigen und weitersuchen
            printf("Value found at position %ld at address: %p\n", pos - vec + 1, pos);

            // Gehe zum nächsten Wert im Array
            pos++;

            // Rufe find_int erneut auf mit restlichem Array
            int size_of_remaining_array =  vec_len - (pos - vec);
            pos = find_int(value, pos, size_of_remaining_array);
        }

        char user_input = '\0';
        printf("Search again? [y/n] ");

        // Clear input buffer
        char buffer[1024];
        fgets(buffer, sizeof(buffer), stdin);

        int ret_val_2 = scanf("%c", &user_input);
        printf("%c\n", user_input);

        if (user_input == 'y')
        {
            repeat = true;
        }
        else
        {
            repeat = false;
        }
    } while (repeat);

    return 0;
}

// Funktion zum Suchen eines bestimmten Werts in einem int-Vektor
int *find_int(int value, int* vec, int vec_len)
{
    // Iterieren Sie durch jedes Element des Vektors
    for (int i = 0; i < vec_len; i++)
    {
        // Wenn das aktuelle Element dem gesuchten Wert entspricht,
        // gib den Zeiger auf das Element zurück
        if (vec[i] == value)
        {
            return &vec[i];
        }
    }

    // Wenn der Wert nicht gefunden wurde, gib NULL zurück
    return NULL;
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
        // https://ascii50.firebaseapp.com/
        ch = ((ch - 'A') + shift) % ALPHABET_SIZE + 'A';
    }

    return ch;
}
//😜😈😈😈😈