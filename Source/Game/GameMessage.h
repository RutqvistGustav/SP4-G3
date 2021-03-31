#pragma once

enum class GameMessage
{
	CheckpointSave,
	CheckpointLoad,

	SpawnEnemy,
	EnemyDied,

	InteractableEnter,
	InteractableExit,
};
