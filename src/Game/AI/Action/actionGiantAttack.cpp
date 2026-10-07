#include "Game/AI/Action/actionGiantAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"

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

void GiantAttack::sub_71002A182C() {
    if (sub_71005DD5B0(mActor, 0x29, nullptr, 0, 0))
        sub_71002A1A08();
    if (sub_71005DD798(mActor, 0x29, nullptr, 0, 0)) {
        sub_71002A1C38();
        return;
    }
    auto* controller = mActor->getCharacterController();
    if (controller) {
        sub_7100737C0C(controller, *mStopSpeedRatio_s, -sead::Vector3f::ey);
        sub_7100738660(controller, *mStopRotSpeedRatio_s);
    }
}

void GiantAttack::calc_() {
    sub_71002A182C();
}

}  // namespace uking::action
