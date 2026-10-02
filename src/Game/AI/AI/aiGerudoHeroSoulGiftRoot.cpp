#include "Game/AI/AI/aiGerudoHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GerudoHeroSoulGiftRoot::GerudoHeroSoulGiftRoot(const InitArg& arg) : HeroSoulGiftRoot(arg) {}

GerudoHeroSoulGiftRoot::~GerudoHeroSoulGiftRoot() = default;

bool GerudoHeroSoulGiftRoot::init_(sead::Heap* heap) {
    return HeroSoulGiftRoot::init_(heap);
}

void GerudoHeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    {
        auto* actor = mActor;
        sead::ScopedLock<sead::JobQueueLock> lock(&_b8._18.mLock);
        _b8._18.mLink.acquire(actor, false);
        _b8._18._10 = 100.0f;
    }
    HeroSoulGiftRoot::enter_(params);
    _9c = false;
    _9d = false;
    if (auto* awareness = mActor->getAwareness())
        awareness->enable();
    _98 = 10;
}

void GerudoHeroSoulGiftRoot::leave_() {
    HeroSoulGiftRoot::leave_();
    if (auto* awareness = mActor->getAwareness())
        awareness->disable();
    _9c = false;
}

void GerudoHeroSoulGiftRoot::loadParams_() {
    HeroSoulGiftRoot::loadParams_();
    getStaticParam(&mMaxLength_s, "MaxLength");
}

bool GerudoHeroSoulGiftRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x8000028 && isCurrentChild("待機")) {
        _9c = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
