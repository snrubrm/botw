#include "Game/AI/Action/actionAnmDrivenMoveAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

AnmDrivenMoveAttack::AnmDrivenMoveAttack(const InitArg& arg) : MoveByAnimeDriven(arg) {}

AnmDrivenMoveAttack::~AnmDrivenMoveAttack() = default;

bool AnmDrivenMoveAttack::init_(sead::Heap* heap) {
    return MoveByAnimeDriven::init_(heap);
}

void AnmDrivenMoveAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveByAnimeDriven::enter_(params);
}

void AnmDrivenMoveAttack::leave_() {
    sub_71005D79AC(mActor, *mWeaponIdx_s, act::Unk_71002edaec(1));
    MoveByAnimeDriven::leave_();
}

void AnmDrivenMoveAttack::loadParams_() {
    MoveByAnimeDriven::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJustAvoidDist_s, "JustAvoidDist");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
}

// NON_MATCHING: the original loads *mIsForceGuardBreak_s before *mWeaponIdx_s, reloads mActor in the else branch and keeps
// the Unk4 query below the Unk_71002edaec temporary in the stack frame
void AnmDrivenMoveAttack::calc_() {
    if (sub_71005DAFB0(mActor)) {
        setFailed();
        return;
    }
    MoveByAnimeDriven::calc_();
    ksys::as::ASList::Unk4 query;
    sub_71005DAB2C(mActor, *mJustAvoidDist_s, *mJustAvoidDist_s, sead::numbers::pi_v<f32>, 0);
    if (sub_71005DD66C(mActor, &query, 0, 0)) {
        sub_71005D7ADC(mActor, *mWeaponIdx_s, *mIsForceGuardBreak_s ? 0x101 : 1, &query.name,
                       nullptr, 1, 1, 0, 1, 1.0f, 1.0f);
    } else if (sub_71005DD74C(mActor, nullptr, 0, 0)) {
        sub_71005D79AC(mActor, *mWeaponIdx_s, act::Unk_71002edaec(1));
    }
}

}  // namespace uking::action
