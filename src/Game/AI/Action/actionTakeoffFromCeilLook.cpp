#include "Game/AI/Action/actionTakeoffFromCeilLook.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

TakeoffFromCeilLook::TakeoffFromCeilLook(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TakeoffFromCeilLook::~TakeoffFromCeilLook() = default;

bool TakeoffFromCeilLook::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TakeoffFromCeilLook::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710073FA90(&_50, mActor);
    playAS("WaitEnd", false, 0, 0, -1.0f);
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    actor->getMtx().getBase(_74, 2);
    _74 = -_74;
    ksys::util::sub_71011EFA00(&_74, _74, controller->get7c());
    _74.normalize();
}

void TakeoffFromCeilLook::leave_() {
    ksys::act::ai::Action::leave_();
}

void TakeoffFromCeilLook::loadParams_() {
    getStaticParam(&mDescentSpeed_s, "DescentSpeed");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
}

void TakeoffFromCeilLook::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
