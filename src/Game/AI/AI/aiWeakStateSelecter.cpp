#include "Game/AI/AI/aiWeakStateSelecter.h"

namespace uking::ai {

WeakStateSelecter::WeakStateSelecter(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeakStateSelecter::~WeakStateSelecter() = default;

bool WeakStateSelecter::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeakStateSelecter::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsWeakPointAppearMode_a)
        changeChild("弱点モード", params);
    else
        changeChild("通常モード", params);
}

void WeakStateSelecter::calc_() {
    if (!*mIsAlwaysUpdate_s)
        return;

    if (*mIsWeakPointAppearMode_a) {
        if (!isCurrentChild("弱点モード"))
            changeChild("弱点モード");
    } else {
        if (!isCurrentChild("通常モード"))
            changeChild("通常モード");
    }
}

void WeakStateSelecter::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeakStateSelecter::loadParams_() {
    getStaticParam(&mIsAlwaysUpdate_s, "IsAlwaysUpdate");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
}

}  // namespace uking::ai
