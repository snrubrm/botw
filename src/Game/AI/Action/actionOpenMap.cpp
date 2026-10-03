#include "Game/AI/Action/actionOpenMap.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

OpenMap::OpenMap(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenMap::~OpenMap() = default;

bool OpenMap::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool OpenMap::oneShot_() {
    ui::sub_7100A9A21C(mWorldPos_d, *mScaleLevel_d);
    return ksys::act::ai::Action::oneShot_();
}

void OpenMap::loadParams_() {
    getDynamicParam(&mScaleLevel_d, "ScaleLevel");
    getDynamicParam(&mWorldPos_d, "WorldPos");
}

}  // namespace uking::action
