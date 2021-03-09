#pragma once

#include <cassert>
#include <unordered_map>

template <typename BehaviourKey, typename BehaviourBase, typename TypeKey, typename TypeData, typename ... ConstructParams>
class BehaviourFactoryBase
{
public:

	using BehaviourConstructor = std::function<std::shared_ptr<BehaviourBase>(ConstructParams...)>;

	BehaviourFactoryBase() = default;
	virtual ~BehaviourFactoryBase() = 0 {};

	void RegisterBehaviour(const BehaviourKey& aKey, const BehaviourConstructor& aConstructor)
	{
		myBehaviourConstructors.insert({ aKey, aConstructor });
	}

	void RegisterType(const TypeKey& aKey, const BehaviourKey& aUsedBehaviourKey, const TypeData& someTypeData)
	{
		myTypes.insert({ aKey, TypeInformation{ aUsedBehaviourKey, someTypeData } });
	}

	template <typename Behaviour>
	static std::shared_ptr<BehaviourBase> ConstructBehaviour(ConstructParams ... someArgs)
	{
		return std::make_shared<Behaviour>(someArgs...);
	}

protected:

	struct TypeInformation
	{
		BehaviourKey myUsedBehaviourKey;
		TypeData myTypeData;
	};

	virtual std::shared_ptr<BehaviourBase> ConstructType(std::shared_ptr<BehaviourBase> aBehaviour, const TypeData& someTypeData) const = 0;

	virtual std::shared_ptr<BehaviourBase> CreateType(const TypeKey& aKey, ConstructParams ... someArgs) const
	{
		assert(myTypes.count(aKey) > 0 && "Trying to create non-registered type!");

		const TypeInformation& typeInformation = myTypes.at(aKey);

		return ConstructType(CreateBehaviour(typeInformation.myUsedBehaviourKey, someArgs...), typeInformation.myTypeData);
	}

	virtual std::shared_ptr<BehaviourBase> CreateBehaviour(const BehaviourKey& aKey, ConstructParams ... someArgs) const
	{
		assert(myBehaviourConstructors.count(aKey) > 0 && "Trying to create non-registered behaviour!");

		std::shared_ptr<BehaviourBase> behaviour = myBehaviourConstructors.at(aKey)(someArgs...);

		return behaviour;
	}

protected:

	std::unordered_map<BehaviourKey, BehaviourConstructor> myBehaviourConstructors;
	std::unordered_map<TypeKey, TypeInformation> myTypes;

};
