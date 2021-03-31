#include "stdafx.h"
#include "SpriteSheetAnimation.h"

#include "JsonManager.h"

#include "SpriteWrapper.h"

#include <tga2d/texture/texture_manager.h>

SpriteSheetAnimation::SpriteSheetAnimation(const JsonManager* aJsonManager, const std::string& anAnimationPath)
{
	Load(aJsonManager, anAnimationPath);
}

SpriteSheetAnimation::SpriteSheetAnimation(const JsonManager* aJsonManager, const char* anAnimationPath)
	: SpriteSheetAnimation(aJsonManager, std::string(anAnimationPath))
{}

void SpriteSheetAnimation::Update(float aDeltaTime)
{
	if (!InState())
	{
		return;
	}

	myTime += aDeltaTime;

	if (IsLooping())
	{
		const float duration = GetDuration();
		if (myTime >= duration)
		{
			myTime = std::fmodf(myTime, duration);
		}
	}
}

void SpriteSheetAnimation::ApplyToSprite(const std::shared_ptr<SpriteWrapper>& aSprite)
{
	if (!InState())
	{
		return;
	}

	const auto& state = GetCurrentState();
	const int frameIndex = min(static_cast<int>(std::floorf(myTime / state.myInvFps)), static_cast<int>(state.myFrames.size() - 1));

	const auto& frame = state.myFrames[frameIndex];

	if (aSprite->GetTexture() != state.myTexture)
	{
		aSprite->SetTexture(state.myTexture);
	}
	aSprite->SetTextureRect({ frame.myX, frame.myY, frame.myX + frame.myWidth, frame.myY + frame.myHeight });

	VECTOR2F imageSize;
	imageSize = state.myTexture->myImageSize;

	aSprite->SetSize({ imageSize.myX * frame.myWidth, imageSize.myY * frame.myHeight });
}

void SpriteSheetAnimation::SetState(const std::string& aState)
{
	assert(myStates.count(aState) > 0);

	myActiveState = aState;
	myTime = 0.0f;
}

const std::string& SpriteSheetAnimation::GetState() const
{
	return myActiveState;
}

float SpriteSheetAnimation::GetDuration() const
{
	const auto& state = GetCurrentState();
	return static_cast<float>(state.myFrames.size()) * state.myInvFps;
}

bool SpriteSheetAnimation::InState() const
{
	return !myActiveState.empty();
}

const SpriteSheetAnimation::AnimationState& SpriteSheetAnimation::GetCurrentState() const
{
	assert(!myActiveState.empty());

	return myStates.at(myActiveState);
}

void SpriteSheetAnimation::Load(const JsonManager* aJsonManager, const std::string& anAnimationPath)
{
	const JsonData& animationData = aJsonManager->GetData(anAnimationPath);

	Tga2D::CTexture* defaultTexture{};

	if (animationData.contains("defaultTexture"))
	{
		defaultTexture = TryLoadTexture(animationData["defaultTexture"]);
	}

	assert(animationData.contains("states") && "animation does not contain states!");

	const auto& states = animationData["states"];

	myStates.reserve(states.size());

	for (const auto& [stateName, stateData] : states.items())
	{
		SpriteSheetAnimation::AnimationState newState{};

		const int fps = stateData.value("fps", 0);
		const std::string texture = stateData.value("texture", "");

		assert(fps > 0 && "invalid or no fps found in animation state!");

		newState.myInvFps = 1.0f / static_cast<float>(fps);
		if (!texture.empty())
		{
			newState.myTexture = TryLoadTexture(texture);
		}
		else
		{
			assert(defaultTexture != nullptr && "state with no texture found and no default set!");
			newState.myTexture = defaultTexture;
		}

		const std::string algorithm = stateData.value("algorithm", "manual");

		if (algorithm == "manual")
		{
			LoadManualFrames(stateData, newState);
		}
		else if (algorithm == "seqrow")
		{
			LoadSeqRowFrames(stateData, newState);
		}
		else
		{
			assert(false && "Invalid algorithm in animation file!");
		}

		myStates.insert({ stateName, newState });
	}
}

void SpriteSheetAnimation::LoadManualFrames(const JsonData& someState, AnimationState& aResultState)
{
	assert(someState.contains("frames") && "no frames in state!");

	const auto& frames = someState["frames"];
	assert(frames.is_array() && "frames not array!");

	aResultState.myFrames.reserve(frames.size());

	for (const auto& frameData : frames)
	{
		const int x = frameData.value("x", -1);
		const int y = frameData.value("y", -1);
		const int w = frameData.value("width", -1);
		const int h = frameData.value("height", -1);

		assert(x >= 0 && y >= 0 && w > 0 && h > 0 && "invalid frame!");

		VECTOR2F imageSize;
		imageSize = aResultState.myTexture->myImageSize;

		AnimationFrame newFrame{};
		newFrame.myX = x / imageSize.myX;
		newFrame.myY = y / imageSize.myY;
		newFrame.myWidth = w / imageSize.myX;
		newFrame.myHeight = h / imageSize.myY;

		aResultState.myFrames.push_back(newFrame);
	}
}

void SpriteSheetAnimation::LoadSeqRowFrames(const JsonData& someState, AnimationState& aResultState)
{
	VECTOR2F textureSize;
	textureSize = aResultState.myTexture->myImageSize;

	const int framePixelWidth = someState["frameWidth"];
	const int framePixelHeight = someState["frameHeight"];

	const int startRow = someState["start"]["row"];
	const int startColumn = someState["start"]["column"];

	const int frameCount = someState["count"];

	// ----

	const int framesPerRow = static_cast<int>(std::floorf(textureSize.x / framePixelWidth));

	const float frameWidth = framePixelWidth / textureSize.x;
	const float frameHeight = framePixelHeight / textureSize.y;

	const int startIndex = startColumn + startRow * framesPerRow;
	for (int i = startIndex; i < startIndex + frameCount; ++i)
	{
		const int row = i / framesPerRow;
		const int column = i % framesPerRow;

		const float startU = column * frameWidth;
		const float startV = row * frameHeight;

		AnimationFrame frame{};
		frame.myX = startU;
		frame.myY = startV;
		frame.myWidth = frameWidth;
		frame.myHeight = frameHeight;

		aResultState.myFrames.push_back(frame);
	}
}

Tga2D::CTexture* SpriteSheetAnimation::TryLoadTexture(const std::string& aPath) const
{
	if (aPath.empty())
	{
		ERROR_PRINT("Trying to load empty texture!");

		return nullptr;
	}

	return Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture(aPath.c_str());
}
