#include "stdafx.h"
#include "ContactManager.h"

#include "Contact.h"
#include "Collider.h"
#include "CollisionInfo.h"
#include "CollisionListener.h"

ContactManager::ContactManager()
{
	for (std::size_t i = 0; i < ContactManager::ourInitialFreeContactsSize; ++i)
	{
		myFreeContacts.push(std::make_shared<Contact>());
	}
}

void ContactManager::AddContact(const ContactKey& aContactKey)
{
	std::shared_ptr<Contact> contact = GetFreeContact();
	contact->Set(aContactKey);

	myContacts.insert({ aContactKey, contact });

	aContactKey.myColliderA->AddContact(aContactKey);
	aContactKey.myColliderB->AddContact(aContactKey);
}

bool ContactManager::HasContact(const ContactKey& aContactKey) const
{
	return myContacts.find(aContactKey) != myContacts.end();
}

void ContactManager::RemoveContact(const ContactKey& aContactKey)
{
	aContactKey.myColliderA->RemoveContact(aContactKey);
	aContactKey.myColliderB->RemoveContact(aContactKey);

	std::shared_ptr<Contact> toRemove = myContacts.at(aContactKey);
	myContacts.erase(aContactKey);

	FreeContact(toRemove);
}

void ContactManager::DestroyContacts(Collider* aCollider)
{
	const std::vector<ContactKey> contacts = aCollider->myContacts;
	for (const ContactKey& aContact : contacts)
	{
		RemoveContact(aContact);
	}
}

void ContactManager::SendOnEnter(const Collider* aColliderA, const Collider* aColliderB)
{
	CollisionListener* listenerA = aColliderA->GetCollisionListener();
	CollisionListener* listenerB = aColliderB->GetCollisionListener();

	const CollisionInfo infoA{ aColliderB };
	const CollisionInfo infoB{ aColliderA };

	if (listenerA != nullptr) listenerA->OnEnter(infoA);
	if (listenerB != nullptr) listenerB->OnEnter(infoB);
}

void ContactManager::SendOnStay(const Collider* aColliderA, const Collider* aColliderB)
{
	CollisionListener* listenerA = aColliderA->GetCollisionListener();
	CollisionListener* listenerB = aColliderB->GetCollisionListener();

	const CollisionInfo infoA{ aColliderB };
	const CollisionInfo infoB{ aColliderA };

	if (listenerA != nullptr) listenerA->OnStay(infoA);
	if (listenerB != nullptr) listenerB->OnStay(infoB);
}

void ContactManager::SendOnExit(const Collider* aColliderA, const Collider* aColliderB)
{
	CollisionListener* listenerA = aColliderA->GetCollisionListener();
	CollisionListener* listenerB = aColliderB->GetCollisionListener();

	const CollisionInfo infoA{ aColliderB };
	const CollisionInfo infoB{ aColliderA };

	if (listenerA != nullptr) listenerA->OnExit(infoA);
	if (listenerB != nullptr) listenerB->OnExit(infoB);
}

std::shared_ptr<Contact> ContactManager::GetFreeContact()
{
	std::shared_ptr<Contact> freeContact = myFreeContacts.front();
	myFreeContacts.pop();

	return freeContact;
}

void ContactManager::FreeContact(std::shared_ptr<Contact> aContact)
{
	aContact->Reset();
	myFreeContacts.push(aContact);
}
