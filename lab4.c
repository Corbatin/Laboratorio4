
// Nombres: Alvaro Soto Albornoz - Benjamín Melis Guerra
// Nombre Profesora: Nicolas Thériault
// IDE: Visual Studio Code 1.63.2
// SO: Windows 10
// Fecha: [REDACTED] de Enero - 2021
// Este programa genera y lee archivos con coordenadas  y las ordena segun x o y mediante el algoritmo de mergesort. A

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NMAX 10000000

// Estructura punte creada para tener coordenadas X y Y juntas
typedef struct punto
{
    long x;
    long y;
} punto;

void generar_archivo(void);                                                                            // Genera archivo con coordendas (X,Y)
punto *leer_archivo(int *dim);                                                                         // Leearchivo con coordendas (X,Y)
void imprimir_puntos(punto *lista, int largo);                                                         // Imprime las coordenadas de una lista
void menu();                                                                                           // Menu
void merge_sort(punto *lista, int inicio, int final, int opcion);                                      // Algoritmo de ordenamiento para listas
void merge(punto *lista, int inicio, int medio, int final, int opcion);                                // Complemento de Algoritmo mergesort. Junta las listas
punto *sublistado(punto *lista, int largo, int coti_x, int coti_y, int cots_x, int cots_y, int *cont); // Imprime un sub listado de coordenadas ordenadas

int main()
{
    menu();

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
    int op, el, largo, coti_x, coti_y, cots_x, cots_y, cont;
    punto *lista, *sublista;
    int m;
    clock_t tiempo_1, tiempo_2;
    do
    {
        printf("\n\nQue desea hacer? ");
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
            break;
        case 2:
            lista = leer_archivo(&largo);

            break;
        case 3:
            tiempo_1 = clock();
            merge_sort(lista, 0, largo - 1, 1); // arreglo,0,largo-1,opcion 1 = x, otra = y
            tiempo_2 = clock();
            printf("\nLista ordenada con exito. tiempo de ejecucion: %f \n", ((double)tiempo_2 - (double)tiempo_1) / ((double)CLOCKS_PER_SEC));
            printf("\nQuiere ver la lista ordenada? (1 = si / 2 = no): ");
            scanf("%i", &m);
            if (m == 1)
            {
                printf("\n\nImprimiendo puntos: \n");
                imprimir_puntos(lista, largo);
            }
            else if (m == 2)
                ;
            {
                break;
            }
            break;
        case 4:

            tiempo_1 = clock();
            merge_sort(lista, 0, largo - 1, 2);
            tiempo_2 = clock();
            printf("\nLista ordenada con exito. tiempo de ejecucion: %f \n", ((double)tiempo_2 - (double)tiempo_1) / ((double)CLOCKS_PER_SEC));
            printf("\nQuiere ver la lista ordenada? (1 = si / 2 = no): ");
            scanf("%i", &m);
            if (m == 1)
            {
                printf("\n\nImprimiendo puntos: \n");
                imprimir_puntos(lista, largo);
            }
            else if (m == 2)
                ;
            {
                break;
            }
            break;

        case 5:
            merge_sort(lista, 0, largo - 1, 1);
            printf("\nIngrese cota inferior de X: ");
            scanf("%i", &coti_x);
            printf("\nIngrese cota inferior de Y: ");
            scanf("%i", &coti_y);
            printf("\nIngrese cota superior de X: ");
            scanf("%i", &cots_x);
            printf("\nIngrese cota superior de Y: ");
            scanf("%i", &cots_y);

            tiempo_1 = clock();
            sublista = sublistado(lista, largo, coti_x, coti_y, cots_x, cots_y, &cont);
            tiempo_2 = clock();
            printf("\nLista ordenada con exito. tiempo de ejecucion: %f \n", ((double)tiempo_2 - (double)tiempo_1) / ((double)CLOCKS_PER_SEC));
            printf("\nQuiere ver la lista ordenada? (1 = si / 2 = no): ");
            scanf("%i", &m);
            if (m == 1)
            {
                printf("\n\nImprimiendo puntos: \n");
                imprimir_puntos(sublista, cont);
            }
            else if (m == 2)
                ;
            {
                break;
            }

            break;
        case 0:
            break;
        default:
            printf("\nOpcion Ingresada no valida\n");
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
    archivo = fopen(nombre_archivo, "r"); // abre el archivo para su lectura
    if (archivo == NULL)
    {
        printf("\nSaliendo del programa\n");
        exit(1);
    }
    fscanf(archivo, "%i", &largo);     // lee la cantidad de datos
    p1 = calloc(largo, sizeof(punto)); // Se aloca la memoria que se ocuparapara la lista de puntos
    *dim = largo;                      // Se ocupa dim para poder devolver la cantidad de datos
    i = 0;
    while (i < largo)
    {
        fscanf(archivo, "%ld %ld", &p1[i].x, &p1[i].y); // Lee cada punto con su X e Y
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

        merge_sort(lista, inicio, medio, opcion);    // Llama a la funcion mergesort desde el inicio a la mitad del arreglo
        merge_sort(lista, medio + 1, final, opcion); // Llama a la funcion mergesort desde la mitad + 1 al final del arreglo

        merge(lista, inicio, medio, final, opcion); // Une los dos sub arreglos
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
    if (opcion == 1) // La opcion 1 ordena los puntos por la coordenada X
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
    else // mientras que cualquier otra opcion ordena los puntos segun la coordenada Y
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
    free(aux1);
    free(aux2); // Se liberan los espacios de memoria alocados
}

punto *sublistado(punto *lista, int largo, int coti_x, int coti_y, int cots_x, int cots_y, int *cont)
{
    punto *sub_lista;
    sub_lista = calloc(largo, sizeof(punto));
    int contador = 0; // cont se usara para llevar la cuenta del subindice de sub-lista y tambien para tener su largo total
    for (int i = 0; i < largo; i++)
    {
        if (lista[i].x > cots_x) // La lista al estar ordenada por X, si un punto supera esa cota todo el resto tambien lo hara
            break;
        // Se comprueba que el punto dado este dentro de las cotas especificadas
        if (lista[i].x >= coti_x && lista[i].x <= cots_x && lista[i].y >= coti_y && lista[i].y <= cots_y)
        {
            // Se copia el punto de la lista a la sub-lista
            sub_lista[contador] = lista[i];
            contador++;
        }
    }
    *cont = contador; // devuelve el largo de la sub-lista
    return sub_lista;
}