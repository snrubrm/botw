#include <basis/seadNew.h>
#include "aal/aalActiveSoundLimiter.h"

namespace aal {

// 0x7100b83514
ActiveSoundLimiter* LimiterUtil::createActiveSoundLimiter(ActiveSoundLimiterType type, sead::Heap* heap) {
    switch (type) {
    case ActiveSoundLimiterType::PriorityEarlier:
        return new (heap) ActiveSoundLimiterPriorityEarlier;
    case ActiveSoundLimiterType::PriorityLater:
        return new (heap) ActiveSoundLimiterPriorityLater;
    case ActiveSoundLimiterType::Earlier:
        return new (heap) ActiveSoundLimiterEarlier;
    case ActiveSoundLimiterType::Later:
        return new (heap) ActiveSoundLimiterLater;
    default:
        return nullptr;
    }
}

// 0x7100b835e4
s32 LimiterUtil::getMaxActiveSoundLimiterSize() {
    return sizeof(ActiveSoundLimiter);
}

}  // namespace aal
