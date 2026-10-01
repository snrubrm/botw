#include "Game/AI/AI/aiHeroSoulGiftRoot.h"
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
    ksys::act::ai::Ai::leave_();
}

void HeroSoulGiftRoot::loadParams_() {
    getStaticParam(&mUseInitMtxForBasePos_s, "UseInitMtxForBasePos");
    getStaticParam(&mUseInitMtxForBaseRot_s, "UseInitMtxForBaseRot");
    getStaticParam(&mPosOffset_s, "PosOffset");
    getStaticParam(&mRotOffset_s, "RotOffset");
}

bool HeroSoulGiftRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x8000036) {
        _88 = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
