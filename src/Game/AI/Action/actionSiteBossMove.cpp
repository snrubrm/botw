#include "Game/AI/Action/actionSiteBossMove.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossMove::SiteBossMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossMove::~SiteBossMove() = default;

bool SiteBossMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getCharacterController()) {
        setFailed();
        return;
    }
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    _6c = mActor->getVelocity();
    _68 = mActor->getVelocity().length();
    sub_710073FA90(&_84, mActor);
    _78 = *mMoveDstPos_d;
    mFlags.set(Flag::Changeable);
    _ac = 0;
}

void SiteBossMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossMove::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mUpdownSpeed_s, "UpdownSpeed");
    getStaticParam(&mAmplitude_s, "Amplitude");
    getStaticParam(&mRotateRate_s, "RotateRate");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
}

void SiteBossMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
