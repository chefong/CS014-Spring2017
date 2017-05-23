#include "Heap.h"
#include <iostream>

using namespace std;

void Heap::enqueue(PrintJob* current) {
	if (numItems < MAX_HEAP_SIZE) {
		if (!numItems) {
			arr[numItems ] = current;
			++numItems;
		}
		else {
		   int x = numItems;
		   while (x > 0 && (arr[(x-1)/2]->getPriority() < current->getPriority())) {
            arr[x] = arr[(x-1)/2];
            x = (x-1)/2;
         }
         arr[x] = current;
         ++numItems;
		}
	}
}

void Heap::dequeue() {
	if ((numItems > 2 && arr[1]->getPriority() < arr[numItems - 1]->getPriority()) && (arr[2]->getPriority() < arr[numItems - 1]->getPriority())) {
		arr[0] = arr[numItems-1];
		--numItems;
	}
	else {
		trickleDown(0);
		--numItems;
	}
}

PrintJob* Heap::highest() {
	if (!numItems) {
		return 0;
	}
	return arr[0]; //highest at index 0 bc max heap
}

void Heap::print() {
	cout << "Priority: " << arr[0]->getPriority()
		 << ", Job Number: " << arr[0]->getJobNumber() 
		 << ", Number of Pages: " << arr[0]->getPages() 
		 << endl; 
}

void Heap::trickleDown(int num) {   
    if (((2 * num + 1) < numItems) && ((2 * num + 2) < numItems)) { //if both children exist  
        if (arr[2 * num + 1]->getPriority() > arr[2 * num + 2]->getPriority()) {//if left > right
            arr[num] = arr[2 * num + 1];
            trickleDown(2 * num + 1);
        }
        else { //if right > left
            arr[num] = arr[2 * num + 2];
            trickleDown(2 * num + 2);
        }
    }
    else if (((2 * num + 1) < numItems)) { //if ONLY left exists
        arr[num] = arr[2 * num + 1];
    }

    return;
}