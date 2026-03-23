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
};


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