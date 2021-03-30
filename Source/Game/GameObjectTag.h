#pragma once

enum class GameObjectTag
{
	Default,

	Player,
	Enemy,

	DamageVolume,

	Trigger,
	PowerUp,

	MousePointer,

	//Menu buttons
	StartButton,
	SettingsButton,
	BackButton,
	CreditsButton,
	LevelSelectButton,
	MuteButton,
	Level1Button,
	ArrowLeftButton,
	ArrowRightButton,
	QuitButton,

	//Sliders
	MasterSlider,
	SfxSlider,
	MusicSlider,

	// Level tags
	Level_1,
	Level_2,
	Level_3,
	Level_4
};
