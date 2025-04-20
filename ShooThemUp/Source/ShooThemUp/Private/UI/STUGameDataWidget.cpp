// Shoot Them Up Game. All Rights Reserved.,


#include "UI/STUGameDataWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"

int32 USTUGameDataWidget::GetKillsNum() const
{
    const auto PlayerState = GetSTUPlayerState();

    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 USTUGameDataWidget::GetDeathsNum() const
{
    const auto PlayerState = GetSTUPlayerState();

    return PlayerState ? PlayerState->GetDeathsNum() : 0;
}

int32 USTUGameDataWidget::GetCurrentRoundNum() const
{
    const auto Gamemode = GetSTUGamemode();

    return Gamemode ? Gamemode->GetCurrentRoundNum() : 0;
}

int32 USTUGameDataWidget::GetTotalsRoundNum() const
{
    const auto Gamemode = GetSTUGamemode();

    return Gamemode ? Gamemode->GetGameData().RoundsNum : 0;
}

int32 USTUGameDataWidget::GetRoundSecondsRemaining() const
{
    const auto Gamemode = GetSTUGamemode();

    return Gamemode ? Gamemode->GetRoundSecondsRemaining() : 0;
}

ASTUGameModeBase* USTUGameDataWidget::GetSTUGamemode() const
{
    return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState() const
{
    return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
