#include<bits/stdc++.h>
#include "json.hpp"
#include "AVL.h"
#include "Utils.h"

using json = nlohmann::json;

using namespace std;

class CustomerNode {
    long long id;
    string first_name;
    string last_name;
    string email;
    string phone;

    CustomerNode(string _first_name,
        string _last_name,
        string _email,
        string _phone,
        long long _id);

    friend class Customers;
};

class Customers {

    private:
        json customers_json;
        AVL<CustomerNode, long long> customers;
        long long last_id;

    public:
        Customers();
        long long addCustomer(string first_name, string last_name, string email, string phone);
        void removeCustomer(long long id);
        string searchCustomer(long long id);
        void saveData();
};


CustomerNode::CustomerNode(string _first_name,
          string _last_name,
          string _email,
          string _phone,
          long long _id) {

  first_name = _first_name;
  last_name = _last_name;
  email = _email;
  phone = _phone;
  id = _id;
}

Customers::Customers(): customers() {

    json data = Utils::readJson("Customers_data.json");
    if (data == NULL) {
        json temp;
        temp["last_id"] = "10000000";
        temp["customers"] = {};
        data = temp;
        Utils::writeJson("Customers_data.json", data);
        data = Utils::readJson("Customers_data.json");
    }

    if(data.contains("last_id"))
        last_id = stoll(data["last_id"].get<std::string>());
    else
        last_id = 10000000;

    customers_json = data["customers"];

    for (auto it = customers_json.begin(); it != customers_json.end(); ++it){
        string id = it.key();
        json c = customers_json[id];
        CustomerNode* customer = new CustomerNode(c["first_name"], c["last_name"], c["email"], c["phone"], stoll(id));
        customers.addItem(customer, stoll(id));
    }

}

long long Customers::addCustomer(string first_name, string last_name, string email, string phone) {
    CustomerNode* customer = new CustomerNode(first_name, last_name, email, phone, last_id);
    customers.addItem(customer, last_id);
    customers_json[to_string(last_id)] = { {"first_name", first_name}, {"last_name", last_name}, {"email", email}, {"phone", phone} };
    return last_id++;
}

void Customers::removeCustomer(long long id) {
    customers.removeItem(id);
    customers_json.erase(to_string(id));
}

string Customers::searchCustomer(long long id) {
    CustomerNode* customer = customers.searchItem(id);
    if(customer != NULL) return customer->first_name + " " + customer->last_name;
    else return "N/A";
}

void Customers::saveData() {
    json data;
    data["last_id"] = to_string(last_id);
    data["customers"] = customers_json;
    Utils::writeJson("Customers_data.json", data);
}
