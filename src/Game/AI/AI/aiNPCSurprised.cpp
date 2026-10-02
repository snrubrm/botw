#include "Game/AI/AI/aiNPCSurprised.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

NPCSurprised::NPCSurprised(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCSurprised::~NPCSurprised() = default;

bool NPCSurprised::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCSurprised::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCSurprised::calc_() {
    if (isCurrentChild("驚く")) {
        if (getCurrentChild()->isFinished()) {
            if (!*mIsNeedUnEquipWeapon_d || sub_71005DB7E4(mActor, 0))
                setFinished();
            else
                changeChild("納刀");
        }
    } else if (isCurrentChild("納刀")) {
        if (getCurrentChild()->isFinished())
            setFinished();
    }
}

void NPCSurprised::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCSurprised::loadParams_() {
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsNeedUnEquipWeapon_d, "IsNeedUnEquipWeapon");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

}  // namespace uking::ai
