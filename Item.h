#include<bits/stdc++.h>
#include "Date.h"
using namespace std;

class Item {
  public:
    int id;
    string name;
    float price;
    Date expiry_date;
    Item(string _name, float _price, Date _expiry_date);
};

class ItemUtils {
    static long long newId();
    static long long getLastId();
    friend class Item;
};
