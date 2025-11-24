#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"
# include <cstdlib>
# include <iomanip>
# include <iostream>
# include <string>

class PhoneBook
{
  private:
	Contact _contacts[8];
	int _totalContact;
	int _indexContact;

  public:
	PhoneBook(void);
	~PhoneBook(void);
	void addContact(const Contact &newContact);
	void displayContacts() const;
	void displayContact(int index) const;
	int getCount() const;
};

#endif