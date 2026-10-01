#include "KingSystem/Event/evtManager.h"

namespace ksys::evt {

SEAD_SINGLETON_DISPOSER_IMPL(Manager)

bool Manager::hasActiveEvent() const {
    return _1d2b8 != nullptr;
}

}  // namespace ksys::evt
