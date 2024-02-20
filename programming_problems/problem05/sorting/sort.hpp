#ifndef _SORT_HPP
#define _SORT_HPP

#include "linked_list.hpp"

template<typename T> LinkedList<T> sort(LinkedList<T> list)
{
	// Selection sort algorithm
	//1) locate largest item in list
	//2) swap that item and the last item in unsorted list
	//3) "remove" the last item from unsorted or working list
	//4) repeat until size = 1
   
    int lastI = list.getLength() - 1; //var to hold the value of the last index of the list
   
    for (int last = lastI; last >= 0; --last) {//looping through entire list until size is 1 
        
		int max = 0;//holder for just the index of the max value
       
	    for (int i = 1; i <= last; ++i) {
           
		   //searches for the max value and reassigns the index accordingly
		    if (list.getEntry(i) > list.getEntry(max)) {
                max = i;
            }
        }

		//if the current index i is not the max value then swapping needs to occur
        if (max != last) {
           
		    //temp holds the item value of the max value
			T temp = list.getEntry(max);
           	//setting the index that held the max value with the last value of the unsorted list
			list.setEntry(max, list.getEntry(last));
            //setting the last index in the list to the hold the max value
			list.setEntry(last, temp);
       
	    }
		//"removes" the last index of the unsorted list as it is now sorted
        --lastI;
    }

    return list;
}

#endif
