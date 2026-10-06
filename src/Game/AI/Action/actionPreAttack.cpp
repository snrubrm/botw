#include "Game/AI/Action/actionPreAttack.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PreAttack::PreAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PreAttack::~PreAttack() = default;

bool PreAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    sub_710073FA90(&_70, mActor);
    const sead::Vector3f axis = mActor->getMtx().getBase(2);
    sub_710072C1B4(controller, axis);
    setDamageCallbackTiming(mActor, 4, &_48);
}

void PreAttack::leave_() {
    sub_71005DA114(mActor, &_48);
}

void PreAttack::loadParams_() {
    getStaticParam(&mTurnSpd_s, "TurnSpd");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void PreAttack::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    const sead::Vector3f up = getUpDir(controller->get70());
    sead::Vector3f dir = *mTargetPos_d - mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&dir, dir, up);
    dir.normalize();
    sub_710073FA94(&_70, mActor);
    sub_710074006C(&_70, dir, up, true, 0.16f, *mTurnSpd_s, *mTurnSpd_s * 0.1f);
    sub_7100740E04(_70, controller);
    sub_7100737C0C(controller, *mPosReduceRatio_s, controller->get7c());
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
