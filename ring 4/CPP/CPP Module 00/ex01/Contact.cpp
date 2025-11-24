#include "Contact.hpp"

Contact::Contact(void)
{
}

Contact::~Contact(void)
{
}

static void	enter_contact(std::string &answer, std::string type)
{
	while (answer.empty())
	{
		std::cout << "Enter " << type << " :";
		std::getline(std::cin, answer);
		if (std::cin.eof())
			exit(0);
		if (answer.empty())
			std::cout << "Field cannot be empty!" << std::endl;
	}
	return ;
}

void Contact::setContact(void)
{
	enter_contact(_firstName, "First Name");
	enter_contact(_lastName, "Last Name");
	enter_contact(_nickname, "Nickname");
	enter_contact(_phoneNumber, "Phone Number");
	enter_contact(_darkestSecret, "Darkest Secret");
}

std::string Contact::getFirstName() const
{
	return (this->_firstName);
}

std::string Contact::getLastName() const
{
	return (this->_lastName);
}

std::string Contact::getNickname() const
{
	return (this->_nickname);
}

std::string Contact::getPhoneNumber() const
{
	return (this->_phoneNumber);
}

std::string Contact::getDarkestSecret() const
{
	return (this->_darkestSecret);
}
