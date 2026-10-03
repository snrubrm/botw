#include "Game/AI/AI/aiCloseSmallAttackBase.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

CloseSmallAttackBase::CloseSmallAttackBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void CloseSmallAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _80 = false;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const f32 dx = pos.x - mParams.mTargetPos_d->x;
    const f32 dz = pos.z - mParams.mTargetPos_d->z;
    if (sead::Mathf::sqrt(dx * dx + dz * dz) < *mParams.mCloseRadius_s + sub_71007320F0(mActor, *mParams.mWeaponIdx_s)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
        changeChild(m35(), &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
        changeChild(m34(), &pack);
    }
    if (*mParams.mIsIgnoreSmallHit_s)
        setDamageCallbackTiming(mActor, 4, &_58);
}

void CloseSmallAttackBase::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!isCurrentChild(m34())) {
            setFinished();
            return;
        }
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        const f32 dx = pos.x - mParams.mTargetPos_d->x;
        const f32 dz = pos.z - mParams.mTargetPos_d->z;
        if (sead::Mathf::sqrt(dx * dx + dz * dz) <
            *mParams.mCloseRadius_s + sub_71007320F0(mActor, *mParams.mWeaponIdx_s)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
            changeChild(m35(), &pack);
        } else {
            setFailed();
            return;
        }
    }
    child->setDynamicParam(*mParams.mTargetPos_d, "TargetPos");
}

void CloseSmallAttackBase::leave_() {
    sub_71005DA114(mActor, &_58);
}

void CloseSmallAttackBase::loadParams_() {
    getStaticParam(&mParams.mCloseRadius_s, "CloseRadius");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

bool CloseSmallAttackBase::isChangeable() const {
    if (isFinished())
        return true;
    return isFailed();
}

}  // namespace uking::ai
