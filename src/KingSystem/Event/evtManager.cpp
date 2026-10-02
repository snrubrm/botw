#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtEventMgrStruct1.h"

namespace ksys::evt {

SEAD_SINGLETON_DISPOSER_IMPL(Manager)

f32 Manager::sub_7100DB1138(int idx) const {
    if (idx == -99)
        return 0.0f;
    return _1d2d0->sub_7101273400(idx);
}

void Manager::sub_7100DB1158(int idx) {
    if (idx == -99)
        return;
    _1d2d0->sub_71012733D8(idx);
}

f32 Manager::sub_7100DB1174(int idx) const {
    return _1d2d0->sub_7101273448(idx);
}

bool Manager::sub_7100DB0CA0(const Metadata& metadata, act::Actor* actor) {
    return false;
}

bool Manager::hasActiveEvent() const {
    return _1d2b8 != nullptr;
}

}  // namespace ksys::evt
