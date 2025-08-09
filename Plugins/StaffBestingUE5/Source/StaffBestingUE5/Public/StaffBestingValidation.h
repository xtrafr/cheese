#pragma once

#include "CoreMinimal.h"

namespace StaffBestingValidation
{
    inline bool IsUE5OrNewer()
    {
    #if ENGINE_MAJOR_VERSION >= 5
        return true;
    #else
        return false;
    #endif
    }

    inline void GuardOrLogFatal()
    {
        if (!IsUE5OrNewer())
        {
            UE_LOG(LogTemp, Error, TEXT("StaffBestingUE5 requires UE5+. Failing closed."));
#if !UE_BUILD_SHIPPING
            checkf(false, TEXT("StaffBestingUE5 requires UE5+"));
#endif
        }
    }
}