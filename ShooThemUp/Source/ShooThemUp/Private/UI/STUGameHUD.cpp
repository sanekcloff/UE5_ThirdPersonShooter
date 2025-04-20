// Shoot Them Up Game. All Rights Reserved.,


#include "STUGameHUD.h"
#include "Engine/Canvas.h"
#include "UI/STUGameHUD.h"
#include "Blueprint/UserWidget.h"

void ASTUGameHUD::DrawHUD() 
{
    Super::DrawHUD();

    //DrawCrossHair();
}

void ASTUGameHUD::BeginPlay() 
{
    Super::BeginPlay();
    auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHudWidgetClass);
    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
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
