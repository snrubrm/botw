#include "Game/Actor/Action/actionHorseRideLoopAttack.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

HorseRideLoopAttack::HorseRideLoopAttack(const InitArg& arg) : HorseRideBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
HorseRideLoopAttack::~HorseRideLoopAttack() {
    ;
}

bool HorseRideLoopAttack::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideLoopAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
    if (!mASName_s.isEmpty())
        sub_71001AD8A0(mASName_s.cstr(), true);
    mFlags.reset(Flag::Changeable);
    _70 = ksys::Timer(0, 0, 1.0f);
    _7c = 0;
}

void HorseRideLoopAttack::leave_() {
    sub_71005D79AC(mActor, *mWeaponIdx_s, act::Unk_71002edaec(1));
    HorseRideBase::leave_();
}

void HorseRideLoopAttack::loadParams_() {
    HorseRideBase::loadParams_();
    getStaticParam(&mLoopAttackTime_s, "LoopAttackTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsFinishByAtHit_s, "IsFinishByAtHit");
    getStaticParam(&mIsNoRodAttack_s, "IsNoRodAttack");
    getStaticParam(&mFinishAS_s, "FinishAS");
    getStaticParam(&mASName_s, "ASName");
}

void HorseRideLoopAttack::calc_() {
    HorseRideBase::calc_();
}

}  // namespace uking::action
