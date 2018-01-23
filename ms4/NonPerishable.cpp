#define _CRT_SECURE_NO_WARNINGS
#include <string>
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

	NonPerishable::NonPerishable(const char* type)
	{
		strcpy(this->m_productType, type);
		this->setEmpty();
	}

	NonPerishable::NonPerishable(const char* sku, const char* name, const char* unit, const int quantityC,
		const bool taxornot, const double price_o, const int quantityN, const char* type)
	{
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
				strcpy(this->m_productType, src.m_productType);
				strcpy(this->m_unit, src.m_unit);
				this->m_taxOrnot = src.m_taxOrnot;
			}
			else
			{
				this->m_productType[0] = '\0';
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
		file << this->m_unit << ",";
		file << this->m_taxOrnot << ",";
		file << this->m_PriceOrigin << ",";
		file << this->m_CurrQuantity << ",";
		file << this->m_NeededQuantity;
		if (newLine)
		{
			file << '\n';
		}
		return file;
	}

	std::fstream& NonPerishable::load(std::fstream& file)
	{
		string s_type;
		string s_sku;
		string s_name;
		string s_taxOrNot;


		if (file)
		{
			getline(file, s_type, ',');
			getline(file, s_sku, ',');
			getline(file, s_name, ',');
			file >> this->m_unit;
			file.ignore();
			getline(file, s_taxOrNot, ',');
			file >> this->m_PriceOrigin;
			file.ignore();
			file >> this->m_CurrQuantity;
			file.ignore();
			file >> this->m_NeededQuantity;
			file.ignore();
			if (file.good())
			{
				char t_type[1];
				char t_sku[max_sku_length];
				char* t_name;
				char t_taxOrNot[1];
				strcpy(t_type, s_type.c_str());
				strcpy(t_sku, s_sku.c_str());
				t_name = new char[s_name.length() + 1];
				strcpy(t_name, s_name.c_str());
				strcpy(t_taxOrNot, s_taxOrNot.c_str());

				strcpy(this->m_productType, t_type);
				strcpy(this->m_productSku, t_sku);
				this->name(t_name);
				if (strcmp(t_taxOrNot, "y")==0 || strcmp(t_taxOrNot, "Y")==0)
				{
					this->m_taxOrnot = true;
				}
				else
				{
					this->m_taxOrnot = false;
				}
				delete[] t_name;
			}
		}

		return file;
	}

	std::ostream& NonPerishable::write(std::ostream& os, bool linear) const
	{
		if (linear)
		{
			os.width(max_sku_length);
			os << "sku - " << this->m_productSku << "|";
			os.width(20);
			os << "name - " << this->name() << "|";
			os.width(7);
			os << "cost - " << this->cost() << "|";
			os.width(4);
			os << "quantity - " << this->m_CurrQuantity << "|";
			os.width(10);
			os << "unit - " << this->m_unit << "|";
			os.width(4);
			os << "quantity needed - " << this->m_NeededQuantity << "|";
		}
		else
		{
			os << "Sku: " << this->m_productSku << std::endl;
			os << "Name: " << this->name() << std::endl;
			os << "Price:" << std::endl;
			if (this->m_taxOrnot)
			{
				os << "Price after tax: " << this->cost() << std::endl;
			}
			else
			{
				os << "N/A" << std::endl;
			}

			os << "Quantity On Hand: " << this->m_CurrQuantity << std::endl;
			os << "Quantity Needed: " << this->m_NeededQuantity << std::endl;
		}
		return os;
	}
	std::istream& NonPerishable::read(std::istream& is)
	{
		char t_productSku[max_sku_length];
		string s_name;
		char* t_productName;
		char t_unit[max_unit_lenght];
		int t_CurrQuantity;
		int t_NeededQuantity;
		double t_PriceOrigin;
		char t_taxOrnot[1];
		if (is.fail())
		{
			return is;
		}
		else
		{
			this->m_error.isClear();
			cout << "Sku: " << endl;
			is >> t_productSku;
			if (!is.fail())
			{
				strcpy(this->m_productSku, t_productSku);

			}
			cout << "Name: " << endl;
			if (getline(is, s_name))
			{
				t_productName = new char[s_name.length() + 1];
				strcpy(t_productName, s_name.c_str());
			}
			if (!is.fail())
			{
				strcpy(this->m_productName, t_productName);
			}

			cout << "Unit: " << endl;
			is >> t_unit;
			if (!is.fail())
			{
				strcpy(this->m_unit, t_unit);
			}

			if (this->m_error.isClear())
			{
				cout << "Taxed(y/n): " << endl;
				is >> t_taxOrnot;
				if (!is.fail())
				{
					if (strcmp(t_taxOrnot, "y") == 0 || strcmp(t_taxOrnot, "Y") == 0)
					{
						this->m_taxOrnot = true;
					}
					else if (strcmp(t_taxOrnot, "N") == 0 || strcmp(t_taxOrnot, "n")==0)
					{
						this->m_taxOrnot = false;
					}
					else
					{
						this->message("Only (Y)es or (N)o are acceptable");
						is.setstate(std::ios::failbit);
					}
				}
			}
			if (!is.fail())
			{
				cout << "Price: " << endl;
				is >> t_PriceOrigin;
				this->m_PriceOrigin = t_PriceOrigin;
			}
			else
			{
				this->message("Invalid Price Entry");
				is.setstate(std::ios::failbit);
			}

			if (!is.fail())
			{
				cout << "Quantity on hand: " << endl;
				is >> t_CurrQuantity;
				if (!is.fail())
				{
					this->m_CurrQuantity = t_CurrQuantity;
				}
			}
			else
			{
				this->message("Invalid Quantity Entry");
				is.setstate(std::ios::failbit);
			}

			if (!is.fail())
			{
				cout << "Quantity Needed";
				is >> t_NeededQuantity;
				this->m_NeededQuantity = t_CurrQuantity;
			}
			else
			{
				this->message("Invalid Quantity Needed Entry");
			}
		}
		return is;
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
		src.write(os, false);
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




