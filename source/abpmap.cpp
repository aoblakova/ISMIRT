#include "abpmap.h"
#include "queue.h"


// these template classes may be used
template class ABPMap<Queue>;
template class ABPMap<double>;
template class ABPMap<ABPMap<double>>;


template<typename type> 
ABPMap<type>::ABPMap(){
    // set all flags to false, as there are no elements in the map
    for (int i = 0; i < 3; ++i){
        flags[i] = false;
    }
}


template<> void ABPMap<Queue>::printMap() const{
    // print every element of the map in case it stores queues
    for (int i = 0; i < 3; ++i){
        if (flags[i]){
            std::cout << getAKey(i) << ":\n";
            data[i].printQueue();
        }
    }
}


template<typename type> void ABPMap<type>::printMap() const{
    // do nothing
}


template<typename type> 
type & ABPMap<type>::operator[](char key){
    // get element of the map
    return operator[](getInd(key));
}


template<typename type> 
type & ABPMap<type>::operator[](int ind){
    // get element of the map
    if (ind < 0 || ind >= NUMBER_OF_KEYS || !flags[ind]){
        // access error, no such key
        printMap();
        std::cout << ind << " <- index\n";
        throw "ABPMap<type>::operator[]: No such key exists in the ABPMap!\n";
    }
    return data[ind];
}

template<typename type> 
const type & ABPMap<type>::operator[](int ind) const{
    // get const reference of the element
    if (ind < 0 || ind >= NUMBER_OF_KEYS || !flags[ind]){
        // access error, no such key
        std::cout << ind << "\n";
        printMap();
        throw "ABPMap<type>::operator[] const:No such key exists in the ABPMap!\n";
    }
    return data[ind];
}

template<typename type> 
const type & ABPMap<type>::operator[](char a_key) const{
    // get const reference of the element
    return operator[](getInd(a_key));
}


template<typename type> 
void ABPMap<type>::insertItem(char key, const type& element){
    // insert an element to the map
    insertItem(getInd(key), element);
}

template<typename type> 
void ABPMap<type>::insertItem(int ind, const type& element){
    // insert an element to the map
    // TODO: do not use this, maybe use some kind of swap
    if (flags[ind]) // do not allow a collision
         throw "An element already exists\n";
    flags[ind] = true;
    data[ind] = element; // copy an element   
}

template<typename type> void ABPMap<type>::eraseItem(int ind){
    // erase an item
    flags[ind] = false;
    // nothing more is required as an element with false flag won't be accessed
    // if inserted once more, or the map is destroyed, so the element would be
}

template<typename type> bool ABPMap<type>::hasAnyKey() const{
    // check if there is any key in the map, i.e., the map is not empty
    for (int i = 0; i < 3; ++i){
        // for each key check if it exists
        if (flags[i]){ // return true if at least one exists
            return true;
        }
    }
    return false;
}

