#include "Game/Actor/Action/actionHorseRideLoopAttack.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

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

// NON_MATCHING: stack layout (the Unk_71002edaec temporary sits above the ASList query in the original, as in
// HorseRideAttack::calc_).
// Attacks on every AS attack event until LoopAttackTime has passed or (with IsFinishByAtHit) the actor,
// the actor it rides or its weapon hit something; then plays FinishAS and finishes with it.
void HorseRideLoopAttack::calc_() {
    HorseRideBase::calc_();

    auto* actor = mActor;
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(actor, &query, 0, 0)) {
        if (*mIsNoRodAttack_s)
            sub_71005D7F4C(actor, *mWeaponIdx_s, 1, &query.name, nullptr, 1, 1.0f, 1.0f);
        else
            sub_71005D7ADC(actor, *mWeaponIdx_s, 1, &query.name, nullptr, 1, 1, 0, 1, 1.0f, 1.0f);
    } else if (sub_71005DD74C(actor, nullptr, 0, 0)) {
        sub_71005D79AC(actor, *mWeaponIdx_s, act::Unk_71002edaec(1));
    }

    switch (_7c) {
    case 0: {
        _70.update();
        bool finish;
        if (_70.value > static_cast<f32>(*mLoopAttackTime_s)) {
            finish = true;
        } else if (!*mIsFinishByAtHit_s) {
            finish = false;
        } else if (hasAttackInfo(mActor)) {
            finish = true;
        } else {
            auto* info = mActor->getPlayerRideInfo();
            auto* ride_actor =
                info ? sead::DynamicCast<ksys::act::Actor>(info->_18.getProc(nullptr, info->mActor)) :
                       nullptr;
            finish = (ride_actor && hasAttackInfo(ride_actor)) ||
                     sub_71005DAA70(mActor, *mWeaponIdx_s);
        }
        if (finish) {
            _7c = 1;
            if (mFinishAS_s.isEmpty())
                setFinished();
            else
                sub_71001AD8A0(mFinishAS_s.cstr(), true);
        }
        break;
    }
    case 1:
        if (sub_71001ADA78())
            setFinished();
        break;
    }
}

}  // namespace uking::action
