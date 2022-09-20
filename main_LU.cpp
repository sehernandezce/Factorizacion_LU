#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

double **Transpuesta(double **Matriz, int Tamano);        //Devuelve la matriz traspuesta de la matriz.
double **Crear_Matriz_Manual (int Tamano);               //Devuelve una matriz ingresada por el usuario.
double **Crear_Matriz_Ale (int Tamano);                  //Devuelve una matriz aleatoria.
double *Crear_Vector_Manual (int Tamano);                  //Devuelve un vector ingresado por el usuario.
double *Crear_Vector_Ale (int Tamano);                     //Devuelve un vector aleatorio.
void Imprimir_Matriz(double **Matriz, int Tamano);       //Imprime una matriz.
void Imprimir_Vector (double *Vector, int Tamano);         //Imprime un vector.
double **Cholesky (double **Matriz, int Tamano);          //Devuelve la matriz L.
double *Sustitucion_Progresiva (double **Matriz, double *Vector, int Tamano);   //Devuelve la solucion (VI) de una MTI y un VTI.
double *Sustitucion_Regresiva (double **Matriz, double *Vector, int Tamano);    //Devuelve la solucion (VI) de una MTS y un VTI.
void Crout (double **Matriz, int Tamano,double **AuxL, double **AuxU); //Realiza la facotirzacion Crout

int main() {
    int Tamano=0, Generacion=0, control=0, Opcion=0;
    srand(time(NULL));
    cout<<"________________________________________________________________________________"<<endl;
    cout<<endl;
    cout<<'\t'<<'\t'<<'\t'<<'\t'<<"DESCOMPOSICION LU: "<<endl;
    cout<<'\t'<<"Una aplicacion para la solucion de sistemas de ecuaciones lineales."<<endl;
    cout<<'\n'<<'\n';

    //Inserte aqu� una descripcion de como funciona el programa.


    // 1. Ingresa el tama�o de la matriz y luego la crea.
    cout<<"1. Ingrese el tama�o de la matriz: ";
    cin>>Tamano;
    double **Matriz;
    Matriz= new double*[Tamano]; //Reservando memoria para las filas
    for (int i=0;i<Tamano;i++)
    {
        Matriz[i]=new double[Tamano]; //Reservando memora para las columnas
    }
    cout<<endl;

    // 2. Pide al usuario el modo de llenar la matriz y luego la llena.
    do
    {
        cout<<"Seleccione modo de generar la Matriz de Coeficientes del sistema (A) : "<<endl;
        cout<<"--->Para Generacion Manual pulse la tecla 1."<<endl;
        cout<<"--->Para Generacion Aleatoria pulse la tecla 2"<<endl;
        cin>>Generacion;
        if (Generacion==1)
        {
            Matriz=Crear_Matriz_Manual(Tamano);
            control++;
            cout<<"La Matriz de Coeficientes ingresada es: ";
            cout<<endl;
        }
        else if (Generacion==2)
        {
            Matriz=Crear_Matriz_Ale(Tamano);
            control++;
            cout<<"La Matriz de Coeficientes generada es: ";
            cout<<endl;
        }
        else
        {
            cout<<"Por favor seleccione una opci�n valida."<<endl;
            cout<<endl;
        }

    }while (control != 1);
    cout<<endl;
    Imprimir_Matriz(Matriz, Tamano);
    cout<<endl;
    cout<<endl;

    //4. Define el Vector de Terminos Independientes.
    double *Terminos_Indep = new double [Tamano];

    // 3. Pide al usuario el modo de ingresar el vector de terminos independientes.
    do
    {
        cout<<"Seleccione modo de generar el Vector de Terminos Independientes (B): "<<endl;
        cout<<"--->Para Generacion Manual pulse la tecla 1."<<endl;
        cout<<"--->Para Generacion Aleatoria pulse la tecla 2"<<endl;
        cin>>Generacion;
        if (Generacion==1)
        {
            Terminos_Indep = Crear_Vector_Manual(Tamano);
            control++;
            cout<<endl;
            cout<<"El vector de Terminos Independientes ingresado es: ";
        }
        else if (Generacion==2)
        {
            Terminos_Indep = Crear_Vector_Ale(Tamano);
            control++;
            cout<<endl;
            cout<<"El vector de Terminos Independientes generado es: ";
        }
        else
        {
            cout<<"Por favor seleccione una opci�n valida."<<endl;
            cout<<endl;
        }

    }while (control != 2);
    ;
    Imprimir_Vector(Terminos_Indep, Tamano);
    cout<<endl;


    //4. Verifica que tipos de factorizacion se le puede hacer a la matriz.

    //5. Le pide al usuario que elija cual factorizacion quiere usar.

    //6a Fact Doolitle

    cout<<"Seleccione modo en que se realizara la factorizacion LU "<<endl;
        cout<<"--->Para Generacion metodo Crout pulse la tecla 1."<<endl;
        cout<<"--->Para Generacion metodo Cholesky pulse la tecla 2"<<endl;
        cout<<"--->Para Generacion metodo Doolitle pulse la tecla 3."<<endl;
        cin>>Opcion;
     switch(Opcion){
        case 1:

        {
            cout<<"Usted ha elegido la factorizacionde Crout."<<endl;
            cout<<endl;
            double**AuxL=Crear_Matriz_Ale(Tamano);// 1 . Crea Matriz L
            double**AuxU=Crear_Matriz_Ale(Tamano);// 2 . Crea Matriz U
            Crout(Matriz,Tamano,AuxL,AuxU);
            cout<<"La matriz L obtenida (L) por Crout es: "<<endl;
            Imprimir_Matriz(AuxL,Tamano);
            cout<<"La matriz U obtenida (U) por Crout es: "<<endl;
            Imprimir_Matriz(AuxU,Tamano);
            cout<<endl;
            cout<<endl;

             //6c.2. Calcular y mostrar el vector solucion (Y) del sistema "L*Y=B"
    cout<<"A continuacion se da el vector solucion al sistema : "<<endl;
    double *Vector_Y = Sustitucion_Progresiva(AuxL, Terminos_Indep, Tamano);
    cout<<" El vector Y, solucion del sistema L*Y=B es: "<<endl;
    Imprimir_Vector(Vector_Y, Tamano);
    cout<<endl;
    cout<<endl;

    //6c.3. Calcular y mostrar el vector solucion (X) del sistema "Lt*X=Y"
    cout<<" El vector X, solucion del sistema U*X=Y es: "<<endl;
    double *Vector_X = Sustitucion_Regresiva(AuxU, Vector_Y, Tamano);
    Imprimir_Vector(Vector_X, Tamano);
    cout<<endl;
    cout<<endl;
        }
        break;
        case 2:
        { //6c Fact Cholesky
             cout<<"Usted ha elegido la factorizacionde Cholesky."<<endl;
    cout<<endl;
    cout<<"La matriz L obtenida (L) por Cholesky es: "<<endl;
    double **Matriz_L = Cholesky(Matriz, Tamano);
    Imprimir_Matriz(Matriz_L, Tamano);
    cout<<endl;
    cout<<endl;
    cout<<"La matriz L traspuesta (Lt) es: "<<endl;
    double **Matriz_Lt = Transpuesta(Matriz_L, Tamano);
    Imprimir_Matriz(Matriz_Lt, Tamano);
    cout<<endl;
    cout<<endl;

    //6c.2. Calcular y mostrar el vector solucion (Y) del sistema "L*Y=B"
    cout<<"A continuacion se da el vector solucion al sistema : "<<endl;
    double *Vector_Y = Sustitucion_Progresiva(Matriz_L, Terminos_Indep, Tamano);
    cout<<" El vector Y, solucion del sistema L*Y=B es: "<<endl;
    Imprimir_Vector(Vector_Y, Tamano);
    cout<<endl;
    cout<<endl;

    //6c.3. Calcular y mostrar el vector solucion (X) del sistema "Lt*X=Y"
    cout<<" El vector X, solucion del sistema Lt*X=Y es: "<<endl;
    double *Vector_X = Sustitucion_Regresiva(Matriz_Lt, Vector_Y, Tamano);
    Imprimir_Vector(Vector_X, Tamano);
    cout<<endl;
    cout<<endl;
        }
        break;
        case 3:
            {
                cout<<"Usted ha elegido la factorizacion de Doolitle."<<endl;
            cout<<endl;
            double**AuxL=Crear_Matriz_Ale(Tamano);// 1 . Crea Matriz L
            double**AuxU=Crear_Matriz_Ale(Tamano);// 2 . Crea Matriz U
            Crout(Matriz,Tamano,AuxL,AuxU);
             cout<<"La matriz L obtenida (L) por Doolitle es: "<<endl;
            Imprimir_Matriz(AuxL,Tamano);
            cout<<"La matriz U obtenida (U) por Doolitle es: "<<endl;
            Imprimir_Matriz(AuxU,Tamano);
            system("pause");
             double**AuxW=Crear_Matriz_Ale(Tamano);
            AuxW=AuxU;
            AuxU=Transpuesta(AuxL,Tamano);
            AuxL=Transpuesta(AuxW,Tamano);
            cout<<"La matriz L obtenida (L) por Doolitle es: "<<endl;
            Imprimir_Matriz(AuxL,Tamano);
            cout<<"La matriz U obtenida (U) por Doolitle es: "<<endl;
            Imprimir_Matriz(AuxU,Tamano);
            cout<<endl;
            cout<<endl;

             //6c.2. Calcular y mostrar el vector solucion (Y) del sistema "L*Y=B"
    cout<<"A continuacion se da el vector solucion al sistema : "<<endl;
    double *Vector_Y = Sustitucion_Progresiva(AuxL, Terminos_Indep, Tamano);
    cout<<" El vector Y, solucion del sistema L*Y=B es: "<<endl;
    Imprimir_Vector(Vector_Y, Tamano);
    cout<<endl;
    cout<<endl;

    //6c.3. Calcular y mostrar el vector solucion (X) del sistema "Lt*X=Y"
    cout<<" El vector X, solucion del sistema U*X=Y es: "<<endl;
    double *Vector_X = Sustitucion_Regresiva(AuxU, Vector_Y, Tamano);
    Imprimir_Vector(Vector_X, Tamano);
    cout<<endl;
    cout<<endl;
            }
            break;
        default:
        {

        }
        break;
     }





    return 0;
}


double *Crear_Vector_Manual (int Tamano){
    //1. Define el nuevo vector.
    double *Vector = new double[Tamano];

    //2. Le pide al usuario que llene el vector.
    for (int i=0; i<Tamano; i++){
        cout<<"Ingrese la posicion ["<<i<<"]: ";
        cin>>Vector[i];
    }

    return Vector;
}


double *Crear_Vector_Ale (int Tamano){
    //1. Define el nuevo vector.
    double *Vector = new double[Tamano];

    //1. Llena el vector de numeros aleatorios del 0 hasta el 30.
    for (int i=0; i<Tamano; i++){
        Vector[i]=rand()%31;
    }

    return Vector;
}


double *Sustitucion_Regresiva (double **Matriz, double *Vector, int Tamano)
{
    // 1. Define el vector solucion de retorno de la funcion.
    double *Vector_X = new double[Tamano];

    //2. Recorre la matriz por filas de abajo para arriba.
    for (int j=Tamano-1; j>-1; j--){

        //3. Paso base de la sustituci�n.
        if (j==Tamano-1){
            Vector_X[j] = (Vector[j]/Matriz[j][j]);
        }

        //4. Paso general de la sustituci�n.
        else{
            int suma=0;
            //5. Realiza la suma de los productos coeficientes-inc�gnita de las incognitas ya calculadas.
            for ( int k=Tamano-1; k>j; k--){
                suma+= Matriz[j][k]*Vector_X[k];
            }

            //6. Resta al termino independiente la suma obtenida y la divide por el coeficiente correspondiente.
            Vector_X[j] = Vector[j] - suma;
            Vector_X[j]/= Matriz[j][j];
        }

    }

    return Vector_X;
}


double *Sustitucion_Progresiva (double **Matriz, double *Vector, int Tamano)
{
    // 1. Define el vector solucion de retorno de la funcion.
    double *Vector_Y = new double[Tamano];

    //2. Recorre la matriz por filas de arriba para abajo.
    for (int j=0; j<Tamano; j++){

        //3. Paso base de la sustitucion.
        if (j==0){
            Vector_Y[j] = (Vector[j]/Matriz[j][j]);
        }

        //4. Paso general de la sustituci�n.
        else{
            int suma=0;
            for ( int k=0; k<j; k++){
                //5. Realiza la suma de los productos coeficientes-inc�gnita de las incognitas ya calculadas.
                suma+= Matriz[j][k]*Vector_Y[k];
            }

            //6. Resta al termino independiente la suma obtenida y la divide por el coeficiente correspondiente.
            Vector_Y[j] = Vector[j] - suma;
            Vector_Y[j]/= Matriz[j][j];
        }

    }

    return Vector_Y;
}


void Imprimir_Matriz(double **Matriz, int Tamano)
{
    //1. Imprime la matriz.
    for (int i=0;i<Tamano;i++)
    {
        for (int j=0;j<Tamano;j++)
        {
            cout<<'\t';
            cout<<*(*(Matriz+i)+j);//Matriz[i][j]
            cout<<'\t';
        }
        cout<<endl;
    }
}

void Imprimir_Vector (double *Vector, int Tamano)
{
    // 1. Imprime el vector.
    cout<<endl;
    for (int i=0; i<Tamano; i++){
        cout<<Vector[i]<<endl;
    }
}

double **Crear_Matriz_Manual (int Tamano)
{
    // 1. Se define la nueva matriz.
    double **Matriz = new double*[Tamano];
    for (int i=0;i<Tamano;i++)
    {
        Matriz[i]=new double[Tamano];
    }

    // 2. Se le pide al usuario que llene la matriz.
    for (int i=0;i<Tamano;i++)
    {
        for (int j=0;j<Tamano;j++)
        {
            cout<<"Ingrese posicion ["<<i<<"]["<<j<<"]:";
            cin>>*(*(Matriz+i)+j); //Matriz [i][j]

        }
    }
    return Matriz;
}

double **Crear_Matriz_Ale (int Tamano){

    // 1. Se define la nueva matriz.
    double **Matriz;
    Matriz= new double*[Tamano];
    for (int i=0;i<Tamano;i++)
    {
        Matriz[i]=new double[Tamano];
    }

    // 2. Se llena la matriz de numeros aleatorios del 0 al 30.
    for (int i=0;i<Tamano;i++)
    {
        for (int j=0;j<Tamano;j++)
        {
            *(*(Matriz+i)+j)=rand()%31;
        }
    }
    return Matriz;
}

double **Transpuesta(double **Matriz, int Tamano){
    //1. Se crea la matriz donde se va a guardar la traspuesta.
    double **aux=Crear_Matriz_Ale(Tamano);
    //3. Se guarda la traspuesta en aux.
    for (int i=0; i<Tamano; i++)
    {
        for (int j=0; j<Tamano; j++)
        {
            aux[j][i]=Matriz[i][j];
        }
    }
    return aux;
}

double **Cholesky (double **Matriz, int Tamano){
    //1. Se crea la matriz L y se inicializa con entradas aleatorias.
    double **matrizl=Crear_Matriz_Ale(Tamano);

    //2. Se hace un recorrido primero por columnas y luego filas.
    for (int j=0; j<Tamano; j++){
        for(int i=0; i<Tamano; i++){

            //3. Se plantea el proceso para los elementos en la diagonal principal.
            if (i==j){
                int Contador1=0;
                for(int k=0;k<i;k++)
                {
                    Contador1+=pow(matrizl[i][k], 2);
                }
                matrizl[i][j]=sqrt(Matriz[i][j]-Contador1);
                Contador1=0;
            }

            //3. Se plantea el proceso para los elementos en la diagonal principal.
            else if (i>j){
                float Contador2=0;
                for (int k=0; k<j; k++){
                    Contador2+=(matrizl[i][k]*matrizl[j][k]);
                }
                matrizl[i][j] = Matriz[i][j] - Contador2;
                matrizl[i][j]/= matrizl[j][j];
                Contador2=0;
            }

            //4. Se llena el triangulo superior de la matriz de ceros.
            else{
                matrizl[i][j]=0;
            }
        }
    }

    //5. La funcion retorna la mariz L.
    return matrizl;
}

double **Multiplicaion_Matriz(double ** matrizC, double **matrizD, int ColumnasC, int FilasD){ // Multiplicacion de matrices C*D=matrizM

    double aux=0;
    double **matrizM = Crear_Matriz_Ale(ColumnasC);//Crea una matriz de tama�ao de la matrizC
    if(ColumnasC==FilasD){// Verifica que sea posible multiplicar.
        int TamanoC=ColumnasC;
        for (int i=0; i<TamanoC; i++){
            for(int j=0;j<TamanoC; j++){
                for (int a=0; a<TamanoC; a++){
                    aux=aux+matrizC[i][a]*matrizD[a][j];  //realiza la multiplicaion de la fila de la matrizC por la columna de la matrizD
                }
                matrizM[i][j]=aux;//Llena la matriz resulatado
                aux=0;
            }
        }
    }
    else
    {
        cout<<"No es posible realizar la multiplicacion"<<endl;
        return 0;
    }

    return matrizM;

}
void Crout (double**Matriz, int Tamano,double**AuxL, double **AuxU){
    int k=0;
    float suma=0;
     for(int i=0; i<Tamano; i++){// 3. Llena las matrices. LLena una columna de la matriz L y luego una fila de la matriz U.
        k=0,suma=0;
        while (k<Tamano){
        if(k<i){// Pone los ceros, da la forma de triaungular inferior.
            AuxL[k][i]=0;
            }
            else{
            for(int j=0; j<i; j++){// 3.1 Multiplica la fila de la matriz L con la columna de la matriz U.
             suma=suma+AuxL[k][j]*AuxU[j][i];
            }
            AuxL[k][i]=Matriz[k][i]-suma;//3.2 Toma el resultado de la multiplicacion y le resta a matriz A.
            }
        k++;
        suma=0;
        }//Llena las columnas de la matriz L.
        k=0,suma=0;
        while (k<Tamano){//3.3  Multiplica la fila de la matriz L con la columna de la matriz U.
        if(k<i){// Pone los ceros, da la forma triaungular superior.
            AuxU[i][k]=0;
            }
        else if (k==i){// Pone los unos de la diagonal.
            AuxU[k][k]=1;
        }
            else{
                for(int j=0; j<i; j++){
             suma=suma+AuxL[i][j]*AuxU[j][k];//3.4 Toma el resultado de la multiplicacion y le resta a matriz A, luego divide
                                                // entre una posicion dada de la matriz L.
            }
        AuxU[i][k]=(Matriz[i][k]-suma)/AuxL[i][i];
            }
        k++;
        suma=0;
        }//Llena las filas de la matriz U.
     }
}


void Doolitle(float **Matriz, int Tamano,float **AuxL, float **AuxU){

    int k=0;
    float suma=0;
     for(int i=0; i<Tamano; i++){// 3. Llena las matrices. LLena una columna de la matriz L y luego una fila de la matriz U.
        k=0,suma=0;
        while (k<Tamano){
        if(k<i){// Pone los ceros, da la forma de triaungular inferior.
            AuxU[i][k]=0;
            }
            else{
            for(int j=0; j<i; j++){// 3.1 Multiplica la fila de la matriz L con la columna de la matriz U.
             suma=suma+AuxL[i][j]*AuxU[j][k];
            }
            AuxL[k][i]=Matriz[i][k]-suma;//3.2 Toma el resultado de la multiplicacion y le resta a matriz A.
            }
        k++;
        suma=0;
     }
     
       k=0,suma=0;
        while (k<Tamano){
        if(k<i)
            {
            AuxL[k][i]=0;
            }
        else if (k==i){// Pone los unos de la diagonal.
            AuxL[k][k]=1;
        }
            else{
                for(int j=0; j<i; j++){
             suma=suma+AuxL[k][j]*AuxU[j][i];//3.4 Toma el resultado de la multiplicacion y le resta a matriz A, luego divide
                                                // entre una posicion dada de la matriz L.
            }
        AuxL[k][i]=(Matriz[k][i]-suma)/AuxU[i][i];
            }
        k++;
        suma=0;
        }//Llena las filas de la matriz .
    }

}
