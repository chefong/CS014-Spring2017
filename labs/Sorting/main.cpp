#include <iostream>
#include <ctime>

using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

//partitions inputs into low and high parts
int partition_midpoint(int numbers[], int i, int k) {
    int l = 0;
    int h = 0;
    int midpoint = 0;
    int pivot = 0;
    int temp = 0;
    bool done = false;
    
    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = numbers[midpoint];
    
    l = i;
    h = k;
    
    while (!done) {
        
        /* Increment l while numbers[l] < pivot */
        while (numbers[l] < pivot) {
            ++l;
        }
        
        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers[h]) {
            --h;
        }
        
        /* If there are zero or one elements remaining,
        all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
            update l and h */
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;
            
            ++l;
            --h;
        }
    }
    
    return h;
}

int partition_median(int numbers[], int i, int k) {
    int l = 0;
    int h = 0;
    int midpoint = 0;
    int pivot = 0;
    int median = 0;
    int temp = 0;
    bool done = false;
    
    /* Pick median element as pivot */
    midpoint = i + (k - i) / 2;

    if ((numbers[midpoint] >= numbers[i] && numbers[midpoint] <= numbers[k]) ||
        (numbers[midpoint] >= numbers[k] && numbers[midpoint] <= numbers[i])) {

        median = midpoint;
    }
    else if ((numbers[i] <= numbers[midpoint] && numbers[i] >= numbers[k]) ||
        (numbers[i] >= numbers[midpoint] && numbers[i] <= numbers[k])) {

        median = i;
    }
    else if ((numbers[k] <= numbers[i] && numbers[k] >= numbers[midpoint]) ||
        (numbers[k] >= numbers[i] && numbers[k] <= numbers[midpoint])) {

        median = k;
    }

    pivot = numbers[median];
    
    l = i;
    h = k;
    
    while (!done) {
        
        /* Increment l while numbers[l] < pivot */
        while (numbers[l] < pivot) {
            ++l;
        }
        
        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers[h]) {
            --h;
        }
        
        /* If there are zero or one elements remaining,
        all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
            update l and h */
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;
            
            ++l;
            --h;
        }
    }
    
    return h;
}

//this function sorts the given array in the range from i to k 
//using quicksort method. In this function, pivot is the midpoint 
//element (numbers[(i+k)/2]). (implementation of this function is 
//given in section 21.5).
void Quicksort_midpoint(int numbers[], int i, int k) {
    int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = partition_midpoint(numbers, i, k);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort_midpoint(numbers, i, j);
   Quicksort_midpoint(numbers, j + 1, k);
   
   return;
}

//this function utilizes different pivot selection technique in 
//quicksort algorithm. The pivot is the median of the following 
//three values: leftmost (numbers[i]), midpoint (numbers[(i+k)/2]) 
//and rightmost (numbers[k]). You should modify the partition 
//function given in section 21.5 to select the pivot using 
//median-of-three technique.
void Quicksort_medianOfThree(int numbers[], int i, int k) {
    int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = partition_median(numbers, i, k);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort_medianOfThree(numbers, i, j);
   Quicksort_medianOfThree(numbers, j + 1, k);
   
   return;
}

//this function sorts the given array using InsertionSort method. 
//(implementation of this method is provided in section 21.3).
void InsertionSort(int numbers[], int numbersSize) {
    int i = 0;
    int j = 0;
    int temp = 0;  // Temporary variable for swap
   
    for (i = 1; i < numbersSize; ++i) {
       j = i;
       // Insert numbers[i] into sorted part
       // stopping once numbers[i] in correct position
       while (j > 0 && numbers[j] < numbers[j - 1]) {
           // Swap numbers[j] and numbers[j - 1]
           temp = numbers[j];
           numbers[j] = numbers[j - 1];
           numbers[j - 1] = temp;
           --j;
       }
    }
   
   return;
}

int main() {

    //declares arrays of size 5000
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];

    //test with size 100,000
    int arr4[100000];
    int arr5[100000];
    int arr6[100000];

    int elapsedTime = 0;
    clock_t Start = 0;
    clock_t End = 0;

    //fills arrays with randomly generated numbers
    fillArrays(arr1, arr2, arr3);
    fillArrays(arr4, arr5, arr6);

    cout << "Quicksort Midpoint" << endl;
    Start = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed time: " << elapsedTime << endl;
    cout << endl;

    cout << "Quicksort Median" << endl;
    Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed time: " << elapsedTime << endl;

    cout << "Insertion Sort" << endl;
    Start = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed time: " << elapsedTime << endl;
    cout << endl;

///////////////////////////////////////////////////////////////////////////////////////////////////

    cout << "Testing with size 100,000..." << endl;
    cout << "Quicksort Midpoint" << endl;
    Start = clock();
    Quicksort_midpoint(arr4, 0, 100000 - 1);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed time: " << elapsedTime << endl;
    cout << endl;

    cout << "Quicksort Median" << endl;
    Start = clock();
    Quicksort_medianOfThree(arr5, 0, 100000 - 1);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed time: " << elapsedTime << endl;
    cout << endl;

    cout << "Insertion Sort" << endl;
    Start = clock();
    InsertionSort(arr6, 100000);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed time: " << elapsedTime << endl;
    cout << endl;

    return 0;
}