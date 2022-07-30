#include<bits/stdc++.h>
#include "Date.h"
#include "json.hpp"
#include "Utils.h"
#include "AVL.h"
#include "HashMap.h"
#include "BPlusTree.h"
#include "PriorityQueue.h"

using namespace std;
using json = nlohmann::json;

class ProductNode {
  public:
    long long id;
    string name;
    float price;
    Date expiry_date;
    ProductNode(string _name, float _price, Date _expiry_date, long long id);
};

class CategoryNode {
  public:
    int key;
    string name;
    AVL<ProductNode, long long>* products_tree;
    CategoryNode(string _name, int _key, AVL<ProductNode, long long>* products);
    AVL<ProductNode, long long>* getProductsTree();
};

class Products {
    private:
        json products_json;
        HashMap<CategoryNode> categories;
        BPTree<ProductNode, float> prices;
        PriorityQueue<ProductNode, Date> expiry;
        long long last_id;
        int getCategoryKey(string category);
    public:
        Products();
        long long addProduct(string name, string category, float price, Date expiry_date);
        void removeProduct(string category, long long id);
        string searchById(long long id);
        string searchByPrice(float start, float end);
        string getLastExpiry();
        void removeExpired();
        void saveData();
};

ProductNode::ProductNode(string _name, float _price, Date _expiry_date, long long _id) {
  name = _name;
  price = _price;
  expiry_date = _expiry_date;
  id = _id;
}

CategoryNode::CategoryNode(string _name, int _key, AVL<ProductNode, long long>* products) {
    name = _name;
    key = _key;
    products_tree = products;
}

AVL<ProductNode, long long>* CategoryNode::getProductsTree() {
    return products_tree;
}

Products::Products(): categories(1000), prices(5), expiry() {

    json data = Utils::readJson("Products_data.json");
    if (data == NULL) {
        json temp;
        temp["last_id"] = "10000000";
        temp["categories"] = {};
        data = temp;
        Utils::writeJson("Products_data.json", data);
        data = Utils::readJson("Products_data.json");
    }

    if(data.contains("last_id"))
        last_id = stoll(data["last_id"].get<std::string>());
    else
        last_id = 10000000;

    products_json = data["categories"];

    for (auto it = products_json.begin(); it != products_json.end(); ++it){
        string c_id = it.key();
        json c = products_json[c_id];
        int key = Products::getCategoryKey(c_id);
        AVL<ProductNode, long long>* products = new AVL<ProductNode, long long>();

         for (auto it2 = c.begin(); it2 != c.end(); ++it2){
            string id = it2.key();
            json p = products_json[c_id][id];
            ProductNode* product = new ProductNode(p["name"], stof((string)p["price"]), Date(p["expiry_date"]), stoll(id));
            products->addItem(product, stoll(id));
            prices.addItem(product, stof((string)p["price"]));
            expiry.push(product, Date(p["expiry_date"]));
        }
        CategoryNode* category = new CategoryNode(c_id, key, products);
        categories.insertItem(category, key);
    }
}

long long Products::addProduct(string name, string category_name, float price, Date expiry_date) {
    ProductNode* product = new ProductNode(name, price, expiry_date, last_id);
    int key = getCategoryKey(category_name);
    CategoryNode* c = categories.getItem(key);
    if (c == NULL) {
        AVL<ProductNode, long long>* products = new AVL<ProductNode, long long>();
        products->addItem(product, last_id);
        CategoryNode* category = new CategoryNode(category_name, key, products);
        categories.insertItem(category, key);
        prices.addItem(product, price);
        expiry.push(product, expiry_date);
    }
    else {
        AVL<ProductNode, long long>* products = c->getProductsTree();
        products->addItem(product, last_id);
        prices.addItem(product, price);
        expiry.push(product, expiry_date);
    }

    products_json[category_name][to_string(last_id)] = { {"name", name}, {"price", to_string(price)}, {"expiry_date", expiry_date.toString()}};
    return last_id++;
}

void Products::removeProduct(string category, long long id) {
    int key = getCategoryKey(category);
    CategoryNode* c = categories.getItem(key);
    if (c == NULL) return;
    AVL<ProductNode, long long>* products = c->getProductsTree();
    ProductNode* product = products->searchItem(id);
    //prices.removeItem(product, product->price);
    //expiry.removeItem(product, product->expiry_date);
    products->removeItem(id);
    products_json[category].erase(to_string(id));
}

string Products::searchById(long long id) {
    CategoryNode** category_list = categories.getAll();
    for(int i = 0; i < 1000; i++) {
        if(category_list[i] != NULL) {
            AVL<ProductNode, long long>* products = category_list[i]->getProductsTree();
            ProductNode* product = products->searchItem(id);
            if(product != NULL) {
                return product->name + " " + to_string(product->price);
            }
        }
    }
    return "N/A";
}

string Products::searchByPrice(float start, float end) {
    ProductNode** result = prices.searchRange(start, end);
    int i = 0;
    string ret = "";
    while(result[i] != NULL) {
        if(searchById(result[i]->id) != "N/A") {
            ret += result[i]->name;
            ret += "\n";
        }
        i++;
    }
    if(ret == "") return "N/A";
    return ret;
}

string Products::getLastExpiry() {
    ProductNode* product = expiry.peek();
    while(searchById(product->id) == "N/A") {
        expiry.pop();
        product = expiry.peek();
    }

    if(product != NULL) {
        return product->name;
    }
    else{
        return "N/A";
    }
}

void Products::removeExpired() {
    expiry.pop();
    return;
}

void Products::saveData() {
    json data;
    data["last_id"] = to_string(last_id);
    data["categories"] = products_json;
    Utils::writeJson("Products_data.json", data);
}

int Products::getCategoryKey(string category) {
    int key = 0;
    for(int i = 0; i < category.size(); i++) {
        key += (int) category[i];
    }
    return key;
}
