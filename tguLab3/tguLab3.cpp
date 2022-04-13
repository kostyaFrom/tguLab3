#include <iostream>
#include <cstdlib>
#include <ctime>                                 
#include <cmath> 
#include <string.h>
using namespace std;

int randomNumber(int range_min, int range_max);
void populateTestArray();
void sortInsertion(int arr[], int n);
void selectionSort(int arr[], int n);
void swap(int* xp, int* yp);
void bubbleSort(int arr[], int n);
int shellSort(int arr[], int n);
void quickSort(int* array, int low, int high);
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);
void populateTestArray();
// методы поиска
void linearSearch(int arr[], int selement, int size);
int binarySearch(int arr[], int l, int r, int selement);
int blockSearch(int a[], int n, int item);

const unsigned int ARRSIZE = 500;
const int ABSLIMIT = 500;
int testArray[ARRSIZE];
clock_t start, finish;

void showArr() {
    for (auto i : testArray) {
        cout << i << endl;
    }
}

int main(){  

    /*populateTestArray();
    linearSearch(testArray, 165, ARRSIZE);*/

    /*populateTestArray();
    int selement = 1364;
    int pivot = sizeof(testArray) / sizeof(testArray[0]);
    cout << binarySearch(testArray, 0, pivot-1 , selement) << endl;*/

    /*populateTestArray();
    sortInsertion(testArray, ARRSIZE);
    showArr();
    int selement = 357;
    cout << blockSearch(testArray, ARRSIZE, selement) << endl;*/

    /*populateTestArray();
    start = clock();
    sortInsertion(testArray, ARRSIZE);
    finish = clock();
    cout << " total tacts = " << (finish - start) << endl;*/

    /*populateTestArray();
    start = clock();
    selectionSort(testArray, ARRSIZE);
    finish = clock();
    cout << " total tacts = " << (finish - start) << endl;*/

    /*populateTestArray();
    start = clock();
    bubbleSort(testArray, ARRSIZE);
    finish = clock();
    cout << " total tacts = " << (finish - start) << endl;*/

    /*populateTestArray();
    start = clock();
    shellSort(testArray, ARRSIZE);
    finish = clock();
    cout << " total tacts = " << (finish - start) << endl;*/

    /*populateTestArray();
    start = clock();
    quickSort(testArray, 1500, 2999);
    finish = clock();
    cout << " total tacts = " << (finish - start) << endl;*/
    
    /*populateTestArray();
    start = clock();
    heapSort(testArray, ARRSIZE);
    finish = clock();   
    cout << " total tacts = " << (finish - start) << endl;*/
}

//=============== функции поиска ==================================

//линейный поиск
void linearSearch(int arr[], int selement, int size) {
    int i{ 0 };
    for (; i < size; i++) {
        if (arr[i] == selement) {
            cout << selement << " is present at location " << i << endl;
            break;
        }
    }
    if (i == size) {
        cout << selement << " isn't present in the array." << i << endl;
    }
}

//бинарный поиск возвращает -1 если элеменнт не найден
int binarySearch(int arr[], int l, int r, int num) {

    if (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid] == num)
            cout << num << " is present at location " << endl;
            return mid;
        if (arr[mid] > num)
            return binarySearch(arr, l, mid - 1, num);
        if (arr[mid] < num)
            return binarySearch(arr, mid + 1, r, num);
    }
    return -1;
}

// блочный поиск
int blockSearch(int array[], int size, int key) {

    int start = 0;
    int end = sqrt(size); //the square root of array length

    while (array[end] <= key && end < size) {
        start = end; //it it is not correct block then shift block
        end += sqrt(size);
        if (end > size - 1)
            end = size; //if right exceeds then bound the range
    }

    for (int i = start; i < end; i++) { //perform linear search in selected block
        if (array[i] == key)
            return i; //the correct position of the key
    }
    return -1;
}



//==================== функции сортировки ================================

/* === populate TestArray with random nuber ============== */
void populateTestArray()
{
    for (unsigned int i = 0; i < ARRSIZE; i++) {
        testArray[i] = randomNumber(-ABSLIMIT, ABSLIMIT);
    }
}
/* === generate random nuber ============== */
int randomNumber(int range_min, int range_max) {
    return rand() % (range_max - range_min + 1) + range_min;
}

/* функция сортировки массива вставками*/
void sortInsertion(int arr[], int n) {

    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /*перемещение элемента массива
        который больше key,
        на одну позицию вперед от текущей*/
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/* ================== сотировка выбором ====================*/
void selectionSort(int arr[], int n) {

    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {
        // поиск минимального элемента 
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // меняем местами найденный минимальный элемент с первым 
        swap(&arr[min_idx], &arr[i]);
    }
}

//дополнительный метод
void swap(int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/* ===================== пузырьковая (обменная) сортировка ============ */
void bubbleSort(int arr[], int n) {

    int i, j;
    for (i = 0; i < n - 1; i++)

        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
}


/* ====================== сортировка Шелла ========================== */
int shellSort(int arr[], int n) {

    //начинаем с половины массива
    for (int gap = n / 2; gap > 0; gap /= 2) {

        /* выполняем сортировку вставками для диапазона gap */
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
    return 0;
}

/* ==================== сортировка Хоара ========================== */

void quickSort(int* array, int low, int high) {
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2];
    int temp;

    while (i <= j)
    {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(array, low, j);
    if (i < high)
        quickSort(array, i, high);
}


/* ===================== функция превращения массива в кучу(пирамиду) ============= */
void heapify(int arr[], int n, int i) {

    int largest = i; // корень
    int l = 2 * i + 1; // левая нода
    int r = 2 * i + 2; // правая нода

    //если левый элемент больше корня записываем его на место корня
    if (l < n && arr[l] > arr[largest])
        largest = l;

    //если правый элемент больше корня записываем его на место корня
    if (r < n && arr[r] > arr[largest])
        largest = r;

    //если корень не равен i меняем местами 
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        //рекурсивно проходим по массиву
        heapify(arr, n, largest);
    }
}

/* ================= функция сортировки кучей (пирамидой) =========== */
void heapSort(int arr[], int n) {

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}