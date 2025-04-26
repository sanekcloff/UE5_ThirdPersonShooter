// Shoot Them Up Game. All Rights Reserved.,

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STULevelItemUserWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class SHOOTHEMUP_API USTULevelItemUserWidget : public UUserWidget
{
    GENERATED_BODY()

    public:
    FOnLevelSelectedSignature OnLevelSelected;

    void SetLevelData(const FLevelData& Data);
    FLevelData GetLevelData() const { return LevelData; }
    void SetSelected(bool IsSelected);

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* LevelSelectButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* LevelImage = nullptr;

    UPROPERTY(meta = (BindWidget))
    UImage* FrameImage;

    virtual void NativeOnInitialized() override;

private:
    FLevelData LevelData;

    UFUNCTION()
    void OnLevelItemClicked();

    UFUNCTION()
    void OnLevelItemHovered();
    
    UFUNCTION()
    void OnLevelItemUnhovered();
};
