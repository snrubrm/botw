#include "Game/AI/Action/actionHuntingDead.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

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
