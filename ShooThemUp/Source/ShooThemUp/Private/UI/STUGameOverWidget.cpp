// Shoot Them Up Game. All Rights Reserved.,


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "STUPlayerState.h"
#include "STUPlayerStatRowWidget.h"
#include "STUUtils.h"
#include "Components/VerticalBox.h"

bool USTUGameOverWidget::Initialize()
{
    if (GetWorld())
    {
        const auto Gamemode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (Gamemode)
        {
            Gamemode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
        }
    }
    return Super::Initialize();
}

void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State) 
{
    if (State == ESTUMatchState::GameOver)
    {
        UpdatePlayersStat();
    }
}

void USTUGameOverWidget::UpdatePlayersStat() 
{
    if (!GetWorld() || !PlayerStatBox) return;

    PlayerStatBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It;++It)
    {
        const auto Controller = It->Get();
        if (!Controller) return;

        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        const auto PlayerStatRowWidget = CreateWidget<USTUPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStatRowWidget) continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatRowWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayerStatRowWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }
}
