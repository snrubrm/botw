#include "Game/AI/AI/aiHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

HeroSoulGiftRoot::HeroSoulGiftRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HeroSoulGiftRoot::~HeroSoulGiftRoot() = default;

bool HeroSoulGiftRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HeroSoulGiftRoot::leave_() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.reset(1);
}

void HeroSoulGiftRoot::loadParams_() {
    getStaticParam(&mUseInitMtxForBasePos_s, "UseInitMtxForBasePos");
    getStaticParam(&mUseInitMtxForBaseRot_s, "UseInitMtxForBaseRot");
    getStaticParam(&mPosOffset_s, "PosOffset");
    getStaticParam(&mRotOffset_s, "RotOffset");
}

bool HeroSoulGiftRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x8000036) {
        _88 = true;
        return true;
    }
    return false;
}

void HeroSoulGiftRoot::m36() {
    _88 = false;
    if (isCurrentChild("退場"))
        return;

    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_20))
        mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    else
        changeChild("退場");
}

}  // namespace uking::ai
