#include "stdafx.h"
#include "CutscenePlayer.h"

#include "Metrics.h"

#include "RenderCommand.h"
#include "RenderQueue.h"

#include "SpriteWrapper.h"

#include <tga2d/sprite/sprite.h>
#include <tga2d/sprite/textured_quad.h>
#include <tga2d/videoplayer/video.h>

CutscenePlayer::CutscenePlayer() = default;
CutscenePlayer::~CutscenePlayer() = default;

bool CutscenePlayer::Init(const std::string & aVideoPath)
{
	myVideo = std::make_unique<Tga2D::CVideo>();

	// TODO: Should sound be played from video or played separately?
	bool success = myVideo->Init(aVideoPath.c_str(), true);

	if (!success)
	{
		ERROR_PRINT("%s", "Could not init CutscenePlayer");

		return false;
	}

	const Tga2D::STextureRext* uvRect = myVideo->GetSprite()->GetTextureRect();

	myFrameSprite = std::make_shared<SpriteWrapper>();
	myFrameSprite->SetTextureRect({ uvRect->myStartX, uvRect->myStartY, uvRect->myEndX, uvRect->myEndY });
	myFrameSprite->SetTexture(myVideo->GetTexture());

	myFrameSprite->SetPosition(Metrics::GetReferenceSize() * 0.5f);

	// TODO: NOTE: If video aspect is not same as window aspect then compute cover size
	myFrameSprite->SetSize(Metrics::GetReferenceSize());

	myFrameSprite->SetLayer(GameLayer::Cutscene);

	myVideo->Play();

	return true;
}

void CutscenePlayer::Update(const float aDeltaTime)
{
	myVideo->Update(aDeltaTime);
}

void CutscenePlayer::Render(RenderQueue* const aRenderQueue)
{
	aRenderQueue->Queue(RenderCommand(myFrameSprite));
}

bool CutscenePlayer::IsPlaying()
{
	return myVideo->GetStatus() == Tga2D::VideoStatus::VideoStatus_Playing;
}
