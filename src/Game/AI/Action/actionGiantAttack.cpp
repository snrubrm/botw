#include "Game/AI/Action/actionGiantAttack.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GiantAttack::GiantAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GiantAttack::~GiantAttack() = default;

bool GiantAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GiantAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mRotBaseBoneName_s.isEmpty())
        return;
    _90.setName(mRotBaseBoneName_s);
    _90.sub_7100743414(0, true, 0);
}

void GiantAttack::leave_() {
    if (mRotBaseBoneName_s.isEmpty())
        return;
    mActor->sub_71011DA868(&_90);
}

void GiantAttack::loadParams_() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mRotBaseBoneName_s, "RotBaseBoneName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GiantAttack::calc_() {
    sub_71002A182C();
}

}  // namespace uking::action
