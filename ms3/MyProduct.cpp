// Final Project Milestone 3
// Version 2.0.1
// Date	2017-12-06
// Authors	Fardad Soleimanloo, Chris Szalwinski
//
// For you final test before submission:
//      DO NOT MODIFY THIS FILE IN ANY WAY
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Chris              2017-12-02           Streamable -> Product
// Chris              2017-12-06           C++17 -> C++11
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "MyProduct.h"
using namespace std;

namespace sict{

  Product* CreateProduct() {
	return new MyProduct("non-perishable");
  }
  Product* CreatePerishable() {
	  return new MyProduct("perishable");
  }
  MyProduct::MyProduct(const char* n) {
	value = 0;
	strcpy(sku, "sku");
    text_[0] = char(0);
	strcpy(name_, n);
  }
  fstream& MyProduct::store(std::fstream& file, bool addNewLine)const{
    int i = 0;
    while (text_[i]){
      file << text_[i];
      i++;
    }
    return file;
  }
  fstream& MyProduct::load(std::fstream& file){
    int i=0;
    while (!file.fail()){
      text_[i++] = file.get();
    }
    file.clear();
    if(i > 0) i--;
    text_[i] = 0;
    return file;
  }
  ostream& MyProduct::write(std::ostream& os, bool linear)const{
    for (int i = 0; text_[i]; i++){
      if (linear && text_[i] == '\n'){
        os << " ";
      }
      else{
        os << text_[i];
      }
    }
    return os;
  }
  istream& MyProduct::read(std::istream& is){
    is.getline(text_, 9999, EOF);
    return is;
  }
  std::ostream& operator<<(std::ostream& ostr, const Product& mf){
    return mf.write(ostr, true);
  }
  std::istream& operator>>(std::istream& istr, Product& mf){
    return mf.read(istr);
  }
  bool MyProduct::operator==(const char* str) const { 
	  return !strcmp(sku, str); 
  }
  double MyProduct::total_cost() const { 
	  return 113.50; 
  }
  const char* MyProduct::name() const { 
	  return name_; 
  }
  void MyProduct::quantity(int i) { 
	  value = i; 
  }
  int MyProduct::qtyNeeded() const { 
	  return 45; 
  }
  int MyProduct::quantity() const { 
	  return value;  
  }
  int MyProduct::operator+=(int i) { 
	  value += i;
	  return value;
  }
  double operator+=(double& d, const Product& p) {
	  d += p.total_cost();
	  return d;
  }
  bool MyProduct::operator>(const Product& p) const { 
	  return !strcmp(name_, p.name()); 
  }
}