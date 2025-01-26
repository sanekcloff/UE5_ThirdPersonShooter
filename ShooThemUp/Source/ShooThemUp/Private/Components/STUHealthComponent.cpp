// Shoot Them Up Game. All Rights Reserved.,

#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    SetHealth(MaxHealth);
    OnHealthChanged.Broadcast(Health);

    auto ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
    // ...
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
    SetHealth(Health - Damage);
    OnHealthChanged.Broadcast(Health);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(
            AutoHealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }

    UE_LOG(LogTemp, Warning, TEXT("%f"), Damage);
    if (DamageType)
    {
        if (DamageType->IsA<USTUFireDamageType>())
        {
            GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, TEXT("So hot!"));
        }
        else if (DamageType->IsA<USTUIceDamageType>())
        {
            GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Cyan, TEXT("So cold!"));
        }
    }
}

void USTUHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);
    OnHealthChanged.Broadcast(Health);

    if (FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(AutoHealTimerHandle);
    }
}

void USTUHealthComponent::SetHealth(float Value)
{
    Health = FMath::Clamp(Value, 0.0f, MaxHealth);
}
