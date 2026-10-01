#include "Game/AI/AI/aiUrbosasFuryDamageSelector.h"

namespace uking::ai {

UrbosasFuryDamageSelector::UrbosasFuryDamageSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

UrbosasFuryDamageSelector::~UrbosasFuryDamageSelector() = default;

bool UrbosasFuryDamageSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void UrbosasFuryDamageSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void UrbosasFuryDamageSelector::calc_() {
    auto* child = getCurrentChild();
    if (!child)
        return;

    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    }
    if (child->isChangeable())
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
}

void UrbosasFuryDamageSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void UrbosasFuryDamageSelector::loadParams_() {}

}  // namespace uking::ai
