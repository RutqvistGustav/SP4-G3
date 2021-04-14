#pragma once

#include <memory>
#include <string>

class SpriteSheetAnimation;
class SpriteWrapper;
class Scene;

class CharacterAnimator
{
public:

	enum class State
	{
		None,

		Idle,
		Walk,
		Run,
		Fall,
		Jump,
		Attack,
		Death,
		Boost
	};

	CharacterAnimator(Scene* aScene, const std::string& anAnimationPath);

	void Update(float aDeltaTime);
	void ApplyToSprite(const std::shared_ptr<SpriteWrapper>& aSprite);

	void SetAnimationSpeed(float aSpeed);
	float GetAnimationSpeed() const;

	void SetDirection(float aDirection);
	float GetDirection() const;

	void SetState(State aState);
	inline State GetState() const { return myState; }
	void DisableStateSwitch();
	void EnableStateSwitch();

	bool HasEnded() const;

private:

	std::string GetAnimationStateName(State aState) const;

private:

	State myState{ State::None };
	float myAnimationSpeed{ 1.0f };

	float myDirection{ 1.0f };

	bool myCanSwitchState = true;

	std::unique_ptr<SpriteSheetAnimation> myAnimator;

	Scene* myScene;

};
