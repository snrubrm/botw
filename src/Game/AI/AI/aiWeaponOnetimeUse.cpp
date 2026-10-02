#include "Game/AI/AI/aiWeaponOnetimeUse.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WeaponOnetimeUse::WeaponOnetimeUse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponOnetimeUse::~WeaponOnetimeUse() = default;

bool WeaponOnetimeUse::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponOnetimeUse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack child_params;
    child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("抜刀", &child_params);
}

void WeaponOnetimeUse::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("抜刀")) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("使用", &params);
        } else if (isCurrentChild("使用")) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("納刀", &params);
        } else {
            setFinished();
        }
    }
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void WeaponOnetimeUse::leave_() {
    sub_71005DB6D0(mActor, *mWeaponIdx_s);
}

void WeaponOnetimeUse::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
