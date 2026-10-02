#include "Game/AI/Action/actionDemoGetItemAnimStop.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DemoGetItemAnimStop::DemoGetItemAnimStop(const InitArg& arg) : DemoGetItem(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
DemoGetItemAnimStop::~DemoGetItemAnimStop() {
    ;
}

bool DemoGetItemAnimStop::init_(sead::Heap* heap) {
    return DemoGetItem::init_(heap);
}

void DemoGetItemAnimStop::loadParams_() {
    DemoGetItem::loadParams_();
    getStaticParam(&mWaitASKeyName_s, "WaitASKeyName");
}

bool DemoGetItemAnimStop::oneShot_() {
    if (!DemoGetItem::oneShot_())
        return false;
    auto* actor = mActor;
    playAS(mWaitASKeyName_s.cstr(), false, 0, 0, -1.0f);
    if (auto* as_list = actor->getASList())
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    return true;
}

}  // namespace uking::action
