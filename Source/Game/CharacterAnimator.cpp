#include "stdafx.h"
#include "CharacterAnimator.h"

#include "SpriteSheetAnimation.h"

#include "Scene.h"
#include "GlobalServiceProvider.h"

#include "MathHelper.h"
#include "SpriteWrapper.h"

CharacterAnimator::CharacterAnimator(Scene* aScene, const std::string& anAnimationPath) :
	myScene(aScene)
{
	myAnimator = std::make_unique<SpriteSheetAnimation>(myScene->GetGlobalServiceProvider()->GetJsonManager(), anAnimationPath);
	myAnimator->SetIsLooping(true);

	SetState(State::Idle);
}

void CharacterAnimator::Update(float aDeltaTime)
{
	myAnimator->Update(aDeltaTime * myAnimationSpeed);
}

void CharacterAnimator::ApplyToSprite(const std::shared_ptr<SpriteWrapper>& aSprite)
{
	myAnimator->ApplyToSprite(aSprite);
	aSprite->SetSize({ aSprite->GetSize().x * myDirection, aSprite->GetSize().y });
}

void CharacterAnimator::SetAnimationSpeed(float aSpeed)
{
	myAnimationSpeed = aSpeed;
}

float CharacterAnimator::GetAnimationSpeed() const
{
	return myAnimationSpeed;
}

void CharacterAnimator::SetDirection(float aDirection)
{
	assert(aDirection != 0.0f);

	myDirection = static_cast<float>(MathHelper::Signum(aDirection));
}

float CharacterAnimator::GetDirection() const
{
	return myDirection;
}

void CharacterAnimator::SetState(State aState)
{
	if ((myState != State::Jump && myState == aState) || myState == State::Death)
	{
		return;
	}

	myState = aState;

	myAnimator->SetState(GetAnimationStateName(aState));
}

bool CharacterAnimator::HasEnded() const
{
	return myAnimator->HasEnded();
}

std::string CharacterAnimator::GetAnimationStateName(State aState) const
{
	switch (aState)
	{
	default:
	case State::Idle:
		myAnimator->SetIsLooping(true);
		return "idle";

	case State::Run:
		myAnimator->SetIsLooping(true);
		return "running";

	case State::Attack:
		return "attack";

	case State::Jump:
		myAnimator->SetIsLooping(false);
		return "jump";

	case State::Boost:
		return "boost";

	case State::Death:
		myAnimator->SetIsLooping(false);
		return "death";
	}
}
