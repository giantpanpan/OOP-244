// Final Project Milestone 3
// Version 2.0
// Date	2017-12-02
// Authors	Fardad Soleimanloo, Chris Szalwinski
//
// For your final test before submission:
//      DO NOT MODIFY THIS FILE IN ANY WAY
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Chris              2017-12-02           Streamable -> Product
/////////////////////////////////////////////////////////////////
#include <iostream>
#include "Product.h"
using namespace std;
using namespace sict;
#define FILE "product.txt" // file of records
#if defined(_MSC_VER)
#define END_OF_FILE "Ctrl^Z"
#else
#define END_OF_FILE "Ctrl^D"
#endif

int main() { 
  // create and populate the file of records
  fstream file(FILE, ios::out);
  file << "one" << endl << "two" << endl;
  file.close();

  // create a Product without records
  Product* product = CreateProduct();

  // populate the product with records from file
  file.open(FILE, ios::in);
  product->load(file);
  file.close();
  // display the product records 
  // - in linear form 
  cout << "Linear: " << *product << endl;
  // - one record per line
  cout << "As is: " << endl;
  product->write(cout, false);
  cout << endl;

  // enter additional product records from the console
  cout << "Enter the following: " << endl << "three<ENTER>" << endl << "four<ENTER>" << endl;
  cout << END_OF_FILE << "<ENTER>" << endl << endl;
  cin >> *product;
  // append these product records to file
  file.open(FILE, ios::app | ios::out);
  product->store(file, true);
  file.close();

  // load the stored product records from file
  file.open(FILE, ios::in);
  product->load(file);
  file.close();
  // display the loaded records in linear form
  cout << *product << endl;
  product->write(cout, false);
  cout << endl;

  // check operators
  Product* perishable = CreatePerishable();
  if (*product == "sku")
	  cout << "sku match" << endl;
  else
	  cout << "sku mismatch" << endl;
  if (*product > *perishable)
	  cout << product->name() << " > " << perishable->name() << endl;
  else
	  cout << product->name() << " < " << perishable->name() << endl;

  // set and check product quantities
  product->quantity(32);
  cout << product->qtyNeeded() << '|' << product->quantity();
  cout << '|' << (*product += 99) << '|' << product->quantity() << endl;

  // check product cost
  double total_cost = 0.0;
  total_cost += *product;
  cout.setf(ios::fixed);
  cout.precision(1);
  cout << total_cost << endl;

  // deallocate
  delete product;
  delete perishable;
  return 0;
}