#pragma once

#include "Weapon.h"
#include "CollisionListener.h"
#include <memory>

class Collider;

class Shotgun :
	public Weapon
{
public:

	Shotgun(Scene* aScene, IWeaponHolder* aWeaponHolder);
	virtual ~Shotgun() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	virtual void ActivatePowerUp(PowerUpType aPowerUpType) override;
	void UpdatePowerUps(const float aDeltaTime);

	virtual void Shoot() override;
	virtual void Boost() override;

	virtual void Reload();

protected:

	virtual void LoadJson(const JsonData& someJsonData) override;
	virtual void Setup() override;

	void SetLoadedAmmo(int anAmount);

	bool IsReloadingComplete() const;
	bool IsReloading() const;
	bool IsLoaded() const;

	void SpawnMuzzleFlash() const;

	virtual void OnStay(const CollisionInfo& someCollisionInfo) override;

private:

	std::shared_ptr<Collider> myShotVolume;
	// TODO: NOTE: If / when immediate shape test is available from CollisionManager this can be removed
	bool myIsShotVolumeActive{};

	int myLoadedAmmo{};

	float myTime{};

	float myNextFireTime{};
	float myReloadCompleteTime{ -1.0f };

	// Loaded from JSON
	int myAmmoPerClip{};

	float myReloadDuration{};

	int myDamage{};

	float myAoeAngle{};
	float myAoeLength{};

	float myRecoilKnockbackStrength{};
	float myBoostKnockBackStrength{};

	// PowerUp Variables
	PowerUpType myActivePowerUp;
	bool myIsPowerUpActive = false;

	float myPowerUpDuration{};
	float myPowerUpDamage{};
	float myPowerUpReloadDuration{};

	float myBerserkDuration{};
	float myBerserkDamage{};
	float myBerserkReloadDuration{};
};
