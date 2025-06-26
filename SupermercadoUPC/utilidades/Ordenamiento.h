#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <vector>
#include <functional>
#include <algorithm>

template <typename T>
class Ordenamiento {
public:
    // Quicksort
    static void quickSort(std::vector<T>& arr, int inicio, int fin) {
        if (inicio < fin) {
            int pivotIndex = particion(arr, inicio, fin);
            quickSort(arr, inicio, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, fin);
        }
    }
    
    // Wrapper para quicksort
    static void quickSort(std::vector<T>& arr) {
        if (arr.size() > 1) {
            quickSort(arr, 0, arr.size() - 1);
        }
    }
    
    // Mergesort
    static void mergeSort(std::vector<T>& arr, int inicio, int fin) {
        if (inicio < fin) {
            int medio = inicio + (fin - inicio) / 2;
            mergeSort(arr, inicio, medio);
            mergeSort(arr, medio + 1, fin);
            merge(arr, inicio, medio, fin);
        }
    }
    
    // Wrapper para mergesort
    static void mergeSort(std::vector<T>& arr) {
        if (arr.size() > 1) {
            mergeSort(arr, 0, arr.size() - 1);
        }
    }
    
    // Heapsort
    static void heapSort(std::vector<T>& arr) {
        int n = arr.size();
        
        // Construir el heap (árbol binario completo)
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        
        // Extraer elementos uno por uno del heap
        for (int i = n - 1; i > 0; i--) {
            // Mover la raíz actual al final
            std::swap(arr[0], arr[i]);
            
            // Llamar a heapify en el heap reducido
            heapify(arr, i, 0);
        }
    }
    
    // Ordenamiento personalizado con función de comparación (lambda)
    static void ordenarPersonalizado(std::vector<T>& arr, std::function<bool(const T&, const T&)> comparador) {
        std::sort(arr.begin(), arr.end(), comparador);
    }
    
private:
    // Función auxiliar para quicksort
    static int particion(std::vector<T>& arr, int inicio, int fin) {
        T pivot = arr[fin];
        int i = inicio - 1;

        for (int j = inicio; j < fin; j++) {
            // Usar std::less para comparar elementos
            if (std::less<T>()(arr[j], pivot)) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[fin]);
        return i + 1;
    }
    
    // Función auxiliar para mergesort
    static void merge(std::vector<T>& arr, int inicio, int medio, int fin) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;
        
        std::vector<T> izquierda(n1);
        std::vector<T> derecha(n2);
        
        for (int i = 0; i < n1; i++) {
            izquierda[i] = arr[inicio + i];
        }
        
        for (int j = 0; j < n2; j++) {
            derecha[j] = arr[medio + 1 + j];
        }
        
        int i = 0, j = 0, k = inicio;
        
        while (i < n1 && j < n2) {
            if (std::less<T>()(izquierda[i], derecha[j])) {
                arr[k] = izquierda[i];
                i++;
            } else {
                arr[k] = derecha[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = izquierda[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = derecha[j];
            j++;
            k++;
        }
    }
    
    // Función auxiliar para heapsort
    static void heapify(std::vector<T>& arr, int n, int i) {
        int largest = i;
        int izquierda = 2 * i + 1;
        int derecha = 2 * i + 2;
        
        if (izquierda < n && arr[izquierda] > arr[largest]) {
            largest = izquierda;
        }
        
        if (derecha < n && arr[derecha] > arr[largest]) {
            largest = derecha;
        }
        
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
};

#endif