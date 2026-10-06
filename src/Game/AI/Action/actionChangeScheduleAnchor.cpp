#include "Game/AI/Action/actionChangeScheduleAnchor.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/actNPCBase.h"

namespace uking::action {

ChangeScheduleAnchor::ChangeScheduleAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeScheduleAnchor::~ChangeScheduleAnchor() = default;

bool ChangeScheduleAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ChangeScheduleAnchor::oneShot_() {
    if (auto* npc = sead::DynamicCast<uking::act::NPC>(mActor)) {
        sead::FixedSafeString<32> anchor;
        anchor.copy(mScheduleName_d);
        anchor.appendWithFormat(":%s", mAnchorUniqueName_d.cstr());
        npc->_ac8.copy(anchor);
    }
    return true;
}

void ChangeScheduleAnchor::loadParams_() {
    getDynamicParam(&mScheduleName_d, "ScheduleName");
    getDynamicParam(&mAnchorUniqueName_d, "AnchorUniqueName");
}

}  // namespace uking::action
