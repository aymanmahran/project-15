#include <iostream>
#include "Product.h"
#include "Customer.h"
#include "Purchase.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    /*Products products;
    cout << products.searchByPrice(11, 13);
    //products.removeProduct("Drinks", 10000002);
    cout <<endl;
    cout << products.searchByPrice(11, 13);

    cout << products.getLastExpiry();
    products.removeExpired();
    cout << products.getLastExpiry();*/

    Purchases purchases;
    //for(int i=0;i<10;i++)
    //    purchases.addPurchase(10000 + i);

    purchases.printPurchases();
    //purchases.addPurchase(10000 + 10);
    //purchases.printPurchases();
   // purchases.saveData();

   long long id = products.addProduct("Chicken", "Meat", 10.0, Date(5, 7, 2022));
   // id = products.addProduct("Beef", "Meat", 10.0, Date(5, 7, 2022));
    //long long id = 10000004;
    //products.deleteProduct("Meat", id);
    // products.saveData();
   // Customers customers;
   // long long id = customers.addCustomer("usef", "afef", "aa@a.ca", "70219");
   // long long id2 = customers.addCustomer("amro", "gmal", "aa.ca", "219");
   // customers.deleteCustomer(10000002);
   // customers.saveData();

    return 0;
}
