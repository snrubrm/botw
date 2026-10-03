#include "Game/AI/Action/actionDownloadRemainsMap.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

DownloadRemainsMap::DownloadRemainsMap(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DownloadRemainsMap::~DownloadRemainsMap() = default;

bool DownloadRemainsMap::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DownloadRemainsMap::enter_(ksys::act::ai::InlineParamPack* params) {
    ui::sub_7100A9F46C(*mIsPlayerClose_d);
}

void DownloadRemainsMap::leave_() {
    ksys::act::ai::Action::leave_();
}

void DownloadRemainsMap::loadParams_() {
    getDynamicParam(&mIsPlayerClose_d, "IsPlayerClose");
}

void DownloadRemainsMap::calc_() {
    if (ui::sub_7100A9F4AC())
        setFinished();
}

}  // namespace uking::action
