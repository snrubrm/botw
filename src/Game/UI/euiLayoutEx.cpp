#include "Game/UI/euiLayoutEx.h"
#include <new>
#include <nn/ui2d/DrawInfo.h>
#include <nn/ui2d/Pane.h>
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

// 0x7100bde5a0
void LayoutEx::CalculateImpl(nn::ui2d::DrawInfo& info, bool force) {
    if (mPane) {
        nn::ui2d::Pane::CalculateContext context;
        context.Set(info, this);
        info.mLayout = this;
        mPane->Calculate(info, context, force);
        info.mLayout = nullptr;
    }
}

// 0x7100bde620
bool LayoutEx::BuildImpl(nn::ui2d::BuildResultInformation* result, nn::gfx::Device* device,
                         const void* data, nn::ui2d::ResourceAccessor* accessor,
                         const nn::ui2d::BuildArgSet& args,
                         const nn::ui2d::Layout::PartsBuildDataSet* parts) {
    const bool built = nn::ui2d::Layout::BuildImpl(result, device, data, accessor, args, parts);
    if (built)
        doInitializeDefalutAnimator_();
    return built;
}

// 0x7100bde458
void LayoutEx::setDrawTargetAnim(DrawTarget target) {
    if (_78)
        _78->Stop(int(target));
    for (auto& part : mPartsLayoutList)
        static_cast<LayoutEx*>(part.layout)->setDrawTargetAnim(target);
}

// 0x7100bdd524
AnimatorSet* LayoutEx::createAnimatorSet(const char* const* names, u32 count, bool enabled) {
    void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(AnimatorSet) + count * sizeof(Animator*), 4);
    if (!memory)
        return nullptr;
    auto* set = new (memory) AnimatorSet;
    set->setBuffer(count, reinterpret_cast<Animator**>(set + 1));
    for (u32 i = 0; i < count; ++i) {
        if (names[i] && names[i][0])
            set->setAnimator(i, tryCreateAnimatorAuto(names[i], i == 0 && enabled));
    }
    return set;
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
