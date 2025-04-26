// Shoot Them Up Game. All Rights Reserved.,


#include "Menu/UI/STULevelItemUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTULevelItemUserWidget::SetLevelData(const FLevelData& Data) 
{
    LevelData = Data;

    if (LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
    }

    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(Data.LevelThumb);
    }
}

void USTULevelItemUserWidget::SetSelected(bool IsSelected) 
{
    if (LevelImage)
    {
        LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
    }
}

void USTULevelItemUserWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();
    
    if (LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this,&USTULevelItemUserWidget::OnLevelItemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &USTULevelItemUserWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &USTULevelItemUserWidget::OnLevelItemUnhovered);
    }
}

void USTULevelItemUserWidget::OnLevelItemClicked() 
{
    OnLevelSelected.Broadcast(LevelData);
}

void USTULevelItemUserWidget::OnLevelItemHovered() 
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void USTULevelItemUserWidget::OnLevelItemUnhovered() 
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
}
