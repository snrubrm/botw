#include "Game/AI/AI/aiZoraHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

ZoraHeroSoulGiftRoot::ZoraHeroSoulGiftRoot(const InitArg& arg) : HeroSoulGiftRoot(arg) {}

ZoraHeroSoulGiftRoot::~ZoraHeroSoulGiftRoot() = default;

bool ZoraHeroSoulGiftRoot::init_(sead::Heap* heap) {
    return HeroSoulGiftRoot::init_(heap);
}

void ZoraHeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _89 = ui::isPauseMenuScreenNotClosed();
    _8c = 30;
    HeroSoulGiftRoot::enter_(params);
}

void ZoraHeroSoulGiftRoot::leave_() {
    HeroSoulGiftRoot::leave_();
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115B01C(0, 0, false);
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

bool ZoraHeroSoulGiftRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x800007b) {
        _89 = true;
        return true;
    }
    return HeroSoulGiftRoot::handleMessage_(message);
}

}  // namespace uking::ai
