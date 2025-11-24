#include "Contact.hpp"
#include "PhoneBook.hpp"

static void	handleAdd(PhoneBook &phoneBook)
{
	Contact newContact;
	
	newContact.setContact();
	phoneBook.addContact(newContact);
}

static void	handleSearch(const PhoneBook &phoneBook)
{
	int	index;
	
	phoneBook.displayContacts();
	if (phoneBook.getCount() == 0)
		return;
	std::cout << "Enter an index: ";
	std::cin >> index;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Invalid input!" << std::endl;
		return;
	}
	std::cin.ignore();
	if (index >= 0 && index < phoneBook.getCount())
		phoneBook.displayContact(index);
	else
		std::cout << "Invalid index!" << std::endl;
}

int	main(void)
{
	PhoneBook	phoneBook;
	std::string	command;
	
	while (true)
	{
		std::cout << "Enter a command: ";
		std::getline(std::cin, command);
		if (std::cin.eof())
		{
			std::cout << std::endl;
			break;
		}
		if (command == "ADD")
			handleAdd(phoneBook);
		else if (command == "SEARCH")
			handleSearch(phoneBook);
		else if (command == "EXIT")
			break;
	}
	return (0);
}