#pragma once

#include "ContactKey.h"

#include <optional>

class Contact
{
public:

	Contact();

	void Set(const ContactKey& aContactKey);
	void Reset();

	const std::optional<ContactKey>& GetContactKey() const;

private:

	std::optional<ContactKey> myContactKey;

};