#include "Game/UI/euiLayoutEx.h"
#include <new>
#include "Game/UI/euiAnimator.h"

namespace eui {

// 0x7100bdd16c
LayoutEx::LayoutEx(Screen* screen) : mScreen(screen) {}

// NON_MATCHING: the original snapshots mScreen before allocation; this natural body reads it at construction.
// 0x7100bdf0f0
LayoutEx* LayoutEx::m21() {
    void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(LayoutEx), 4);
    if (!memory)
        return nullptr;
    return new (memory) LayoutEx(mScreen);
}

// 0x7100bde308
bool LayoutEx::isAnimOpenEnd(bool recursive) const {
    if (mOpenAnimator && mOpenAnimator->mFrame != mOpenAnimator->GetFrameSize())
        return false;
    if (recursive) {
        for (const auto& part : mPartsLayoutList) {
            if (!static_cast<const LayoutEx*>(part.layout)->isAnimOpenEnd(true))
                return false;
        }
    }
    return true;
}

// NON_MATCHING: duplicate constant-return blocks remain around the recursive traversal.
// 0x7100bde39c
bool LayoutEx::isAnimCloseEnd(bool recursive) const {
    if (mCloseAnimator) {
        if (mCloseAnimator->mFrame != mCloseAnimator->GetFrameSize())
            return false;
        if (mCloseAnimator->mEnabled)
            return false;
    } else if (mOpenAnimator) {
        if (mOpenAnimator->mFrame != 0.0f)
            return false;
        if (mOpenAnimator->mEnabled)
            return false;
    }
    if (recursive) {
        for (const auto& part : mPartsLayoutList) {
            if (!static_cast<const LayoutEx*>(part.layout)->isAnimCloseEnd(true))
                return false;
        }
    }
    return true;
}

// 0x7100bdd41c
Animator* LayoutEx::createAnimatorAuto(const char* name, bool b) {
    return tryCreateAnimatorAuto(name, b);
}

// 0x7100bdd980
Animator* LayoutEx::tryCreateAnimatorAutoWithWarning(const char* name, bool b) {
    return tryCreateAnimatorAuto(name, b);
}

}  // namespace eui
