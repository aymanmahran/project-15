#ifndef PURCHASE_H_INCLUDED
#define PURCHASE_H_INCLUDED

#include<bits/stdc++.h>
#include "json.hpp"
#include "CircularQueue.h"
#include "Utils.h"

using json = nlohmann::json;

using namespace std;

class PurchaseNode {
    public:
        long long customer_id;
        PurchaseNode(long long _customer_id);
};

class Purchases {

    private:
        CircularQueue<PurchaseNode> purchases;
        json purchases_json;

    public:
        Purchases();
        void addPurchase(long long id);
        void printPurchases();
        void saveData();
};


PurchaseNode::PurchaseNode(long long _customer_id) {
    customer_id = _customer_id;
}

Purchases::Purchases(): purchases(10) {

    json data = Utils::readJson("Purchases_data.json");
    if (data == NULL) {
        json temp;
        temp["purchases"] = {};
        data = temp;
        Utils::writeJson("Purchases_data.json", data);
        data = Utils::readJson("Purchases_data.json");
    }

    purchases_json = data["purchases"];

    for (auto it = purchases_json.begin(); it != purchases_json.end(); ++it){
        string s = (string) it.value();
        if(s == "") continue;
        long long id = stoll(s);
        PurchaseNode* purchase = new PurchaseNode(id);
        purchases.enqueue(purchase);
    }
}

void Purchases::addPurchase(long long customer_id) {
    PurchaseNode* purchase = new PurchaseNode(customer_id);
    purchases.enqueue(purchase);
    PurchaseNode** cq = purchases.getAll();
    string data[10];
    for(int i = 0; i < 10; i++) {
        if(cq[i] != NULL)
            data[i] = to_string(cq[i]->customer_id);
    }
    purchases_json = data;
}

void Purchases::printPurchases() {
    PurchaseNode** cq = purchases.getAll();
    for(int i = 9; i >= 0; i--) {
        if(cq[i] != NULL)
            cout << cq[i]->customer_id << endl;
    }
}

void Purchases::saveData() {
    json data;
    data["purchases"] = purchases_json;
    Utils::writeJson("Purchases_data.json", data);
}

#endif
