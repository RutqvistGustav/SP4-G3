#pragma once

enum class GameMessage
{
	CheckpointSave,
	CheckpointLoad,

	SpawnEnemy,
	SpawnCollectable,
	EnemyDied,

	InteractableEnter,
	InteractableExit,

	StageClear,

	SpawnParticleEffect,
};
