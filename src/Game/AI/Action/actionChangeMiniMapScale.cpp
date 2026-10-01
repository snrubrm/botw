#include "Game/AI/Action/actionChangeMiniMapScale.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

ChangeMiniMapScale::ChangeMiniMapScale(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeMiniMapScale::~ChangeMiniMapScale() = default;

bool ChangeMiniMapScale::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ChangeMiniMapScale::oneShot_() {
    if (mScaleLevel_d)
        ksys::gdt::setFlag_App_Map_ForceSetScaleLevelWhenMiniMap(*mScaleLevel_d);
    return true;
}

void ChangeMiniMapScale::loadParams_() {
    getDynamicParam(&mScaleLevel_d, "ScaleLevel");
}

}  // namespace uking::action
