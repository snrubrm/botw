#include "Game/AI/AI/aiCloseSmallAttackBase.h"
#include "Game/Damage/dmgDamageCallback.h"

namespace uking::ai {

// NON_MATCHING: zero stores to 0x38-0x78 scheduled in a different order
CloseSmallAttackBase::CloseSmallAttackBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void CloseSmallAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CloseSmallAttackBase::leave_() {
    sub_71005DA114(mActor, &_58);
}

void CloseSmallAttackBase::loadParams_() {
    getStaticParam(&mCloseRadius_s, "CloseRadius");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool CloseSmallAttackBase::isChangeable() const {
    if (isFinished())
        return true;
    return isFailed();
}

}  // namespace uking::ai
