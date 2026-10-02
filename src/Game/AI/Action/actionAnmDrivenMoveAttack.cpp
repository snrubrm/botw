#include "Game/AI/Action/actionAnmDrivenMoveAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
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

void AnmDrivenMoveAttack::calc_() {
    MoveByAnimeDriven::calc_();
}

}  // namespace uking::action
