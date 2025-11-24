#include "PhoneBook.hpp"

PhoneBook::PhoneBook(void) : _totalContact(0), _indexContact(0)
{
}

PhoneBook::~PhoneBook(void)
{
}

void PhoneBook::addContact(const Contact &newContact)
{
	_contacts[_indexContact] = newContact;
	_indexContact = (_indexContact + 1) % 8;
	if (_totalContact < 8)
		_totalContact++;
}

void	print(std::string str)
{
	if (str.size() > 10)
	{
		for (int i = 0; i < 9; i++)
			std::cout << str[i];
		std::cout << '.';
	}
	else
		std::cout << std::setfill(' ') << std::setw(10) << str;
}

void PhoneBook::displayContacts() const
{
	if (_totalContact == 0)
	{
		std::cout << "PhoneBook is empty!" << std::endl;
		return ;
	}
	std::cout << std::setw(10) << "index" << '|';
	std::cout << std::setw(10) << "first name" << '|';
	std::cout << std::setw(10) << "last name" << '|';
	std::cout << std::setw(10) << "nick name" << std::endl;
	for (int i = 0; i < _totalContact; i++)
	{
		std::cout << std::setw(10) << i << '|';
		print(_contacts[i].getFirstName());
		std::cout << '|';
		print(_contacts[i].getLastName());
		std::cout << '|';
		print(_contacts[i].getNickname());
		std::cout << std::endl;
	}
}

void PhoneBook::displayContact(int i) const
{
	std::cout << "First Name: " << _contacts[i].getFirstName() << std::endl;
	std::cout << "Last Name: " << _contacts[i].getLastName() << std::endl;
	std::cout << "Nick Name: " << _contacts[i].getNickname() << std::endl;
	std::cout << "Phone Number: " << _contacts[i].getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << _contacts[i].getDarkestSecret() << std::endl;
}

int PhoneBook::getCount() const
{
	return (_totalContact);
}