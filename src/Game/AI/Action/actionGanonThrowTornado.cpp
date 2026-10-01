#include "Game/AI/Action/actionGanonThrowTornado.h"
#include "Game/AI/aiUnk_710073fa90.h"

namespace uking::action {

GanonThrowTornado::GanonThrowTornado(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonThrowTornado::~GanonThrowTornado() = default;

bool GanonThrowTornado::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonThrowTornado::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _68 = 0;
    sub_710073FA90(&_6c, mActor);
}

void GanonThrowTornado::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonThrowTornado::loadParams_() {
    getStaticParam(&mInitVelocity_s, "InitVelocity");
    getStaticParam(&mCreateHeight_s, "CreateHeight");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAppearOffset_s, "AppearOffset");
    getDynamicParam(&mThrowPartsName_d, "ThrowPartsName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void GanonThrowTornado::calc_() {
    ksys::act::ai::Action::calc_();
}

bool GanonThrowTornado::isFinished() const {
    return isFinishedAS(0, 0);
}

}  // namespace uking::action
