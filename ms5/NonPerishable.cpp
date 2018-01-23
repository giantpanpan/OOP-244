#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "NonPerishable.h"

using namespace std;

namespace sict
{
	void NonPerishable::setEmpty()
	{
		this->m_productSku[0] = '\0';
		this->m_productName = nullptr;
		this->m_PriceOrigin = 0;
		this->m_NeededQuantity = 0;
		this->m_CurrQuantity = 0;
		this->m_unit[0] = '\0';
		this->m_taxOrnot = true;
		this->m_error.message("");
	}

	void NonPerishable::name(const char* name)
	{

		if (nullptr != name)
		{
			if (this->m_productName != nullptr)
			{
				delete[] this->m_productName;
				this->m_productName = nullptr;
			}
			int length = strlen(name);
			this->m_productName = new char[length + 1];
			strcpy(this->m_productName, name);
		}
		else
		{
			delete[] this->m_productName;
			this->m_productName = nullptr;
		}
	}

	const char* NonPerishable::name() const
	{

		return this->m_productName;
	}

	double NonPerishable::cost() const
	{
		//cout << "double NonPerishable::cost() const" << endl;
		double price = this->m_PriceOrigin;
		if (this->m_taxOrnot)
		{
			price = price + price*tax_rate;
			//cout << "price = " << price << endl;
		}
		return price;
	}

	void NonPerishable::message(const char* err_msg)
	{
		this->m_error.message(err_msg);
	}

	bool  NonPerishable::isClear() const
	{
		if (m_error.isClear())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	NonPerishable::NonPerishable(const char type)
	{
		this->m_productType = type;
		this->setEmpty();
	}

	NonPerishable::NonPerishable(const char* sku, const char* name, const char* unit, const int quantityC,
		const bool taxornot, const double price_o, const int quantityN)
	{
		if (sku != nullptr && name != nullptr && unit != nullptr&& quantityC >= 0 && price_o >= 0 && quantityN >= 0) {
			//delete[] this->m_productName;
			this->m_productName = nullptr;    //WHY???!!!
			strcpy(this->m_productSku, sku);
			this->name(name);
			strcpy(this->m_unit, unit);
			this->m_CurrQuantity = quantityC;
			this->m_taxOrnot = taxornot;
			this->m_PriceOrigin = price_o;
			this->m_NeededQuantity = quantityN;
		}
		else 
		{
			*this = NonPerishable();
		}




	}

	NonPerishable::NonPerishable(const NonPerishable& src)
	{
		this->m_productName = nullptr;
		*this = src;
	}

	NonPerishable& NonPerishable::operator= (const NonPerishable& src)
	{
		if (this != &src)
		{
			if (src.m_productName != nullptr) {
				delete[] this->m_productName;
				this->name(src.name());
				this->m_CurrQuantity = src.m_CurrQuantity;
				this->m_error.message(src.m_error.message());
				this->m_NeededQuantity = src.m_NeededQuantity;
				this->m_PriceOrigin = src.m_PriceOrigin;
				strcpy(this->m_productSku, src.m_productSku);
				this->m_productType = src.m_productType;
				strcpy(this->m_unit, src.m_unit);
				this->m_taxOrnot = src.m_taxOrnot;
			}
			else
			{
				this->setEmpty();
			}

		}
		return *this;
	}


	NonPerishable::~NonPerishable()
	{
		delete[] this->m_productName;
		this->m_productName = nullptr;
	}

	std::fstream& NonPerishable::store(std::fstream& file, bool newLine) const
	{
		file << this->m_productType << ",";
		file << this->m_productSku << ",";
		file << this->name() << ",";
		file << this->m_PriceOrigin << ",";
		file << this->m_taxOrnot << ",";
		file << this->quantity() << ",";
		file << this->m_unit << ",";
		file << this->qtyNeeded();

		if (newLine)
		{
			file << '\n';
		}
		return file;
	}

	std::fstream& NonPerishable::load(std::fstream& file)
	{

		string s_sku;
		string s_name;
		bool s_taxOrNot;
		string s_unit;
		double t_price;
		int t_curQ;
		int t_neededQ;

		if (file)
		{
			getline(file, s_sku, ',');
			getline(file, s_name, ',');
			file >> t_price;
			file.ignore();
			file >> s_taxOrNot;
			file.ignore();
			file >> t_curQ;
			file.ignore();
			getline(file, s_unit, ',');
			file >> t_neededQ;
			file.ignore();
			if (file.good())
			{
				//NonPerishable(const char* sku, const char* name, const char* unit, const int quantityC = 0, const bool taxornot = true, const double price_o = 0, const int quantityN = 0, const char* type = "N");

				//*this = NonPerishable(s_sku.c_str(), s_name.c_str(), s_unit.c_str(), t_curQ, s_taxOrNot, t_price, t_neededQ);
				strcpy(this->m_productSku, s_sku.c_str());
				name(s_name.c_str());
				strcpy(this->m_unit, s_unit.c_str());
				this->m_PriceOrigin = t_price;
				this->m_CurrQuantity = t_curQ;
				this->m_NeededQuantity = t_neededQ;
				this->m_taxOrnot = s_taxOrNot;
			}
		}

		return file;
	}

	std::ostream& NonPerishable::write(std::ostream& os, bool linear) const
	{
		if (this->m_error.isClear())
		{
			if (linear)
			{
				os.setf(ios::fixed);
				os.precision(2);
				os.fill(' ');
				os.setf(ios::left);
				os.width(max_sku_length);
				os << this->m_productSku << "|";
				os.width(20);
				os << this->name() << "|";
				os.unsetf(ios::left);
				os.width(7);
				os << this->cost() << "|";
				os.width(4);
				os << this->m_CurrQuantity << "|";
				os.setf(ios::left);
				os.width(10);
				os << this->m_unit << "|";
				os.unsetf(ios::left);
				os.width(4);
				os << this->m_NeededQuantity << "|";
			}
			else
			{
				os.setf(ios::fixed);
				os.precision(2);
				os << "Sku: " << this->m_productSku << std::endl;
				os << "Name: " << this->name() << std::endl;
				os << "Price: " << this->m_PriceOrigin << std::endl;
				if (this->m_taxOrnot)
				{
					os << "Price after tax: " << this->cost() << std::endl;
				}
				else
				{
					os << "Price after tax:" << " N/A" << std::endl;
				}

				os << "Quantity On Hand: " << this->quantity() << " " << this->m_unit << std::endl;
				os << "Quantity Needed: " << this->qtyNeeded();
			}
		}
		else
		{
			os << this->m_error.message();
		}

		return os;
	}
	std::istream& NonPerishable::read(std::istream& is)
	{
		char t_productSku[max_sku_length];
		char t_name[max_name_length]; //why cannot use string and getline(is, s_name)

		char t_unit[max_unit_lenght];
		int t_CurrQuantity;
		int t_NeededQuantity;
		double t_PriceOrigin;
		char t_taxOrnot[1048];
		if (is.fail())
		{
			return is;
		}
		else
		{

			cout << " Sku: ";
			is >> t_productSku;
			if (!is.fail())
			{
				strcpy(this->m_productSku, t_productSku);

			}
			cout << " Name: ";

			is >> t_name;

			if (!is.fail())
			{
				this->name(t_name);
			}

			cout << " Unit: ";
			is >> t_unit;
			if (!is.fail())
			{
				strcpy(this->m_unit, t_unit);
			}


			cout << " Taxed? (y/n): ";
			is >> t_taxOrnot;
			if (!is.fail())
			{
				if ((strcmp(t_taxOrnot, "y") == 0 || strcmp(t_taxOrnot, "Y") == 0) && strlen(t_taxOrnot) == 1)
				{
					this->m_taxOrnot = true;
				}
				else if ((strcmp(t_taxOrnot, "N") == 0 || strcmp(t_taxOrnot, "n") == 0) && strlen(t_taxOrnot) == 1)
				{
					this->m_taxOrnot = false;
				}
				else
				{
					this->m_error.message("Only (Y)es or (N)o are acceptable");
					is.setstate(std::ios::failbit);
				}
			}

			if (!is.fail())
			{
				cout << " Price: ";
				is >> t_PriceOrigin;
				if (!is.fail()) {
					this->m_PriceOrigin = t_PriceOrigin;
				}
				else
				{
					this->m_error.message("Invalid Price Entry");
				}
			}

			if (!is.fail())
			{
				cout << "Quantity On hand: ";
				is >> t_CurrQuantity;

				if (!is.fail())
				{
					this->m_CurrQuantity = t_CurrQuantity;
				}
				else
				{
					this->m_error.message("Invalid Quantity Entry");

				}
			}

			if (!is.fail())
			{
				cout << "Quantity Needed: ";
				is >> t_NeededQuantity;
				if (!is.fail())
				{
					this->m_NeededQuantity = t_NeededQuantity;
				}
				else
				{
					this->message("Invalid Quantity Needed Entry");
				}
			}
			if (!is.fail())
			{
				this->m_error.clear();
			}
			return is;
		}
	}

	bool NonPerishable::operator==(const char* sku) const
	{
		bool valid;
		if (strcmp(this->m_productSku, sku) == 0)
		{
			valid = true;
		}
		else
		{
			valid = false;
		}
		return valid;
	}

	double NonPerishable::total_cost() const
	{
		double total_Price;
		if (this->m_taxOrnot)
		{
			total_Price = this->m_PriceOrigin* this->m_CurrQuantity * (1 + tax_rate);
		}
		else
		{
			total_Price = this->m_PriceOrigin* this->m_CurrQuantity;
		}
		return total_Price;
	}

	void NonPerishable::quantity(int quantity)
	{
		this->m_CurrQuantity = quantity;
	}

	bool NonPerishable::isEmpty() const
	{
		bool valid;
		if (this->m_productName == nullptr)
		{
			valid = true;
		}
		else
		{
			valid = false;
		}
		return valid;
	}

	int NonPerishable::qtyNeeded() const
	{
		return this->m_NeededQuantity;
	}

	int NonPerishable::quantity() const
	{
		return this->m_CurrQuantity;
	}

	bool NonPerishable::operator>(const char* sku) const
	{
		bool valid;
		if (strcmp(sku, this->m_productSku) > 0)
		{
			valid = true;
		}
		else
		{
			valid = false;
		}
		return valid;
	}

	int NonPerishable::operator+=(int quantity)
	{
		if (quantity > 0)
		{
			this->m_CurrQuantity = this->m_CurrQuantity + quantity;
		}
		return m_CurrQuantity;
	}

	bool NonPerishable::operator>(const Product& src) const
	{
		bool valid;
		if (strcmp(this->m_productName, src.name()) > 0)
		{
			valid = true;
		}
		else
		{
			valid = false;
		}
		return valid;
	}
	std::ostream& operator<<(std::ostream& os, const Product& src)
	{
		src.write(os, true);
		return os;
	}

	std::istream& operator>>(std::istream& is, Product& src)
	{
		src.read(is);
		return is;
	}

	double operator+=(double& extra_cost, const Product& src)
	{
		extra_cost = extra_cost + src.total_cost();
		return extra_cost;
	}

	Product* CreateProduct()
	{
		Product* aProduct = nullptr;
		aProduct = new NonPerishable;
		return aProduct;
	}




}




