#include "Customer.h"
using namespace std;

Customer::Customer(string _first_name,
          string _last_name,
          string _email,
          string _phone) {

  first_name = _first_name;
  last_name = _last_name;
  email = _email;
  phone = _phone;

  id = CustomerUtils::newId();
}

long long CustomerUtils::newId() {
  long long last_id = getLastId() + 1;
  return 0;
}

long long CustomerUtils::getLastId() {
  //return Json.read();
  return 0;
}
