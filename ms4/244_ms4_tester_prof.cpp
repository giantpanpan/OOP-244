// Final Project Milestone 4
// Version 2.0
// Date	2017-12-06
// Author	Fardad Soleimanloo, Chris Szalwinski
//
// For you final test before submission:
//      DO NOT MODIFY THIS FILE IN ANY WAY
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include "ErrorMessage.h"
#include "NonPerishable.h"
#ifdef TAB
# undef TAB
#endif
#define TAB '\t'
#define filename "ms4.txt"
using namespace std;

namespace sict {
  class Test : public NonPerishable {
	  char sku_[max_sku_length + 1];
	  double price_;
	  int taxed_;
  public:
	  Test() { sku_[0] = '\0'; price_ = 0.0; taxed_ = 1; }
    Test(const char* theSku, const char * theName) : NonPerishable(theSku, theName, "") {
		strncpy(sku_, theSku, max_sku_length);
		sku_[max_sku_length] = '\0';
	}
    virtual std::fstream& store(std::fstream& file, bool addNewLine = true) const {
      if (!isEmpty()){
        file.open(filename, ios::out|ios::app);
        file << sku_ << TAB << name() << TAB << quantity() << TAB << qtyNeeded() << TAB
          << taxed_ << TAB << price_ << endl;
        file.clear();
        file.close();
      }
      return file;
    }
    virtual std::fstream& load(std::fstream& file) {
	  char name[max_name_length + 1];
	  int quantity, qtyNeeded;
      file.open("ms4.txt", ios::in);
	  file >> sku_;
	  file >> name;
	  file >> quantity;
	  file >> qtyNeeded;
	  file >> taxed_;
	  file >> price_;
	  (NonPerishable&)*this = NonPerishable(sku_, name, "", quantity, taxed_ != 0, price_, qtyNeeded);
	  file.clear();
      file.close();
      return file;
    }
    virtual std::ostream& write(std::ostream& os, bool linear) const {
      return isEmpty() ? os : (os << sku_ << ": " << name() << ", quantity: " 
        << quantity() << ", quantity needed:" << qtyNeeded() 
        <<", Cost: " << fixed << setprecision(2) << cost());
    }
    virtual std::istream& read(std::istream& is) {
	  char name[max_name_length + 1];
	  int quantity, qtyNeeded;
      cout << " Sku: ";
      is >> sku_;
      cout << " Name (no spaces): ";
      is >> name;
      cout << " Quantity: ";
      is >> quantity;
      cout << " Quantity Needed: ";
      is >> qtyNeeded;
      cout << " Is taxed? (1/0): ";
      is >> taxed_;
      cout << " Price: ";
      is >> price_;
	  (NonPerishable&)*this = NonPerishable(sku_, name, "", quantity, taxed_ != 0, price_, qtyNeeded);
	  return is;
    }
  };
}
void dumpFile(fstream& f) {
	f.open(filename, ios::in);
	char ch;
	while (!f.get(ch).fail()) {
		cout.put(ch);
	}
	f.clear();
	f.close();
}

using namespace sict;
void test() {
	fstream file(filename, ios::out);
	file.close();
	cout << endl;
	cout << "Enter Product Info: " << endl;
	Test s;
	cin >> s;
	cout << "\nTesting:" << endl;
	cout << " s.store(): " << endl;
	s.store(file);
	cout << "  s: " << s << endl;
	Test t;
	cout << " t.load(): " << endl;
	t.load(file);
	cout << "  t: " << t << endl;
	cout << " X(const X&): X v = s" << endl;
	Test v = s;
	cout << "  v: " << v << endl;
	cout << "  s: " << s << endl;
	cout << " X& operator=(const X&): u = t" << endl;
	Test u;
	u = t;
	cout << "  t: " << t << endl;
	cout << "  u: " << u << endl;
	cout << " bool operator==(const char*) const: ";
	cout << (t == "1234" ? "OK" : "NOT OK") << endl;
	cout << " int operator+=(int): u += 10 " << endl;
	cout << "  u: " << u << endl;
	u += 10;
	cout << "  u: " << u << endl;
	cout << " double operator+=(double&, const Product&) : 200 += u" << endl;
	double res, val = 200.0;
	res = val += u;
	cout << "  ?:" << res << " = " << val << endl;
	cout << endl;
}

int main() {
	fstream file(filename, ios::out);
	file.close();
	Test s;
	Test u("4321", "Rice");
	cout << "Empty Product:" << endl << s << endl;
	cout << "u(\"4321\", \"Rice\"):" << endl << u << endl;
	cout << "Please enter the following information:" << endl;
	cout << " Sku: 1234" << endl;
	cout << " Name(no spaces) : Blanket" << endl;
	cout << " Quantity : 12" << endl;
	cout << " Quantity Needed : 23" << endl;
	cout << " Is taxed ? (1 / 0) : 1" << endl;
	cout << " Price : 12.34" << endl;
	test();
	cout << "Please enter the following information:" << endl;
	cout << " Sku: 1234" << endl;
	cout << " Name(no spaces) : Jacket" << endl;
	cout << " Quantity : 12" << endl;
	cout << " Quantity Needed : 23" << endl;
	cout << " Is taxed ? (1 / 0) : 0" << endl;
	cout << " Price : 12.34" << endl;
	test();
	dumpFile(file);
	cout << "----The End" << endl;
	return 0;
}
