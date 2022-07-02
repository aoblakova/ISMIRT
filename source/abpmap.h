#ifndef ABPMAP_H
#define ABPMAP_H
#include <map>
#include "general.h"


extern int TOTAL_QUEUE_COPIES;


class Queue; // ABPMaps are used in Queue to create new Queue, so this used instead of include statement.
template <class type> class ABPMap;

// declare possible doesEmplaceMakeSense functions, they are defined in queue.cpp
bool doesEmplaceMakeSense(int new_capacity); // for creating an empty queue
bool doesEmplaceMakeSense(int new_capacity, double probability); // for creating a queue with prob 0 equal to probability
bool doesEmplaceMakeSense(int new_capacity, const Queue & another, int m_second, double coef_no_dep, double coef_dep); // for creating a queue that is a part of departure queue
bool doesEmplaceMakeSense(int new_capacity, const ABPMap<Queue>& queues, const std::map<char,double>& coefficients, 
                          const std::map<char,double>& coefficients_full, bool is_free_departure_possible); // for creating a mix queue
bool doesEmplaceMakeSense(int new_capacity, int new_start, int new_end); // for creating a part of another queue (and later swap values)
bool doesEmplaceMakeSense(const Queue& another, int start, int end); // copy part of another queue
bool doesEmplaceMakeSense(const Queue & another, int m_second, bool is_from_a, bool is_block, double coefficient); // creating a tail queue
bool doesEmplaceMakeSense(int new_capacity, int queue_length, double probability); // for queues starting not (necessary) with zero


template <class type>
class ABPMap{
    // a map which can contain only keys 'a', 'b' and 'p', they are changed to ints 0, 1, 2 and data is stored in an array
    std::array<bool, NUMBER_OF_KEYS> flags; // flags that store if a particular element exists
    std::array<type, NUMBER_OF_KEYS> data; // data elements to access
public:
    ABPMap(); // constructor 
    // access operators
    type & operator[](int ind); 
    const type & operator[](int ind) const;
    type & operator[](char key);
    const type & operator[](char key) const;
    // inserting an item
    void insertItem(int ind, const type & element);
    void insertItem(char key, const type & element);
    // check is there is a particular key
    bool hasKey(int ind) const {return flags[ind];}
    bool hasKey(char key) const {return flags[getInd(key)];}
    // erase an item 
    void eraseItem(int ind);
    void eraseItem(char key) = delete; // some char functions are deleted to eliminate char to int implicit conversions 
    // check if any key exists (map is not empty)
    bool hasAnyKey() const;
    // print map, only used for type = Queue
    void printMap() const;
    // emplace functions
    template<typename... Args> void justEmplace(int ind, const Args &... args){
                                    // just emplace a new element without checking that it is non-empty 
                                    if (ind < 0 || ind >= NUMBER_OF_KEYS) { // check that index is valid
                                        std::cout << ind << "\n";
                                        throw "Invalid element index\n";
                                    }
                                    if (flags[ind]) // check that the item don't yet exists
                                        throw "An element already exists\n";
                                    flags[ind] = true; 
                                    data[ind].emplace(args...); // emplace element
    }
    template<typename... Args> bool emplace(int ind, const Args &... args){
                                    // emplace a new item if it is not empty, return true if added
                                    if (ind < 0 || ind >= NUMBER_OF_KEYS) { // check that index is valid
                                        std::cout << ind << "\n";
                                        throw "Invalid element index\n";
                                    }
                                    if (flags[ind]) // check that the item don't yet exists
                                        throw "An element already exists\n";
                                    if (data[ind].doesEmplaceMakeSense(args...)){ // check if emplacement makes sense (the item is not empty)
                                        flags[ind] = true;
                                        data[ind].emplace(args...); 
                                        return true; // added
                                    }
                                    return false; // not added
    }
    template<typename... Args> void emplace(char a_key, const Args &... args) = delete;
};


#endif // ABPMAP_H
