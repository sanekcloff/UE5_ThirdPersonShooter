// Shoot Them Up Game. All Rights Reserved.,

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlayerName(const FText& Text);
    void SetKills(const FText& Text);
    void SetDeaths(const FText& Text);
    void SetTeam(const FText& Text);
    void SetPlayerIndicatorVisibility(bool Visible);

protected:
    UPROPERTY(meta = (BindWidth))
    UTextBlock* PlayerNameTextBlock;

    UPROPERTY(meta = (BindWidth))
    UTextBlock* KillsTextBlock;

    UPROPERTY(meta = (BindWidth))
    UTextBlock* DeathsTextBlock;

    UPROPERTY(meta = (BindWidth))
    UTextBlock* TeamTextBlock;

    UPROPERTY(meta = (BindWidth))
    UImage* PlayerIndicatorImage;
};
