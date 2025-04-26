// Shoot Them Up Game. All Rights Reserved.,

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTHEMUP_API ASTUMenuHUD : public AHUD
{
	GENERATED_BODY()
protected:
      UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;

      virtual void BeginPlay() override;
	
};
