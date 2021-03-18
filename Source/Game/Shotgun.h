#pragma once

#include "Weapon.h"

#include <memory>

class Collider;

class Shotgun : public Weapon
{
public:

	Shotgun(Scene* aScene, IWeaponHolder* aWeaponHolder);
	virtual ~Shotgun() override;

	virtual void Update(float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	virtual void Shoot() override;

	virtual void Reload();

	virtual void OnCollision(GameObject* aGameObject) override;

protected:

	virtual void LoadJson(const JsonData& someJsonData) override;
	virtual void Setup() override;

	void SetLoadedAmmo(int anAmount);

	bool IsReloadingComplete() const;
	bool IsReloading() const;
	bool IsLoaded() const;

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

	float myDamage{};

	float myAoeAngle{};
	float myAoeLength{};

	float myRecoilKnockbackStrength{};

};
