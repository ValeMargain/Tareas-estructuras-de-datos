/**
 * Danna Valeria Rosales Margain 
 * Tarea 1: Funciones Iterativas y Recursivas
 * 25/Agosto/2025
 */
class Funciones {
public:
	int sumaIterativa(int n);
	int sumaRecursiva(int n);
	int sumaDirecta(int n);
};

int Funciones::sumaIterativa(int n){
    int val=0;
    for(int i=0; i<=n; i++) //Ciclo para ir hasta n
    {
        val = val + i; //Suma de 0 a n
    }
    return val;
}

int Funciones::sumaRecursiva(int n){
    if (n == 0) //Valida que sea diferente de 0
    {
        return 0;
    }
    else
    { //Procede con la suma
        return n + sumaRecursiva(n - 1); //Se toma n actual y se va sumando n-1 hasta que n sea 0
    }

}

int Funciones::sumaDirecta(int n){
    return n * (n + 1) / 2; //Utiliza la formula de Gauss S = n(n+1)/2
}

