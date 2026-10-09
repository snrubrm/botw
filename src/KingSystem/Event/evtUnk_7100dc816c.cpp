#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"

namespace ksys::evt {

// 0x7100dc85d4
act::BaseProcLink& sub_7100DC85D4(act::Actor* actor) {
    if (actor) {
        if (auto* manager = Manager::instance()) {
            if (auto* link = manager->getBaseProcLinkForActorOrActiveLink(actor)) {
                if (link->hasProc())
                    return *link;
            }
        }
    }
    return act::getDummyBaseProcLink();
}

// 0x7100dc8630
act::BaseProcLink& sub_7100DC8630(const sead::SafeString& name,
                                const sead::SafeString& secondary_name) {
    if (auto* manager = Manager::instance()) {
        if (auto* link = manager->getBaseProcLinkFromActiveEvent(name, secondary_name))
            return *link;
    }
    return act::getDummyBaseProcLink();
}

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
