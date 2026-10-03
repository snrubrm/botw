#include "Game/AI/Action/actionSiteBossSpearChangeWaterLevel.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SiteBossSpearChangeWaterLevel::SiteBossSpearChangeWaterLevel(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossSpearChangeWaterLevel::~SiteBossSpearChangeWaterLevel() = default;

bool SiteBossSpearChangeWaterLevel::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSpearChangeWaterLevel::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    mActor->getMtx().getTranslation(_3c);
    _48 = 240.0f;
    _4c = 240.0f;
    _50 = -1.0f;
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
    _38 = false;
}

void SiteBossSpearChangeWaterLevel::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5F6FC(sead::Vector3f::zero);
}

void SiteBossSpearChangeWaterLevel::loadParams_() {
    getStaticParam(&mIsSignalOn_s, "IsSignalOn");
    getStaticParam(&mASName_s, "ASName");
}

void SiteBossSpearChangeWaterLevel::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
