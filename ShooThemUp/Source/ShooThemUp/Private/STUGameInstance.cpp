// Shoot Them Up Game. All Rights Reserved.,


#include "STUGameInstance.h"
#include "Sound/STUSoundFunctLib.h"

void USTUGameInstance::ToggleVolume() 
{
    USTUSoundFunctLib::ToggleSoundClassVolume(MasterSoundClass);
}
