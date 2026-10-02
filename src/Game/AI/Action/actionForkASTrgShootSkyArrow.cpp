#include "Game/AI/Action/actionForkASTrgShootSkyArrow.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkASTrgShootSkyArrow::ForkASTrgShootSkyArrow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgShootSkyArrow::~ForkASTrgShootSkyArrow() = default;

bool ForkASTrgShootSkyArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgShootSkyArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    _58 = false;
}

void ForkASTrgShootSkyArrow::leave_() {
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(5));
}

void ForkASTrgShootSkyArrow::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mBaseBoneName_s, "BaseBoneName");
    getStaticParam(&mFrontDirOfBaseBone_s, "FrontDirOfBaseBone");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void ForkASTrgShootSkyArrow::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
