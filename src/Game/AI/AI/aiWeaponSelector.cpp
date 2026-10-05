#include "Game/AI/AI/aiWeaponSelector.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

WeaponSelector::WeaponSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool WeaponSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71005DBB60(mActor, 0) != -1) {
        sub_71005F13D4(params);
        return;
    }
    auto* actor = mActor;
    if (sub_71005DB904(actor, sub_71005DB96C(actor)))
        sub_71005F13D4(params);
    else
        changeChild("素手", params);
}

void WeaponSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponSelector::loadParams_() {}

}  // namespace uking::ai
