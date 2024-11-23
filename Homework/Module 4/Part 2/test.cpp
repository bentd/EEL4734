#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    char *a = NULL;
    char *c = NULL;
    char *b = NULL;
    char *d = NULL;
    char *e = NULL;

    int i = 1;

    while (i < argc)
    {
        if (strcmp(argv[i], "-a") == 0 && i + 1 < argc)
        {
            a = argv[++i];
        }
        else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc)
        {
            b = argv[++i];
        }
        else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
        {
            c = argv[++i];
        }
        else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc)
        {
            d = argv[++i];
        }
        else if (strcmp(argv[i], "-e") == 0 && i + 1 < argc)
        {
            e = argv[++i];
        }
        i++;
    }

    if (a != NULL)
        cout << a << " ";

    if (b != NULL)
        cout << b << " ";

    if (c != NULL)
        cout << c << " ";

    if (d != NULL)
        cout << d << " ";

    if (e != NULL)
        cout << e;

    cout << endl;

    return 0;
}