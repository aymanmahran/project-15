#include<bits/stdc++.h>
using namespace std;

class Customer {
    long long id;
    string first_name;
    string last_name;
    string email;
    string phone;

    Customer(string _first_name,
        string _last_name,
        string _email,
        string _phone);
};

class CustomerUtils {
    static long long newId();
    static long long getLastId();
    friend class Customer;
};
