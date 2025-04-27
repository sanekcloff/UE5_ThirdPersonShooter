// Shoot Them Up Game. All Rights Reserved.,

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SHOOTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
    GENERATED_BODY()
public:
    ASTURifleWeapon();
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimerBetweenShots = 0.1f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 2.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 15.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float FOVZoomAngle = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    USTUWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;

    virtual void MakeShoot() override;

    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

    virtual void Zoom(bool Enabled) override;


private:
    FTimerHandle ShootTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFxComponent;
    UPROPERTY()

    UAudioComponent* FireAutioComponent;

    float DefaultCameraFOV = 90.0f;

    void InitFX();
    void SetFXActive(bool IsActive);

    void MakeDamage(const FHitResult& HitResult);

    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
    AController* GetController() const;
};
