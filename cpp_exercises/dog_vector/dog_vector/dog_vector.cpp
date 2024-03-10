#include<iostream>
#include<string>
#include<vector>

class Dog
{
public:
	Dog(std::string n, std::string s) : name(n), sound{ s } {}
	std::string speak(void) { return sound; }
	std::string get_name(void) { return name; }
private:
	std::string name, sound;
};

std::vector<Dog*> dogs;

int main(void)
{
	Dog pluto("Pluto", "bow-wow"), rolf("Rolf", "wuff"), fido("Fido", "wan");
	dogs.push_back(&pluto); dogs.push_back(&rolf); dogs.push_back(&fido);

	for (std::vector<Dog*>::iterator it=dogs.begin(); it != dogs.end(); it++)
	{
		std::cout << (*it)->get_name() << " says " << (*it)->speak() << std::endl; //at performs range check
	}
	std::cout << std::endl;
	for (auto it = dogs.begin(); it != dogs.end(); it++) //easier
	{
		std::cout << (*it)->get_name() << " says " << (*it)->speak() << std::endl; //at performs range check
	}
	std::cout << std::endl;
	for (auto dog_ptr : dogs) //very easy, C++ 11 loop
	{
		std::cout << dog_ptr->get_name() << " says " << dog_ptr->speak() << std::endl; //at performs range check
	}

	dogs.erase(dogs.begin() + 1); //erase Rolf
	dogs.erase(dogs.begin(), dogs.end()); //erase all dogs

	return 0;
}