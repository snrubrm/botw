#include "Game/AI/Action/actionSiteBossBowMoveForArrowRain.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossBowMoveForArrowRain::SiteBossBowMoveForArrowRain(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossBowMoveForArrowRain::~SiteBossBowMoveForArrowRain() = default;

bool SiteBossBowMoveForArrowRain::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossBowMoveForArrowRain::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossBowMoveForArrowRain::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void SiteBossBowMoveForArrowRain::loadParams_() {
    getStaticParam(&mFirstMoveSpeed_s, "FirstMoveSpeed");
    getStaticParam(&mFirstAccelFrame_s, "FirstAccelFrame");
    getStaticParam(&mSecondMoveSpeed_s, "SecondMoveSpeed");
    getStaticParam(&mSecondAccelFrame_s, "SecondAccelFrame");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mMoveTarget_s, "MoveTarget");
}

void SiteBossBowMoveForArrowRain::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
