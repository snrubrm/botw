#include "Game/AI/AI/aiEquipConditionSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EquipConditionSelect::EquipConditionSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EquipConditionSelect::~EquipConditionSelect() = default;

bool EquipConditionSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EquipConditionSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71005DA5AC(mActor, *mWeaponIdx_s))
        changeChild("炎上", params);
    else
        changeChild("通常", params);
}

void EquipConditionSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("炎上"))
            changeChild("通常");
        else
            setFinished();
    } else if (child->isChangeable()) {
        if (sub_71005DA5AC(mActor, *mWeaponIdx_s)) {
            if (isCurrentChild("通常"))
                changeChild("炎上");
        } else if (isCurrentChild("炎上")) {
            changeChild("通常");
        }
    }
}

void EquipConditionSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EquipConditionSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
