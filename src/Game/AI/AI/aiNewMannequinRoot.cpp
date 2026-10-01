#include "Game/AI/AI/aiNewMannequinRoot.h"

namespace uking::ai {

NewMannequinRoot::NewMannequinRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NewMannequinRoot::~NewMannequinRoot() = default;

bool NewMannequinRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NewMannequinRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NewMannequinRoot::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return;
    child->isChangeable();
}

void NewMannequinRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NewMannequinRoot::loadParams_() {
    getMapUnitParam(&mArmorDyeColor_m, "ArmorDyeColor");
    getMapUnitParam(&mShopSellType_m, "ShopSellType");
}

}  // namespace uking::ai
