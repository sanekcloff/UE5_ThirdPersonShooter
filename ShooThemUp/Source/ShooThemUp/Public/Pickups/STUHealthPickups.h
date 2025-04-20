// Shoot Them Up Game. All Rights Reserved.,

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickups.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTHEMUP_API ASTUHealthPickups : public ASTUBasePickup
{
	GENERATED_BODY()
protected:
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
      float HealthAmount = 100.0f;

  private:
      virtual bool GivePickUpTo(APawn* PlayerPawn) override;
	
};
