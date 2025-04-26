// Shoot Them Up Game. All Rights Reserved.,


#include "STUGameHUD.h"
#include "Engine/Canvas.h"
#include "STUGameModeBase.h"
#include "UI/STUBaseWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);

void ASTUGameHUD::DrawHUD() 
{
    Super::DrawHUD();

    //DrawCrossHair();
}

void ASTUGameHUD::BeginPlay() 
{
    Super::BeginPlay();

    GameWidgets.Add(ESTUMatchState::InProgress,CreateWidget<USTUBaseWidget>(GetWorld(),PlayerHudWidgetClass));
    GameWidgets.Add(ESTUMatchState::Pause, CreateWidget<USTUBaseWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(ESTUMatchState::GameOver, CreateWidget<USTUBaseWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto Gamemode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (Gamemode)
        {
            Gamemode->OnMatchStateChanged.AddUObject(this,&ASTUGameHUD::OnMatchStateChanged);
        }
    }
}

void ASTUGameHUD::DrawCrossHair()
{
    int32 SizeX = Canvas->SizeX;
    int32 SizeY = Canvas->SizeY;
    const TInterval<float> Center(SizeX*0.5f,SizeY*0.5f);

    const float HalfLineSize = 10.0f;
    const float LineThicness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Red;

    DrawLine(Center.Min-HalfLineSize,Center.Max, Center.Min+ HalfLineSize,Center.Max,LineColor,LineThicness);
    DrawLine(Center.Min,Center.Max- HalfLineSize, Center.Min,Center.Max + HalfLineSize,LineColor,LineThicness);
}

void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState State) 
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        CurrentWidget->Show();
    }
    UE_LOG(LogSTUGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}
