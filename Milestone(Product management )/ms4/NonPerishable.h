#ifndef SICT_NONPERISHABLE_H
#define SICT_NONPERISHABLE_H

#include <fstream>
#include "Product.h"
#include "ErrorMessage.h"

namespace sict
{
	const int max_sku_length = 7;
	const int max_unit_lenght = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;


	class NonPerishable : public Product
	{
	private:
		char m_productType[1];
		char m_productSku[max_sku_length];
		char* m_productName;
		char m_unit[max_unit_lenght];
		int m_CurrQuantity;
		int m_NeededQuantity;
		double m_PriceOrigin;
		bool m_taxOrnot;
		ErrorMessage m_error;
		void setEmpty();
	protected:
		void name(const char*);
		const char* name() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;
	public:
		NonPerishable(const char* type="x");
		NonPerishable(const char* sku, const char* name, const char* unit, const int quantityC=0, const bool taxornot =true, const double price_o =0, const int quantityN=0, const char* type = "x");
		NonPerishable(const NonPerishable& src);
		NonPerishable& operator= (const NonPerishable& src);
		~NonPerishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		int operator+=(int);
		bool operator>(const Product&) const;
	};
	std::ostream& operator<<(std::ostream&, const Product&);
	std::istream& operator>>(std::istream&, Product&);
	double operator+=(double&, const Product&);
	Product* CreateProduct();
}










#endif // !SICT_NONPERISHABLE_H

