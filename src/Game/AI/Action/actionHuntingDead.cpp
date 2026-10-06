#include "Game/AI/Action/actionHuntingDead.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

HuntingDead::HuntingDead(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HuntingDead::~HuntingDead() = default;

void HuntingDead::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, "Dead", 0, 0, true);
    if (auto* controller = mActor->getCharacterController()) {
        sub_71001B4AFC(controller);
        controller->sub_7100F5E7F0(0.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        controller->_a0.getTranslation(_48);
        if (mActor->getASList()->sub_710115AA68("Dead"))
            return;
    }
    setFailed();
}

// NON_MATCHING: the original tail-calls sub_7100F5F458 from both branches, loads the actor's y before _6f0 and
// the InWaterDepth param after the subtraction.
void HuntingDead::sub_71001B4AFC(ksys::phys::CharacterController* controller) {
    if (!controller)
        return;
    auto* actor = mActor;
    const f32 y = actor->getMtx().m[1][3];
    if (actor->get68f() && actor->get6f0() - y > *mInWaterDepth_s) {
        const ksys::act::MotionType current = controller->sub_7100F5F0E4();
        if (int(current) != int(ksys::act::MotionType::Hover))
            controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    } else {
        const ksys::act::MotionType ground = controller->sub_7100F5F0E4();
        if (int(ground) == int(ksys::act::MotionType::_0))
            return;
        const ksys::act::MotionType current = controller->sub_7100F5F0E4();
        if (int(current) != int(ksys::act::MotionType::_1))
            controller->sub_7100F5F458(ksys::act::MotionType::_1);
    }
}

void HuntingDead::leave_() {
    ksys::act::ai::Action::leave_();
}

void HuntingDead::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mIsUseOffsetY_s, "IsUseOffsetY");
    getStaticParam(&mOffsetBoneName_s, "OffsetBoneName");
    getStaticParam(&mExtraOffset_s, "ExtraOffset");
}

void HuntingDead::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
