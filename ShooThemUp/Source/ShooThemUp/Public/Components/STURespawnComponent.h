// Shoot Them Up Game. All Rights Reserved.,

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTHEMUP_API USTURespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    USTURespawnComponent();

    void Respawn(int32 RespawnTime);

    int32 GetRespawnCountDown() const { return RespawnCountDown; }
    bool IsRespawnableInProgress() const;

private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountDown = 0;
    void RespawnTimerUpdate();
};
