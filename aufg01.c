#include <stdio.h>
#include <stdlib.h>
#include <math.h> //fuer die Sinusfunktion

/*a)Programm um Daten aus dataset1 einzulesen und auf dem Bildschrim auszugeben.
 dataset1 enthaehlt in 1. Zeile Integer der Laenge des Datensatzes (doubles) angibt
 
 b)eingelesene daten bearbeoiten und in neuem Array speichern
 
 c) Einlesen eines binaeren Datensatzes (1. Zeile mit Anzahl der Daten), speichern in einer Textdatei in Tabellenform(A,sin(A))*/

//Teil a:
//Daten in Array einlesen:
double *array_init(FILE *data, int N) {
    double *A = (double*)malloc(N*sizeof(double));  //Speicher allokieren fuer Array
    if(A == NULL) {
        printf("Speicher fuer Array konnte nicht allokiert werden.\n");
        exit(1);
    }
    for(int k=0; k<N; k++) {
        fscanf(data,"%le\n",&A[k]);
    }
    return A;
    }

//Array ausgeben:
void array_print(double *array, int N) {
    for(int k=0; k<N; k++) {
        printf("%le\n",array[k]);
    }
}

//Array freigeben:
void array_free(double *array) {
    free(array);
}


//Teil b: kumulative Quadratsumme der Daten berechnen und in neuem Array speichern
double* kumm_qusum(double *A, int N) {
    double *B = (double*)malloc(N*sizeof(double));  //Speicher allokieren
    if(B == NULL) {
        printf("Speicher konnte fuer das Array fuer die kummulative\
        Quadratsumme nicht allokiert werden\n");
        exit(1);
    }
    double sum = 0;
    for(int k=0; k<N; k++) {
        sum += (A[k]*A[k]);
        B[k] = sum;
    }
    return B;
}

//Teil c (erster Versuch):
//Funktion liest Binaerdaten in Array ein:
double *array_binaer(FILE *data, int N) {
    double *C = (double*)malloc(N * sizeof(double));    //Speicher allokieren
    if(C == NULL) {
        printf("Speicher zum einlesen der Binaerdatei konnte nicht\
        allokiert werden\n");
        exit(1);
    }
    for(int k=0; k<N; k++) {
        fread(&C[k], sizeof(double), 1, data);
    }
    return C;
}

/*Funktion berechnet Funktionswerte zu den eingelesenen Binaerdaten und speichert diese
in einem Array*/
double *array_sinus(double *C, int N) {
    double *C2 = (double*)malloc(N * sizeof(double));    //Speicher allokieren
    if(C2 == NULL) {
        printf("Speicher fuer C2, dem Array fuer die Funktionswerte\
        der eingelesenen Binaerdateien konnte nicht allokiert werden.\n");
        exit(1);
    }
    for(int k=0; k<N; k++) {
        C2[k] = sin(C[k]);
    }
    return C2;
}

/*Funktion erstellt Datei mit Wertetabelle mit Binaerdateien und dessen Funktionswerten:
 */
void data_save(double *C, double *C2, int N) {
    FILE *res = fopen("wertetabelle.txt","w");
    if(res == NULL) {
        printf("Wertetabelle konnte nicht erstellt werden\n");
        exit(1);
    }
    for(int k=0; k<N; k++) {
        //fwrite(&C[k], sizeof(double), 1, res);
        fprintf(res,"%lf\t%lf\n", C[k], C2[k]);
        //fwrite(&C2[k], sizeof(double), 1, res);
        //fprintf(res, "\n");
    }
    fclose(res);
}


//------------------------------------------------------------------------------------       
int main(void) {
    FILE *dataset1 = fopen("dataset1","r");     //Datei oeffnen im Lesemodus
    if(dataset1 == NULL) {                      //Test, ob geoeffnet
        printf("Die Datei dataset1 konnte nicht geoeffnet werden");
        exit(1);
    }
    
    int N;  //Anzahl der Datenelemente ermitteln
    fscanf(dataset1,"%d\n", &N); 
    
    double *DATA = array_init(dataset1,N); //Daten in Array einlesen
    //array_print(DATA,N);  //Array ausgeben
    double *DATA2 = kumm_qusum(DATA,N);
    //array_print(DATA2,N);
    array_free(DATA2);  //Arrays freigeben
    array_free(DATA);   
    
    FILE *dataset2 = fopen("dataset2","r");
    if(dataset2 == NULL) {
        printf("Die Datei dataset2 konnte nicht geoeffnet werden");
        exit(1);
    }
    int N2;
    fread(&N2, sizeof(int), 1, dataset2);   //fread verwenden, da Binaercode
    
    //printf("%d\n",N2);
    double *DATA3 = array_binaer(dataset2, N2); //Daten in Array speichern
    double *DATA4 = array_sinus(DATA3, N2); //Funktionswerte zu DATA3 berechnen und in DATA4 speichern
    data_save(DATA3, DATA4, N2);
    
    array_free(DATA3);
    array_free(DATA4);
    
    fclose(dataset1);   //Dateien schliessen
    fclose(dataset2);

}
