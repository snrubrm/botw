#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/Event/evtManager.h"

namespace ksys::evt {

bool sub_7100DC866C() {
    if (auto* manager = Manager::instance())
        return manager->hasActiveEvent();
    return false;
}

bool sub_7100DC8684(const sead::SafeString& event_name, const sead::SafeString& entry_point) {
    if (auto* manager = Manager::instance())
        return manager->isActiveEventNameEqualTo(event_name, entry_point);
    return false;
}

}  // namespace ksys::evt
