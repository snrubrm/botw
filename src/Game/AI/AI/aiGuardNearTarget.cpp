#include "Game/AI/AI/aiGuardNearTarget.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

// NON_MATCHING: store scheduling (the original pairs the callback's vtable with its mPrev store)
GuardNearTarget::GuardNearTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardNearTarget::~GuardNearTarget() = default;

bool GuardNearTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original inlines the RootAi flag test (testRootAiFlag2 is out-of-line here)
void GuardNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    const float distance = sub_710044C9E8();
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1)) {
        m37(true);
        _60._25 = true;
        ksys::act::ai::InlineParamPack params_;
        params_.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("ガード待機", &params_);
    } else if (m34(distance)) {
        sub_710044CA3C();
    } else {
        ksys::act::ai::InlineParamPack params_;
        params_.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("通常", &params_);
    }
}

float GuardNearTarget::sub_710044C9E8() const {
    return (mActor->getMtx().getTranslation() - *mTargetPos_d).length();
}

void GuardNearTarget::sub_710044CA3C() {
    if (m38()) {
        m37(true);
        _60._25 = false;
    }
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("ガード開始", &params);
}

void GuardNearTarget::leave_() {
    m37(false);
}

void GuardNearTarget::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mGuardStartDist_s, "GuardStartDist");
    getStaticParam(&mGuardEndDist_s, "GuardEndDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool GuardNearTarget::isChangeable() const {
    return getCurrentChild()->isChangeable() && isCurrentChild("通常");
}

void GuardNearTarget::m37(bool enable) {
    auto* damage_mgr = mActor->getDamageMgr();
    if (enable) {
        if (!_60.mDamageManager)
            damage_mgr->addDamageCallback(4, &_60);
    } else {
        damage_mgr->removeDamageCallback(&_60);
    }
}

bool GuardNearTarget::m34(float distance) {
    return *mBaseDist_s + *mGuardStartDist_s + sub_71007320F0(mActor, *mWeaponIdx_s) >= distance;
}

bool GuardNearTarget::m36(float distance) {
    return *mBaseDist_s + *mGuardEndDist_s + sub_71007320F0(mActor, *mWeaponIdx_s) < distance;
}

}  // namespace uking::ai
