#include "Item.h"
#include "Date.h"

Item::Item(string _name, float _price, Date _expiry_date) {
  name = _name;
  price = _price;
  expiry_date = _expiry_date;
  id = ItemUtils::newId();
}

long long ItemUtils::newId() {
  long long new_id = getLastId() + 1;
  return new_id;
}

long long ItemUtils::getLastId() {
  //return Json.read();
  return 0;
}
