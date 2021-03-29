#include "stdafx.h"
#include "Contact.h"

Contact::Contact() = default;

void Contact::Set(const ContactKey& aContactKey)
{
	myContactKey = aContactKey;
}

void Contact::Reset()
{
	myContactKey.reset();
}

const std::optional<ContactKey>& Contact::GetContactKey() const
{
	return myContactKey;
}
