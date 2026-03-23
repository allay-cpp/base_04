#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <new>

class Address
{
private:
	std::string city;
	std::string street;
	int house;
	int flat;

public:
	Address(std::string setCity, std::string setStreet, int setHouse, int setFlat) : city{ setCity }, street{ setStreet }, house{ setHouse }, flat{ setFlat }
	{}

	~Address()
	{}

	std::string get_output_address()
	{
		return 	this->city + ", " + this->street + ", " + std::to_string(this->house) + ", " + std::to_string(this->flat);
	}

	char symbol_city()
	{
		return this->getCity()[0];
	}

private:
	void setAddress(std::string newCity, std::string newStreet, int newHouse, int newFlat)
	{
		this->city = newCity;
		this->street = newStreet;
		this->house = newHouse;
		this->flat = newFlat;
	}
	std::string getCity()
	{
		return this->city;
	}
	std::string getStreet()
	{
		return this->street;
	}
	int getHouse()
	{
		return this->house;
	}
	int getFlat()
	{
		return this->flat;
	}
};

void sort(Address* addresses, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (addresses[j].symbol_city() > addresses[j + 1].symbol_city())
			{
				Address temp_address = addresses[j];
				addresses[j] = addresses[j + 1];
				addresses[j + 1] = temp_address;
			}
		}
	}
}

int main(int argc, char** argv)
{
	std::ifstream fin("in.txt");
	std::string s;
	if (fin.is_open())
	{
		fin >> s;
		int n = std::stoi(s);

		std::string city;
		std::string street;
		int house;
		int flat;

		void* memory = operator new[](n * sizeof(Address));
		Address* addresses = static_cast<Address*>(memory);

		for (int i = 0; i < n; i++)
		{
			fin >> city;
			fin >> street;
			fin >> s;
			house = std::stoi(s);
			fin >> s;
			flat = std::stoi(s);
			new(addresses + i) Address(city, street, house, flat);
		}
		fin.close();

		sort(addresses, n);

		for (int i = 0; i < n; i++)
		{
			std::cout << addresses[i].get_output_address() << std::endl;
		}

		std::ofstream fin("out.txt");
		fin << n << '\n';
		for (int i = 0; i < n; i++)
		{
			fin << addresses[i].get_output_address() << std::endl;
		}
		fin.close();

		for (int i = 0; i < n; i++)
		{
			addresses[i].~Address();
		}
		operator delete[](memory);
	}

	return 0;
}