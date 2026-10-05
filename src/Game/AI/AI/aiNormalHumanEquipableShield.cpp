#include "Game/AI/AI/aiNormalHumanEquipableShield.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

NormalHumanEquipableShield::NormalHumanEquipableShield(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

NormalHumanEquipableShield::~NormalHumanEquipableShield() = default;

bool NormalHumanEquipableShield::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NormalHumanEquipableShield::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (sub_71005D8B60(actor) || sub_71005DB96C(actor) >= 0 ||
        sub_71005DBB60(actor, *mWeaponIdx_s) != 0)
        changeChild("盾装備不能", params);
    else
        changeChild("盾装備可能", params);
}

void NormalHumanEquipableShield::calc_() {
    if (!getCurrentChild()->isChangeable())
        return;
    auto* actor = mActor;
    if (sub_71005D8B60(actor) || sub_71005DB96C(actor) >= 0 ||
        sub_71005DBB60(actor, *mWeaponIdx_s) != 0) {
        if (!isCurrentChild("盾装備不能"))
            changeChild("盾装備不能");
    } else if (!isCurrentChild("盾装備可能")) {
        changeChild("盾装備可能");
    }
}

void NormalHumanEquipableShield::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NormalHumanEquipableShield::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
