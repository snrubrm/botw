#include "Game/AI/AI/aiWolfLinkAmiibo.h"
#include "Game/Actor/actWolfLink.h"
#include "Game/UI/uiUtils.h"

namespace uking::ai {

WolfLinkAmiibo::WolfLinkAmiibo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkAmiibo::~WolfLinkAmiibo() = default;

bool WolfLinkAmiibo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkAmiibo::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c = false;
    if (cannotUseWolfLinkAmiibo()) {
        ui::showInfoOverlay(26);
        setFailed();
        return;
    }
    sub_7100600A6C();
}

void WolfLinkAmiibo::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkAmiibo::loadParams_() {
    getStaticParam(&mAreaSearchCharacterRadius_s, "AreaSearchCharacterRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mAreaSearchRadius_s, "AreaSearchRadius");
}

}  // namespace uking::ai
