//
//  test.cpp
//
//  Tests to prove your code works.
//  You should NOT modify this file.
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

#include "HashTable.h"
#include "catch.h"
#include <string>
#include <iostream>

using namespace std;
using namespace csi281;

TEST_CASE( "Hash Table w/ string int", "[stringint]" ) {
    SECTION( "basic string int Test" ) {
        // basic checks
        HashTable<string, int> ht1 = HashTable<string, int>();
        ht1.put("dog", 34);
        auto optValue = ht1.get("dog");
        CHECK( optValue.has_value() );
        CHECK( optValue.value() == 34 );
        CHECK( ht1.getCount() == 1 );
        // change value
        ht1.put("dog", 50);
        optValue = ht1.get("dog");
        CHECK( optValue.has_value() );
        CHECK( optValue.value() == 50 );
        CHECK( ht1.getCount() == 1 );
        // remove value
        ht1.remove("dog");
        optValue = ht1.get("dog");
        CHECK( ht1.getCount() == 0 );
        CHECK( !optValue.has_value() );
    }
    
    SECTION( "basic string int Test with resize" ) {
        HashTable<string, int> ht2 = HashTable<string, int>(5);
        ht2.put("dog", 34);
        ht2.put("cat", 234);
        ht2.put("panda", 134);
        cout << "Before Resize" << endl;
        ht2.debugPrint();
        CHECK( ht2.getCapacity() == 5 );
        auto optValue = ht2.get("panda");
        CHECK( optValue.has_value() );
        CHECK( optValue.value() == 134 );
        CHECK( ht2.getCount() == 3 );
        // change cat value
        ht2.put("cat", 334);
        optValue = ht2.get("cat");
        CHECK( optValue.has_value() );
        CHECK( optValue.value() == 334 );
        CHECK( ht2.getCount() == 3 );
        // add one more
        ht2.put("bull", 500);
        cout << "After Resize" << endl;
        ht2.debugPrint();
        // expect a resize because load factor over 0.7
        CHECK( ht2.getCapacity() == 10 );
        CHECK( ht2.getCount() == 4 );
        // check all values still work
        optValue = ht2.get("cat");
        CHECK( optValue.has_value() );
        CHECK( optValue.value() == 334 );
        optValue = ht2.get("dog");
        CHECK( optValue.has_value() );
        CHECK( optValue.value() == 34 );
        optValue = ht2.get("panda");
        CHECK( optValue.has_value() );
        CHECK( optValue.value() == 134 );
        optValue = ht2.get("bull");
        CHECK( optValue.has_value() );
        CHECK( optValue.value() == 500 );
    }
}

TEST_CASE( "Hash Table w/ string string", "[stringstring]" ) {
    SECTION( "50 strings of a test" ) {
        HashTable<string, string> ht1 = HashTable<string, string>(10);
        for (int i = 1; i <= 50; i++) {
            string s = string(i, 'a');
            ht1.put(s, s);
        }
        auto optValue = ht1.get("aaaaaaaaaaa");
        CHECK( optValue.has_value() );
        CHECK( optValue.value() == "aaaaaaaaaaa" );
        CHECK( ht1.getCount() == 50 );
        CHECK( ht1.getCapacity() == 80 );
        // change value
        ht1.put("aaa", "dog");
        optValue = ht1.get("aaa");
        CHECK( optValue.has_value() );
        CHECK( optValue.value() == "dog" );
        CHECK( ht1.getCount() == 50 );
        // remove value
        ht1.remove("a");
        optValue = ht1.get("a");
        CHECK( ht1.getCount() == 49 );
        CHECK( !optValue.has_value() );
        ht1.remove("aaaa");
        optValue = ht1.get("aaaa");
        CHECK( ht1.getCount() == 48 );
        CHECK( !optValue.has_value() );
        CHECK( ht1.getCapacity() == 80 );
    }
}

TEST_CASE( "Hash Table w/ int float", "[intfloat]" ) {
    SECTION( "50 ints with floats" ) {
        HashTable<int, float> ht1 = HashTable<int, float>(10);
        for (int i = 1; i <= 50; i++) {
            float f = (((float) i) * ((float) i) / 3.0);
            ht1.put(i, f);
        }
        auto optValue = ht1.get(27);
        CHECK( optValue.has_value() );
        CHECK( ht1.getCount() == 50 );
        CHECK( ht1.getCapacity() == 80 );
        // change value
        ht1.put(45, 2.5);
        optValue = ht1.get(45);
        CHECK( optValue.has_value() );
        CHECK( optValue.value() == 2.5 );
        CHECK( ht1.getCount() == 50 );
        // remove value
        ht1.remove(48);
        optValue = ht1.get(48);
        CHECK( ht1.getCount() == 49 );
        CHECK( !optValue.has_value() );
        ht1.remove(2);
        optValue = ht1.get(2);
        CHECK( ht1.getCount() == 48 );
        CHECK( !optValue.has_value() );
        CHECK( ht1.getCapacity() == 80 );
    }
}

