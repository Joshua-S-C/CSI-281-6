//
//  HashTable.h
//
//  This file defines a Hash Table class.
//  You SHOULD modify this file.
//
//  Copyright 2019 David Kopec
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation files
//  (the "Software"), to deal in the Software without restriction,
//  including without limitation the rights to use, copy, modify, merge,
//  publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice
//  shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.

#ifndef hashtable_hpp
#define hashtable_hpp

#include <utility> // for pair
#include <functional> // for hash()
#include <list>
#include <optional>
#include <algorithm> // find_if(), remove_if()
#include <iostream>

#define DEFAULT_CAPACITY 10
#define MAX_LOAD_FACTOR 0.7

using namespace std;

namespace csi281 {
    template
    <typename K, typename V>
    class HashTable {
    public:
        // Initialize the array with a starting capacity
        HashTable(int cap = DEFAULT_CAPACITY) {
            if (cap < 1) { cap = 1; } // cannot have < 1 capacity
            resize(cap);
        }
        
        // Erase the array
        ~HashTable() {
            delete[] backingStore;
        }
        
        // Put the key value pair in the hash table
        // If *key* is already present, change its
        // associated value to *value*
        // If the load factor exceeds the MAX_LOAD_FACTOR
        // then resize the table
        // TIP: Be careful to get a reference to the list at each
        // location in the backing store, so you're modifying
        // the original and not a copy
        // Note: doesn't matter if you put it at the start of the end of the linked lists
        void put(const K key, const V value) {
            // std::find_if will prolly be helpful
            // thePair.first or second to get Key or Value
            
            // If full
            if (count + 1 >= capacity)
                resize(capacity * growthFactor);

            pair<K, V> insert(key, value);
            // Iterate thru Linked List
            auto& theList = backingStore[(int)hashKey(key) % capacity]; // Ref to list
            for (auto p& : theList[i]) {
                // Overwrites Value
                if (p.first == insert.first) { 
                    p.second = insert.second; 
                    return;
                }
                
            }


            count++;
        }
        
        // Get the item associated with a particular key
        // return an empty optional (nullopt) if the item is not found
        // and returns an optional with the value associated with key
        // if key is found
        // TIP: read the documentation on optional
        // https://en.cppreference.com/w/cpp/utility/optional
        // TIP: Be careful to get a reference to the list at each
        // location in the backing store, so you're modifying
        // the original and not a copy
        optional<V> get(const K &key) {
            // if found: return optional<V>(value)
            // go to index of hash and look thru linked list
            // not found: return nullopt;

            optional<V> answer;

            // Iterate thru Linked List
            for (auto p : backingStore[(int)hashKey(key) % capacity]) {
                if (p.first == key) return optional<V>(p.second);
            }
            return nullopt;
            
            // this is the actual code but I cant get the value
            /*optional<V> answer = backingStore[hashKey(key)].second;
            return answer;*/


            // Old v
            //if (backingStore[hashKey(key)].second == NULL)
            //    return answer; // Use optional thing here
            //answer = backingStore[hashKey(key)].second;
            //return answer;
        }
        
        // Remove a key and any associated value from the hash table
        // TIP: I suggest using remove_if()
        // https://en.cppreference.com/w/cpp/algorithm/remove
        // TIP: Be careful to get a reference to the list at each
        // location in the backing store, so you're modifying
        // the original and not a copy
        void remove(const K &key) {
            // YOUR CODE HERE
            auto& theList = backingStore[(int)hashKey(key) % capacity]; // Ref to list
            //theList.erase(std::remove_if(theList.begin(), theList.end(), [&](auto& p) {return something; }), theList.end());
        }
        
        // Calculate and return the load factor
        float getLoadFactor() {
            return ((float) count) / ((float) capacity);
        }
        
        // Get the count
        int getCount() {
            return count;
        }
        
        // Get the capacity
        int getCapacity() {
            return capacity;
        }
        
        // Print out the contents of the hash table
        void debugPrint() {
            for (int i = 0; i < capacity; i++) {
                cout << i << ":";
                for (auto p : backingStore[i]) {
                    cout << " -> (" << p.first << ", " << p.second << ")";
                }
                cout << endl;
            }
        }
        
    private:
        int capacity = 0;
        int growthFactor = 2;
        int count = 0;
        hash<K> key_hash;
        list<pair<K, V>> *backingStore = nullptr;
        
        // Shift all of the items in backingStore into a
        // new backing store of size cap, or create
        // the backingStore for the first time
        void resize(int cap) {
            // If empty, make BS at capacity
            if (backingStore == nullptr) {
                list<pair<K, V>>* newBS = new list<pair<K, V>>[cap];
                capacity = cap;
                return;
            }

            // otherwise create newBS, go thru old entries and put them to new w new capcity
            list<pair<K, V>>* newBS = new list<pair<K, V>>[cap];
            for (size_t i = 0; i < capacity; i++) {
                // Get old KV
                K key = backingStore[i].first;
                V value = backingStore[i].second;

                // Add old KV to new BS
                newBS[hashKey(key) % cap].put(key, value);
            }

            // Delete old and change to new?
            capacity = cap;
        }
        
        // hash anything into an integer appropriate for
        // the current capacity
        // TIP: use the std::hash key_hash defined as a private variable
        size_t hashKey(const K &key) {
            return key_hash(key);
        }
    };
    
}

#endif /* hashtable_hpp */
