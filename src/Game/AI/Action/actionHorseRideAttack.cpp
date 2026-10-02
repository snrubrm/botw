#include "Game/AI/Action/actionHorseRideAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseRideAttack::HorseRideAttack(const InitArg& arg) : HorseRideLookWait(arg) {}

HorseRideAttack::~HorseRideAttack() = default;

bool HorseRideAttack::init_(sead::Heap* heap) {
    return HorseRideLookWait::init_(heap);
}

void HorseRideAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideLookWait::enter_(params);
    mFlags.reset(Flag::Changeable);
    _70 = false;
}

void HorseRideAttack::leave_() {
    sub_71005D79AC(mActor, *mWeaponIdx_s, act::Unk_71002edaec(1));
    HorseRideLookWait::leave_();
}

void HorseRideAttack::loadParams_() {
    HorseRideLookWait::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
}

// NON_MATCHING: stack layout (the original keeps the Unk_71002edaec temporary above the ASList query)
void HorseRideAttack::calc_() {
    if (sub_71005DAFB0(mActor)) {
        setFailed();
        return;
    }

    auto* actor = mActor;
    const f32 base = sub_71007322E8(actor, *mWeaponIdx_s);
    sub_71005DAB2C(actor, base + *mJustAvoidSideDist_s, base + *mJustAvoidBackDist_s,
                   *mJustAvoidAngle_s, 0);

    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(actor, &query, 0, 0)) {
        sub_71005D7ADC(actor, *mWeaponIdx_s, _70 ? 0x41 : 1, &query.name, nullptr, 1, 1, 0, 1,
                       1.0f, 1.0f);
        _70 = true;
    } else if (sub_71005DD74C(actor, nullptr, 0, 0)) {
        sub_71005D79AC(actor, *mWeaponIdx_s, act::Unk_71002edaec(1));
    }

    if (sub_71001ADA78())
        setFinished();
    HorseRideLookWait::calc_();
}

}  // namespace uking::action
