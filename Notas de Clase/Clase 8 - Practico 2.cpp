#include <iostream>
using namespace std;

// Funci�n para intercambiar dos elementos en un arreglo
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Funci�n para ajustar un sub�rbol con ra�z en el �ndice i en un arreglo
void heapify(int arr[], int n, int i) {
    int largest = i; // Inicializa el �ndice de la ra�z como el mayor
    int left = 2 * i + 1; // �ndice del hijo izquierdo
    int right = 2 * i + 2; // �ndice del hijo derecho

    // Si el hijo izquierdo es mayor que la ra�z
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Si el hijo derecho es mayor que la ra�z
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Si el mayor no es la ra�z
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Ajusta el sub�rbol afectado
        heapify(arr, n, largest);
    }
}

// Funci�n principal para ordenar un arreglo utilizando heapsort
void heapsort(int arr[], int n) {
    // Construye un mont�culo (heap)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extrae los elementos del mont�culo uno por uno
    for (int i = n - 1; i >= 0; i--) {
        // Mueve la ra�z actual al final
        swap(arr[0], arr[i]);

        // Ajusta el mont�culo reducido
        heapify(arr, i, 0);
    }
}

// Funci�n para imprimir un arreglo
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

// Funci�n principal
int main() {
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Arreglo original: ";
    printArray(arr, n);

    heapsort(arr, n);

    cout << "Arreglo ordenado: ";
    printArray(arr, n);
    
    system("PAUSE");	
    return 0;
}
