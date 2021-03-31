#pragma once

#include "JsonData.h"

#include <unordered_map>
#include <vector>

namespace Tga2D
{
	class CTexture;
}

class JsonManager;
class SpriteWrapper;

class SpriteSheetAnimation
{
public:

	SpriteSheetAnimation(const JsonManager* aJsonManager, const std::string& anAnimationPath);
	SpriteSheetAnimation(const JsonManager* aJsonManager, const char* anAnimationPath);

	void Update(float aDeltaTime);

	void ApplyToSprite(const std::shared_ptr<SpriteWrapper>& aSprite);

	void SetState(const std::string& aState);
	const std::string& GetState() const;

	float GetDuration() const;

	bool InState() const;

	inline void SetIsLooping(bool anIsLooping) { myIsLooping = anIsLooping; }
	inline bool IsLooping() const { return myIsLooping; }

private:

	struct AnimationFrame
	{
		float myX;
		float myY;
		float myWidth;
		float myHeight;
	};

	struct AnimationState
	{
		float myInvFps{};

		Tga2D::CTexture* myTexture{};
		std::vector<AnimationFrame> myFrames;
	};

	const AnimationState& GetCurrentState() const;

	void Load(const JsonManager* aJsonManager, const std::string& anAnimationPath);

	void LoadManualFrames(const JsonData& someState, AnimationState& aResultState);
	void LoadSeqRowFrames(const JsonData& someState, AnimationState& aResultState);

	Tga2D::CTexture* TryLoadTexture(const std::string& aPath) const;

private:

	float myTime{};
	bool myIsLooping{};

	std::string myActiveState;
	std::unordered_map<std::string, AnimationState> myStates;

};
