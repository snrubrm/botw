#include "Game/AI/AI/aiEquipHaveSelector.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EquipHaveSelector::EquipHaveSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EquipHaveSelector::~EquipHaveSelector() = default;

bool EquipHaveSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EquipHaveSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    if (m34())
        changeChild("非所持", params);
    else
        changeChild("所持", params);
}

void EquipHaveSelector::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (m34()) {
            if (!isCurrentChild("非所持")) {
                changeChild("非所持");
                return;
            }
        } else if (!isCurrentChild("所持")) {
            changeChild("所持");
            return;
        }

        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (child->isChangeable()) {
        if (m34()) {
            if (!isCurrentChild("非所持"))
                changeChild("非所持");
        } else if (!isCurrentChild("所持")) {
            changeChild("所持");
        }
    }
}

bool EquipHaveSelector::m34() {
    return sub_71005DBB60(mActor, *mWeaponIdx_s) == -1;
}

bool EquipHaveSelector::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EquipHaveSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EquipHaveSelector::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
