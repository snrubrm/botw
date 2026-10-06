#include "Game/AI/AI/aiGuardNearTarget.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

GuardNearTarget::GuardNearTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardNearTarget::~GuardNearTarget() = default;

bool GuardNearTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original inlines the RootAi flag-2 test here (testRootAiFlag2 is an out-of-line call
// everywhere else); an extra inline-only accessor reproduced it but was rejected as invented.
void GuardNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    const float distance = sub_710044C9E8();
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1)) {
        changeToGuardWait();
    } else if (m34(distance)) {
        changeToStartGuard();
    } else {
        changeToNormal();
    }
}

// Child names: 通常 (normal), ガード開始 (start guard), ガード待機 (guard wait), ガード終了 (end guard).
void GuardNearTarget::calc_() {
    const float distance = sub_710044C9E8();
    auto* child = getCurrentChild();
    child->setDynamicParam(*mParams.mTargetPos_d, "TargetPos");
    if (!child->isFinished() && !child->isFailed()) {
        if (child->isChangeable()) {
            if (!isCurrentChild("通常") && !isCurrentChild("ガード終了")) {
                if (!isCurrentChild("ガード待機"))
                    return;
                if (!m36(distance))
                    return;
                changeToEndGuard();
                return;
            }
            if (m35(distance)) {
                changeToStartFastGuard();
            } else if (m34(distance)) {
                changeToStartGuard();
            }
        }
    } else if (!isCurrentChild("ガード開始") && !isCurrentChild("高速ガード開始")) {
        if (isCurrentChild("ガード待機")) {
            changeToEndGuard();
            return;
        }
        if (isCurrentChild("ガード終了")) {
            changeToNormal();
            return;
        }
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else {
        changeToGuardWait();
    }
}

void GuardNearTarget::changeToGuardWait() {
    m37(true);
    _60._25 = true;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
    changeChild("ガード待機", &pack);
}

void GuardNearTarget::changeToEndGuard() {
    m37(false);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
    changeChild("ガード終了", &pack);
}

void GuardNearTarget::changeToNormal() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
    changeChild("通常", &pack);
}

float GuardNearTarget::sub_710044C9E8() const {
    return (mActor->getMtx().getTranslation() - *mParams.mTargetPos_d).length();
}

void GuardNearTarget::changeToStartGuard() {
    if (m38()) {
        m37(true);
        _60._25 = false;
    }
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
    changeChild("ガード開始", &params);
}

void GuardNearTarget::leave_() {
    m37(false);
}

void GuardNearTarget::loadParams_() {
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mBaseDist_s, "BaseDist");
    getStaticParam(&mParams.mGuardStartDist_s, "GuardStartDist");
    getStaticParam(&mParams.mGuardEndDist_s, "GuardEndDist");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
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
    return *mParams.mBaseDist_s + *mParams.mGuardStartDist_s + sub_71007320F0(mActor, *mParams.mWeaponIdx_s) >= distance;
}

bool GuardNearTarget::m36(float distance) {
    return *mParams.mBaseDist_s + *mParams.mGuardEndDist_s + sub_71007320F0(mActor, *mParams.mWeaponIdx_s) < distance;
}

void GuardNearTarget::changeToStartFastGuard() {
    if (m38()) {
        m37(true);
        _60._25 = false;
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
    changeChild("高速ガード開始", &pack);
}

}  // namespace uking::ai
