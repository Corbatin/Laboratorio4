
// Nombres: Alvaro Soto Albornoz - Benjamín Melis Guerra
// Nombre Profesora: Nicolas Thériault
// IDE: Visual Studio Code 1.62.3
// SO: Windows 10
// Fecha: [REDACTED] de Enero - 2021
// Este programa genera dos matrices de un orden dado por el usuario y realiza multiplicaciones con dos algoritmos distintos, el algoritmo clasico y la multiplicacion de Strassen

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NMAX 10000000

typedef struct punto
{
    long x;
    long y;
    //struct punto *sig;
} punto;

void generar_archivo(void);
punto *leer_archivo(int *dim);
void imprimir_puntos(punto *lista, int largo);
void menu();
void merge_sort(punto *lista, int inicio, int final, int opcion);
void merge(punto *lista, int inicio, int medio, int final, int opcion);
void lista_enlazada(punto *lista, int inicio, int final, int opcion);
void sublistado(punto *lista, int largo, int coti_x, int coti_y, int cots_x, int cots_y);

int main()
{
    clock_t Tiempo_1, Tiempo_2;
    punto *p1;
    // p1 = calloc(10, sizeof(punto));
    // for (int i = 0; i < 10; i++)
    // {
    //     p1[i].x = i;
    //     p1[i].y = i + 1;
    // }
    // imprimir_puntos(p1, 10);
    // p1 = calloc(10, sizeof(punto));
    // for (int i = 0; i < 10; i++)
    // {
    //     p1[i].x = rand() % (21);
    //     p1[i].y = rand() % (21);
    // }
    // printf("\nPuntos Iniciales: \n");
    // imprimir_puntos(p1, 10);
    // merge_sort(p1, 0, 9, 2);
    // printf("\nPuntos ordenados: \n");
    // imprimir_puntos(p1, 10);
    menu();
    // generar_archivo();

    return 0;
}

void imprimir_puntos(punto *lista, int largo)
{
    for (int i = 0; i < largo; i++)
    {
        printf("\nPunto %i : %ld %ld", i + 1, lista[i].x, lista[i].y);
    }
}

void menu()
{
    int op, el, largo, coti_x, coti_y, cots_x, cots_y;
    punto *lista;
    char m;

    // printf("\n Inserte el largo de la lista: ");
    // scanf("%i",&largo);
    // lista = calloc(largo,sizeof(punto));
    // for (int i = 0; i < largo; i++)
    // {
    //     lista[i].x = rand() % (NMAX);
    //     lista[i].y = rand() % (NMAX);
    // }
    do
    {
        printf("\nQue desea hacer? ");
        printf("\n 1)Generar archivo con puntos.");
        printf("\n 2)Leer archivo con puntos.");
        printf("\n 3)Ordenar los puntos segun el valor de sus coordenadas x (S/N)");
        printf("\n 4)Ordenar los puntos segun el valor de sus coordenadas y (S/N)");
        printf("\n 5)Sub listado con cotas: ");
        printf("\n 0)Salir del programa.");
        printf("\n Opcion: ");
        scanf("%i", &op);
        switch (op)
        {
        case 1:
            generar_archivo();
            printf("\nDesea ver tiempo? (s/n)");
            scanf("%c", &m);
            break;
        case 2:
            lista = leer_archivo(&largo);
            printf("\nDesea ver tiempo? (s/n)");
            scanf("%c", &m);
            break;
        case 3:
            printf("\nPuntos Iniciales: \n");
            imprimir_puntos(lista, largo);
            merge_sort(lista, 0, largo - 1, 1); // arreglo,0,largo-1,opcion 1 = x, otra = y
            printf("\nPuntos ordenados en X: \n");
            imprimir_puntos(lista, largo);
            // printf("\nDesea ver tiempo? (s/n)");
            // scanf("%c", &m);
            break;
        case 4:
            printf("\nPuntos Iniciales: \n");
            imprimir_puntos(lista, largo);
            merge_sort(lista, 0, largo - 1, 2);
            printf("\nPuntos ordenados en Y: \n");
            imprimir_puntos(lista, largo);
            // printf("\nDesea ver tiempo? (s/n)");
            // scanf("%c", &m);
            break;
        case 5:
            merge_sort(lista,0 ,largo - 1, 1);
            printf("\nIngrese cota inferior de X: ");
            scanf("%i", &coti_x);
            printf("\nIngrese cota inferior de Y: ");
            scanf("%i", &coti_y);
            printf("\nIngrese cota superior de X: ");
            scanf("%i", &cots_x);
            printf("\nIngrese cota superior de Y: ");
            scanf("%i", &cots_y);
            sublistado(lista, largo, coti_x, coti_y, cots_x, cots_y);

            break;
        case 0:
            break;
        default:
            break;
        }
    } while (op);
    free(lista);
}

void generar_archivo(void)
{
    srand(clock());
    long a;
    int n;
    long i;
    FILE *archivo;
    char nombre_archivo[30];
    printf("Ingresar nombre de archivo: ");
    scanf("%s", nombre_archivo);

    while (getchar() != '\n')
        ;
    archivo = fopen(nombre_archivo, "w");
    printf("Ingresar la cantidad de puntos: ");
    scanf("%d", &n);
    fprintf(archivo, "%d \n", n);
    for (i = 0; i < n; i++)
    {
        a = rand() % NMAX;
        fprintf(archivo, "%ld ", a);
        a = rand() % NMAX;
        fprintf(archivo, "%ld ", a);
        fprintf(archivo, "\n");
    }
    fclose(archivo);
    printf("El archivo esta listo.\n");
}

punto *leer_archivo(int *dim)
{
    punto *p1;
    long largo;
    int i;
    FILE *archivo;
    char nombre_archivo[30];
    printf("\nIngrese el nombre del archivo\n ");
    scanf("%s", &nombre_archivo);
    if (!nombre_archivo)
    {
        printf("\nSaliendo del programa\n");
        exit(0);
    }
    printf("\nEscanee el nombre %s\n", nombre_archivo);
    archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL)
    {
        printf("\nSaliendo del programa\n");
        exit(1);
    }
    fread(p1, sizeof(long), largo, archivo);
    fscanf(archivo, "%i", &largo);
    p1 = calloc(largo, sizeof(punto));
    *dim = largo;
    i = 0;
    while (i < largo)
    {
        fscanf(archivo, "%ld %ld", &p1[i].x, &p1[i].y);
        i++;
    }
    fclose(archivo);
    return p1;
}

void merge_sort(punto *lista, int inicio, int final, int opcion)
{
    if (inicio < final)
    {
        int medio = inicio + (final - inicio) / 2;

        merge_sort(lista, inicio, medio, opcion);
        merge_sort(lista, medio + 1, final, opcion);

        merge(lista, inicio, medio, final, opcion);
    }
}

void merge(punto *lista, int inicio, int medio, int final, int opcion)
{
    punto *aux1, *aux2;
    int largo1, largo2, i, j, k;
    largo1 = medio - inicio + 1;
    largo2 = final - medio;

    aux1 = calloc(largo1, sizeof(punto));
    aux2 = calloc(largo2, sizeof(punto));

    for (i = 0; i < largo1; i++)
    {
        aux1[i] = lista[inicio + i];
    }
    for (j = 0; j < largo2; j++)
    {
        aux2[j] = lista[medio + j + 1];
    }
    i = 0;
    j = 0;
    k = inicio;
    if (opcion == 1)
    {
        while (i < largo1 && j < largo2)
        {
            if (aux1[i].x <= aux2[j].x)
            {
                lista[k] = aux1[i];
                i++;
            }
            else
            {
                lista[k] = aux2[j];
                j++;
            }
            k++;
        }
        while (i < largo1)
        {
            lista[k] = aux1[i];
            i++;
            k++;
        }
        while (j < largo2)
        {
            lista[k] = aux2[j];
            j++;
            k++;
        }
    }
    else
        while (i < largo1 && j < largo2)
        {
            if (aux1[i].y <= aux2[j].y)
            {
                lista[k] = aux1[i];
                i++;
            }
            else
            {
                lista[k] = aux2[j];
                j++;
            }
            k++;
        }
    while (i < largo1)
    {
        lista[k] = aux1[i];
        i++;
        k++;
    }
    while (j < largo2)
    {
        lista[k] = aux2[j];
        j++;
        k++;
    }
}

void lista_enlazada(punto *lista, int inicio, int final, int opcion)
{
    
}

void sublistado(punto *lista, int largo, int coti_x, int coti_y, int cots_x, int cots_y)
{
    punto *sub_lista; //calloc(largo)
    sub_lista=calloc(largo,sizeof(punto));
    int cont = 0;
    for (int i = 0; i < largo; i++)
    {
        if(lista[i].x > cots_x)
            break;
        if (lista[i].x >= coti_x && lista[i].x <= cots_x && lista[i].y >= coti_y && lista[i].y <= cots_y)
        {
            sub_lista[cont] = lista[i];
            cont++;
        }
    }
    imprimir_puntos(sub_lista,cont);
}