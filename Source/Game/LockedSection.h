#pragma once

#include <cassert>

class LockedSection
{
public:

	inline void Lock()
	{
		assert(!myIsLocked);

		myIsLocked = true;
	}

	inline void Unlock()
	{
		assert(myIsLocked);

		myIsLocked = false;
	}

	inline bool IsLocked() const { return myIsLocked; }

private:

	bool myIsLocked{};

};
