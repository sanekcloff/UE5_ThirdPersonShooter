// Shoot Them Up Game. All Rights Reserved.,

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "UI/STUBaseWidget.h"
#include "STUMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTUGameInstance;
class USTULevelItemUserWidget;

UCLASS()
class SHOOTHEMUP_API USTUMenuWidget : public USTUBaseWidget
{
    GENERATED_BODY()
protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    virtual void NativeOnInitialized() override;

private:

    UPROPERTY()
    TArray<USTULevelItemUserWidget*> LevelItemWidgets;

    UFUNCTION()
    void OnStartGame();
    UFUNCTION()
    void OnQuitGame();

    void InitLevelItem();
    void OnLevelSelected(const FLevelData& Data);
    USTUGameInstance* GetSTUGameInstance() const;
};
