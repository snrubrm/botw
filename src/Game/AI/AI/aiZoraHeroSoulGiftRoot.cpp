#include "Game/AI/AI/aiZoraHeroSoulGiftRoot.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

ZoraHeroSoulGiftRoot::ZoraHeroSoulGiftRoot(const InitArg& arg) : HeroSoulGiftRoot(arg) {}

ZoraHeroSoulGiftRoot::~ZoraHeroSoulGiftRoot() = default;

bool ZoraHeroSoulGiftRoot::init_(sead::Heap* heap) {
    return HeroSoulGiftRoot::init_(heap);
}

void ZoraHeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HeroSoulGiftRoot::enter_(params);
}

void ZoraHeroSoulGiftRoot::leave_() {
    HeroSoulGiftRoot::leave_();
}

void ZoraHeroSoulGiftRoot::loadParams_() {
    HeroSoulGiftRoot::loadParams_();
}

void ZoraHeroSoulGiftRoot::calc_() {
    HeroSoulGiftRoot::calc_();
    if (_8c != 0) {
        --_8c;
        if (_8c == 1)
            _89 = true;
    }
}

bool ZoraHeroSoulGiftRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x800007b) {
        _89 = true;
        return true;
    }
    return HeroSoulGiftRoot::handleMessage_(message);
}

}  // namespace uking::ai
