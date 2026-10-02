#include "Game/AI/Action/actionFallAttack.h"
#include "KingSystem/ActorSystem/actUnk_71007A24BC.h"

namespace uking::action {

FallAttack::FallAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FallAttack::~FallAttack() = default;

bool FallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FallAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void FallAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAtkBodyName_s, "AtkBodyName");
    getStaticParam(&mJustAvoidDist_s, "JustAvoidDist");
}

void FallAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

int FallAttack::m32() {
    return 12;
}

int FallAttack::m33() {
    return 4;
}

bool FallAttack::isFinished() const {
    return ksys::act::sub_71007A4864(mActor, false);
}

}  // namespace uking::action
