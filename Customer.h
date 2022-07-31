#include<bits/stdc++.h>
#include "json.hpp"
#include "AVL.h"
#include "Utils.h"

using json = nlohmann::json;

using namespace std;

class CustomerNode {
    int id;
    string first_name;
    string last_name;
    string email;
    string phone;

    CustomerNode(string _first_name,
        string _last_name,
        string _email,
        string _phone,
        int _id);

    friend class Customers;
};

class Customers {

    private:
        json customers_json;
        AVL<CustomerNode, int> customers;
        int last_id;

    public:
        Customers();
        int addCustomer(string first_name, string last_name, string email, string phone);
        void removeCustomer(int id);
        string searchCustomer(int id);
        void saveData();
};


CustomerNode::CustomerNode(string _first_name,
          string _last_name,
          string _email,
          string _phone,
          int _id) {

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
        temp["last_id"] = "10000";
        temp["customers"] = {};
        data = temp;
        Utils::writeJson("Customers_data.json", data);
        data = Utils::readJson("Customers_data.json");
    }

    if(data.contains("last_id"))
        last_id = stoi(data["last_id"].get<std::string>());
    else
        last_id = 10000;

    customers_json = data["customers"];

    for (auto it = customers_json.begin(); it != customers_json.end(); ++it){
        string id = it.key();
        json c = customers_json[id];
        CustomerNode* customer = new CustomerNode(c["first_name"], c["last_name"], c["email"], c["phone"], stoi(id));
        customers.addItem(customer, stoi(id));
    }

}

int Customers::addCustomer(string first_name, string last_name, string email, string phone) {
    CustomerNode* customer = new CustomerNode(first_name, last_name, email, phone, last_id);
    customers.addItem(customer, last_id);
    customers_json[to_string(last_id)] = { {"first_name", first_name}, {"last_name", last_name}, {"email", email}, {"phone", phone} };
    return last_id++;
}

void Customers::removeCustomer(int id) {
    customers.removeItem(id);
    customers_json.erase(to_string(id));
}

string Customers::searchCustomer(int id) {
    CustomerNode* customer = customers.searchItem(id);
    string ret = "";
    if(customer != NULL) {
        ret = "First name: " + customer->first_name + "\n";
        ret = ret + "Last name: " + customer->last_name + "\n";
        ret = ret + "Email: " + customer->email + "\n";
        ret = ret + "Phone: " + customer->phone + "\n";
        return ret;
    }
    else return "N/A";
}

void Customers::saveData() {
    json data;
    data["last_id"] = to_string(last_id);
    data["customers"] = customers_json;
    Utils::writeJson("Customers_data.json", data);
}
