#pragma once

#include "ContactKey.h"

#include <queue>
#include <map>

class Contact;
class Collider;

class ContactManager
{
public:

	ContactManager();

	// void AddContact(Collider* aColliderA, Collider* aColliderB);
	void AddContact(const ContactKey& aContactKey);
	bool HasContact(const ContactKey& aContactKey) const;
	void RemoveContact(const ContactKey& aContactKey);
	
	void DestroyContacts(Collider* aCollider);

	static void SendOnEnter(const Collider* aColliderA, const Collider* aColliderB);
	static void SendOnStay(const Collider* aColliderA, const Collider* aColliderB);
	static void SendOnExit(const Collider* aColliderA, const Collider* aColliderB);

private:

	std::shared_ptr<Contact> GetFreeContact();
	void FreeContact(std::shared_ptr<Contact> aContact);

private:

	static constexpr std::size_t ourInitialFreeContactsSize = 256;

	std::map<ContactKey, std::shared_ptr<Contact>> myContacts;
	std::queue<std::shared_ptr<Contact>> myFreeContacts;

};
