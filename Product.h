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
    int id;
    string name;
    string category;
    float price;
    int stock;
    Date expiry_date;
    ProductNode(string _name, string _category, float _price, int _stock, Date _expiry_date, int id);
    friend ostream& operator<< (ostream& os, const ProductNode& node);
};

class CategoryNode {
  public:
    int key;
    string name;
    AVL<ProductNode, int>* products_tree;
    CategoryNode(string _name, int _key, AVL<ProductNode, int>* products);
    AVL<ProductNode, int>* getProductsTree();
};

class Products {
    private:
        json products_json;
        HashMap<CategoryNode*> categories;
        BPTree<ProductNode, float> prices;
        PriorityQueue<ProductNode, Date> expiry;
        HashMap<int> stocks;
        int last_id;
        int getCategoryKey(string category);
    public:
        Products();
        int addProduct(string name, string category, float price, int stock, Date expiry_date);
        void removeProduct(int id);
        string searchById(int id);
        string searchByPrice(float start, float end);
        string getLastExpiry();
        void printAll(string category);
        void removeExpired();
        string getCategory(int id);
        bool addStock(int id, int n);
        int getStock(int id);
        void saveData();
};

ProductNode::ProductNode(string _name, string _category, float _price, int _stock, Date _expiry_date, int _id) {
  name = _name;
  category = _category;
  price = _price;
  stock = _stock;
  expiry_date = _expiry_date;
  id = _id;
}

ostream& operator<< (ostream& os, const ProductNode& node) {
    os << node.name << "\t" << node.category << "\t" << node.price << "\t" << node.stock << "\t" << node.expiry_date.toString();
    return os;
}

CategoryNode::CategoryNode(string _name, int _key, AVL<ProductNode, int>* products) {
    name = _name;
    key = _key;
    products_tree = products;
}

AVL<ProductNode, int>* CategoryNode::getProductsTree() {
    return products_tree;
}

Products::Products(): categories(1000), prices(5), expiry(), stocks(1000) {

    json data = Utils::readJson("Products_data.json");
    if (data == NULL) {
        json temp;
        temp["last_id"] = "10000";
        temp["categories"] = {};
        data = temp;
        Utils::writeJson("Products_data.json", data);
        data = Utils::readJson("Products_data.json");
    }

    if(data.contains("last_id"))
        last_id = stoi(data["last_id"].get<std::string>());
    else
        last_id = 10000;

    products_json = data["categories"];

    for (auto it = products_json.begin(); it != products_json.end(); ++it){
        string c_id = it.key();
        json c = products_json[c_id];
        int key = Products::getCategoryKey(c_id);
        AVL<ProductNode, int>* products = new AVL<ProductNode, int>();

        for (auto it2 = c.begin(); it2 != c.end(); ++it2){
            string id = it2.key();
            json p = products_json[c_id][id];
            ProductNode* product = new ProductNode(p["name"], c_id, stof((string)p["price"]), stoi((string)p["stock"]), Date(p["expiry_date"]), stoi(id));
            products->addItem(product, stoi(id));
            prices.addItem(product, stof((string)p["price"]));
            expiry.push(product, Date(p["expiry_date"]));
            stocks.insertItem(stoi((string)p["stock"]), stoi(id));
        }
        CategoryNode* category = new CategoryNode(c_id, key, products);
        categories.insertItem(category, key);
    }
}

int Products::addProduct(string name, string category_name, float price, int stock, Date expiry_date) {
    ProductNode* product = new ProductNode(name, category_name, price, stock, expiry_date, last_id);
    int key = getCategoryKey(category_name);
    CategoryNode* c = categories.getItem(key);
    if (c == NULL) {
        AVL<ProductNode, int>* products = new AVL<ProductNode, int>();
        products->addItem(product, last_id);
        CategoryNode* category = new CategoryNode(category_name, key, products);
        categories.insertItem(category, key);
        prices.addItem(product, price);
        expiry.push(product, expiry_date);
        stocks.insertItem(stock, last_id);
    }
    else {
        AVL<ProductNode, int>* products = c->getProductsTree();
        products->addItem(product, last_id);
        prices.addItem(product, price);
        expiry.push(product, expiry_date);
        stocks.insertItem(stock, last_id);
    }

    products_json[category_name][to_string(last_id)] = { {"name", name}, {"price", to_string(price)}, {"stock", to_string(stock)}, {"expiry_date", expiry_date.toString()}};
    return last_id++;
}

void Products::removeProduct(int id) {
    string category = getCategory(id);
    int key = getCategoryKey(category);
    CategoryNode* c = categories.getItem(key);
    if (c == NULL) return;
    AVL<ProductNode, int>* products = c->getProductsTree();
    ProductNode* product = products->searchItem(id);
    //prices.removeItem(product, product->price);
    //expiry.removeItem(product, product->expiry_date);
    products->removeItem(id);
    products_json[category].erase(to_string(id));
}

string Products::searchById(int id) {
    ArrayList<CategoryNode*>** category_list = categories.getAll();
    string ret = "";

    for(int i = 0; i < 1000; i++) {
        if(category_list[i] != NULL) {
            int cnt = category_list[i]->getSize();
            for(int j = 0; j < cnt; j++) {
                AVL<ProductNode, int>* products = category_list[i]->getItem(j)->getProductsTree();
                ProductNode* product = products->searchItem(id);
                if(product != NULL) {
                    ret = "Name: " + product->name + "\n";
                    ret = ret + "Category: " + product->category + "\n";
                    ret = ret + "Price: " + to_string(product->price) + "\n";
                    ret = ret + "Stock: " + to_string(product->stock) + "\n";
                    ret = ret + "Expiry date: " + product->expiry_date.toString() + "\n";
                    return ret;
                }
            }
        }
    }
    return "N/A";
}

string Products::searchByPrice(float start, float end) {
    ArrayList<ProductNode*>* result = prices.searchRange(start, end);
    int i = 0;
    string ret = "Product\tPrice\n";
    while(result->getItem(i) != NULL) {
        ProductNode* p = result->getItem(i);
        if(searchById(p->id) != "N/A") {
            ret += p->name;
            ret += "\t";
            ret += to_string(p->price);
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
        return product->name + ": " + product->expiry_date.toString();
    }
    else{
        return "N/A";
    }
}

void Products::printAll(string category) {
    int key = getCategoryKey(category);
    CategoryNode* c = categories.getItem(key);
    if (c == NULL) {
        cout << "Invalid category" << endl;
        return;
    }
    AVL<ProductNode, int>* products = c->getProductsTree();

    cout << "Name\tCategory\tPrice\tStock\tExpiry date" << endl;
    products->printAll();
}

void Products::removeExpired() {
    ProductNode* product = expiry.peek();
    removeProduct(product->id);
    expiry.pop();
    return;
}

bool Products::addStock(int id, int n) {
    if(searchById(id) == "N/A") return false;
    else {
        int stock = stocks.getItem(id);
        stocks.updateItem(id, stock + n);

        int key = getCategoryKey(getCategory(id));
        CategoryNode* c = categories.getItem(key);
        c->getProductsTree()->searchItem(id)->stock += n;

        products_json[getCategory(id)][to_string(id)]["stock"] = to_string(stock + n);
    }
}

int Products::getStock(int id) {
    if(searchById(id) == "N/A") return 0;
    return stocks.getItem(id);
}

string Products::getCategory(int id) {
    ArrayList<CategoryNode*>** category_list = categories.getAll();
    for(int i = 0; i < 1000; i++) {
        if(category_list[i] != NULL) {
            int cnt = category_list[i]->getSize();
            for(int j = 0; j < cnt; j++) {
                AVL<ProductNode, int>* products = category_list[i]->getItem(j)->getProductsTree();
                ProductNode* product = products->searchItem(id);
                if(product != NULL) {
                    return category_list[i]->getItem(j)->name;
                }
            }
        }
    }
    return "N/A";
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
