// Shoot Them Up Game. All Rights Reserved.,


#include "UI/STUSpectatorWidget.h"
#include "STUUtils.h"
#include "STURespawnComponent.h"

bool USTUSpectatorWidget::GetRespawnTime(int32& CountDown) const
{
    const auto RespawnComponent = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnableInProgress()) return false;

    CountDown = RespawnComponent->GetRespawnCountDown();
    return true;
}
