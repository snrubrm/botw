#include "Game/AI/Action/actionNPCDyeShopCloseMaterial.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCDyeShopCloseMaterial::NPCDyeShopCloseMaterial(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCDyeShopCloseMaterial::~NPCDyeShopCloseMaterial() = default;

bool NPCDyeShopCloseMaterial::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool NPCDyeShopCloseMaterial::oneShot_() {
    if (ui::sub_7100A98558())
        ui::sub_7100A98598();
    return ksys::act::ai::Action::oneShot_();
}

void NPCDyeShopCloseMaterial::loadParams_() {}

}  // namespace uking::action
