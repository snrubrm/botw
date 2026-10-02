#include "Game/AI/Action/actionDragonMoveTo.h"
#include "Game/Actor/actDragon.h"

namespace uking::action {

DragonMoveTo::DragonMoveTo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DragonMoveTo::~DragonMoveTo() {
    _f8.freeBuffer();
}

bool DragonMoveTo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DragonMoveTo::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;
    _80._24 = false;
    _80._20 = -1.0f;
    _a8._20 = -1.0f;
    _a8._24 = false;
    _d0._20 = -1.0f;
    _d0._24 = false;
    _108 = dragon->sub_710001014C();
    _138 = dragon->sub_710001014C().getBase(1);
    if (mActor->getCharacterController())
        mFlags.set(Flag::Changeable);
}

void DragonMoveTo::leave_() {
    _80.handle.fadeXLink();
    _a8.handle.fadeXLink();
    _d0.handle.fadeXLink();
}

void DragonMoveTo::loadParams_() {
    getStaticParam(&mRollMax_s, "RollMax");
    getStaticParam(&mRollSpeed_s, "RollSpeed");
    getStaticParam(&mRollMaxSpeed_s, "RollMaxSpeed");
    getStaticParam(&mRollAmount_s, "RollAmount");
    getStaticParam(&mRestoreUp_s, "RestoreUp");
    getStaticParam(&mBackAdjustAngle_s, "BackAdjustAngle");
    getStaticParam(&mBackAdjustRestoreUp_s, "BackAdjustRestoreUp");
    getStaticParam(&mFixAngle_s, "FixAngle");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mFrontDir_d, "FrontDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void DragonMoveTo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
