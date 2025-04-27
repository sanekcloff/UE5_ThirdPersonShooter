// Shoot Them Up Game. All Rights Reserved.,


#include "Weapon/STURifleWeapon.h"
#include "GameFramework/DamageType.h"
#include "Engine/DamageEvents.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "STUUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

ASTURifleWeapon::ASTURifleWeapon() 
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::StartFire()
{
    InitFX();
    GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &ASTURifleWeapon::MakeShoot, TimerBetweenShots, true);
    MakeShoot();
}
void ASTURifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShootTimerHandle);
    SetFXActive(false);
}

void ASTURifleWeapon::BeginPlay() 
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void ASTURifleWeapon::MakeShoot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector TraceFxEnd = TraceEnd;

    if (HitResult.bBlockingHit)
    {
        TraceFxEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);

        WeaponFXComponent->PlayImpactFX(HitResult);
    }
    SpawnTraceFX(GetMuzzleWorldLocation(), TraceFxEnd);
    
    DecreaseAmmmo();
}
bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}
void ASTURifleWeapon::Zoom(bool Enabled) 
{
    const auto Controller = Cast<APlayerController>(GetController());

    if (!Controller || !Controller->PlayerCameraManager) return;

    if (Enabled)
    {
        DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
    }

    Controller->PlayerCameraManager->SetFOV(Enabled ? FOVZoomAngle : DefaultCameraFOV);
}
void ASTURifleWeapon::InitFX() 
{
    if (!MuzzleFxComponent)
    {
        MuzzleFxComponent = SpawnMuzzleFx();
    }
    if (!FireAutioComponent)
    {
        FireAutioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    }
    SetFXActive(true);
}
void ASTURifleWeapon::SetFXActive(bool IsActive) 
{
    if (MuzzleFxComponent)
    {
        MuzzleFxComponent->SetPaused(!IsActive);
        MuzzleFxComponent->SetVisibility(IsActive, true);
    }
    if(FireAutioComponent)
    {
        IsActive ? FireAutioComponent->Play() : FireAutioComponent->Stop();
    }
}


void ASTURifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamageActor = HitResult.GetActor();
    if (!DamageActor) return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    DamageActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}

void ASTURifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) 
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX,TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName,TraceEnd);
    }
}

AController* ASTURifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
