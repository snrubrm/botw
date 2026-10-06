#include "Game/AI/AI/aiRemainsWindBatteryRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

RemainsWindBatteryRoot::RemainsWindBatteryRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsWindBatteryRoot::~RemainsWindBatteryRoot() = default;

bool RemainsWindBatteryRoot::init_(sead::Heap* heap) {
    auto* actor = mActor;
    if (actor->getModel()) {
        _48.search(actor->getModel(), "Head");
        _80.search(actor->getModel(), "Neck");
    }
    return true;
}

void RemainsWindBatteryRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        if (actor->getConstraints().size() == 0)
            body->changeMotionType(ksys::phys::MotionType::Fixed);
    }
    if (auto* awareness = actor->getAwareness())
        awareness->enable();
    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, "MaterialDefault", 0, 1, true);
    changeChild("待機");
    _38 = 3;
    _40 = false;
    _3c = 0;
}

void RemainsWindBatteryRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWindBatteryRoot::loadParams_() {}

// NON_MATCHING: the original branches on `damage_state > 0` and then on the x_4 result; ours folds the two into
// one cset + tbz
// 0x710054ea4c
void RemainsWindBatteryRoot::sub_710054EA4C(s32 damage_state) {
    auto* as_list = mActor->getASList();
    if (damage_state > 0)
        as_list->startAnimationMaybe(-1.0f, -1.0f, "MaterialDamage", 0, 1, true);
    if (as_list->x_1(0, 1) == "MaterialDamage") {
        const bool finished = as_list->x_4(0, 1);
        if (damage_state > 0)
            return;
        if (!finished)
            return;
    } else if (damage_state > 0) {
        return;
    }
    sub_710054EB78();
}

}  // namespace uking::ai
