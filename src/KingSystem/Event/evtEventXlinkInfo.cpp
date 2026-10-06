#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace ksys::evt {

// 0x7100dc96a0
void EventXlinkInfo::x_1(EventFlowBase* flow) {
    if (auto* actor = sead::DynamicCast<act::Actor>(_18.getProc(nullptr))) {
        if (_8.isAllocatedOrFailed())
            _8.releaseAndWakeProc();
        else
            actor->wakeUp(act::BaseProc::SleepWakeReason::_0);
        actor->x_15(flow, nullptr);
    }
}

// 0x7100dc9780
void EventXlinkInfo::x_0() {
    if (auto* actor = sead::DynamicCast<act::Actor>(_18.getProc(nullptr))) {
        actor->sleep(act::BaseProc::SleepWakeReason::_0);
        actor->sub_71011C98F8();
    }
}

}  // namespace ksys::evt
