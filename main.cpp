#include <iostream>
#include "Product.h"
#include "Customer.h"
#include "Purchase.h"
#include "Date.h";

using namespace std;

Products products;
Customers customers;
Purchases purchases;

void clear_screen() {
    #ifdef WINDOWS
        system("cls");
    #else
        system ("clear");
    #endif
    return;
}

void add_product_screen();
void delete_product_screen();
void search_id_product_screen();
void search_price_product_screen();
void check_expiry_product_screen();
void display_product_screen();
void add_customer_screen();
void remove_customer_screen();
void search_id_customer_screen();
void add_purchase_screen();
void print_purchase_screen();

void products_screen() {
    int option;
    clear_screen();
    cout << "Choose an option:" << endl;
    cout << "1: Add product" << endl;
    cout << "2: Delete product" << endl;
    cout << "3: Search products by ID" << endl;
    cout << "4: Search products by price range" << endl;
    cout << "5: Check expiry dates" << endl;
    cout << "6: Display products in a category" << endl;
    cout << "7: Go back" << endl;
    cin >> option;

    switch(option) {
        case 1:
            add_product_screen();
            break;
        case 2:
            delete_product_screen();
            break;
        case 3:
            search_id_product_screen();
            break;
        case 4:
            search_price_product_screen();
            break;
        case 5:
            check_expiry_product_screen();
            break;
        case 6:
            display_product_screen();
            break;
        case 7:
            return;
        default:
            cout << "Invalid option" << endl;
    }
    products_screen();
}

void add_product_screen() {
    string name, category, date_string;
    float price;

    clear_screen();

    cout << "Enter the following details:" << endl;
    cout << "Name: ";
    cin >> name;

    cout << "Category: ";
    cin >> category;

    cout << "Price: ";
    cin >> price;

    cout << "Expiry date (dd-mm-yyyy): ";
    cin >> date_string;
    cout << endl;

    long long id = products.addProduct(name, category, price, Date(date_string));

    int option;

    cout << "Product added: " << id << endl;
    cout << "Press 1 to return" << endl;
    cin >> option;

    return;
}


void delete_product_screen() {
    long long id;
    string category;

    clear_screen();

    Delete_Product:

    cout << "Enter the product category: ";
    cin >> category;

    cout << "Enter the product ID to delete: ";
    cin >> id;
    cout << endl;

    if(products.searchById(id) == "N/A") {
        cout << "Invalid ID" << endl;
        goto Delete_Product;
    }

    products.removeProduct(category, id);

    int option;
    cout << "Product deleted" << endl;
    cout << "Press 1 to return" << endl;
    cin >> option;

    return;
}

void search_id_product_screen() {
    long long id;

    clear_screen();

    cout << "Enter the product ID: ";
    cin >> id;
    cout << endl;

    cout << products.searchById(id) << endl << endl;

    int option;
    cout << "Press 1 to return" << endl;
    cin >> option;

    return;
}

void search_price_product_screen() {
    float start, end;

    clear_screen();

    cout << "Enter the starting price: ";
    cin >> start;

    cout << "Enter the ending price: ";
    cin >> end;
    cout << endl;

    cout << products.searchByPrice(start, end) << endl;

    int option;
    cout << "Press 1 to return" << endl;
    cin >> option;

    return;
}

void display_product_screen() {
    string category;

    clear_screen();

    cout << "Enter the product category: ";
    cin >> category;
    cout << endl;

    products.printAll(category);

    cout << endl;

    int option;
    cout << "Press 1 to return" << endl;
    cin >> option;
}

void check_expiry_product_screen() {
    clear_screen();

    Expired:
    cout << products.getLastExpiry() << endl << endl;

    cout << "1: Remove from products" << endl;
    cout << "2: Return" << endl;

    int option;
    cin >> option;

    switch(option) {
        case 1:
            products.removeExpired();
            cout << "Product removed" << endl;
            break;
        case 2:
            return;
    }

    goto Expired;
}

void customers_screen() {
    int option;
    clear_screen();

    cout << "Choose an option:" << endl;
    cout << "1: Add customer" << endl;
    cout << "2: Remove customer" << endl;
    cout << "3: Search customer by ID" << endl;
    cout << "4: Go back" << endl;
    cin >> option;

    switch(option) {
        case 1:
            add_customer_screen();
            break;
        case 2:
            remove_customer_screen();
            break;
        case 3:
            search_id_customer_screen();
            break;
        case 4:
            return;
        default:
            cout << "Invalid option" << endl;
    }
    customers_screen();
}

void add_customer_screen() {
    string first_name, last_name, email, phone;

    clear_screen();

    cout << "Enter the following details:" << endl;
    cout << "First name: ";
    cin >> first_name;

    cout << "Last name: ";
    cin >> last_name;

    cout << "Email: ";
    cin >> email;

    cout << "Phone: ";
    cin >> phone;
    cout << endl;

    long long id = customers.addCustomer(first_name, last_name, email, phone);

    int option;

    cout << "Customer added: " << id << endl;
    cout << "Press 1 to return" << endl;
    cin >> option;

    return;
}

void remove_customer_screen() {
    long long id;

    clear_screen();

    Remove_Customer:

    cout << "Enter the customer ID to delete: ";
    cin >> id;
    cout << endl;

    if(customers.searchCustomer(id) == "N/A") {
        cout << "Invalid ID" << endl;
        goto Remove_Customer;
    }

    customers.removeCustomer(id);

    int option;
    cout << "Customer deleted" << endl;
    cout << "Press 1 to return" << endl;
    cin >> option;

    return;
}

void search_id_customer_screen() {
    long long id;

    clear_screen();

    cout << "Enter the cusomter ID: ";
    cin >> id;
    cout << endl;

    cout << customers.searchCustomer(id) << endl << endl;

    int option;
    cout << "Press 1 to return" << endl;
    cin >> option;

    return;
}

void purchases_screen() {
    int option;
    clear_screen();

    cout << "Choose an option:" << endl;
    cout << "1: Add purchase" << endl;
    cout << "2: Customer history" << endl;
    cout << "3: Go back" << endl;
    cin >> option;

    switch(option) {
        case 1:
            add_purchase_screen();
            break;
        case 2:
            print_purchase_screen();
            break;
        case 3:
            return;
        default:
            cout << "Invalid option" << endl;
    }
    purchases_screen();
}

void add_purchase_screen() {
    long long id;

    clear_screen();

    Add_Purchase:

    cout << "Enter the customer ID: ";
    cin >> id;
    cout << endl;

    if(customers.searchCustomer(id) == "N/A") {
        cout << "Invalid ID" << endl;
        goto Add_Purchase;
    }

    purchases.addPurchase(id);

    int option;

    cout << "Purchase recorded" << endl;
    cout << "Press 1 to return" << endl;
    cin >> option;

    return;
}

void quit_screen() {
    products.saveData();
    purchases.saveData();
    customers.saveData();

    cout << "Changes saved" << endl;
}

void print_purchase_screen() {
    clear_screen();

    purchases.printPurchases();
    cout << endl;

    int option;
    cout << "Press 1 to return" << endl;
    cin >> option;

    return;
}

int main() {

    Start:

    clear_screen();

    cout << "Hello Agwad!" << endl;

    int option;
    cout << "Choose an option:" << endl;
    cout << "1: Manage products" << endl;
    cout << "2: Manage customers" << endl;
    cout << "3: Manage purchases" << endl;
    cout << "4: Quit" << endl;
    cin >> option;

    switch(option) {
        case 1:
            products_screen();
            break;
        case 2:
            customers_screen();
            break;
        case 3:
            purchases_screen();
            break;
        case 4:
            quit_screen();
            return 0;
        default:
            cout << "Invalid option" << endl;
    }

    goto Start;

    return 0;
}
