#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::as {

TimeSelector::TimeSelector() {}

const char* TimeSelector::m40(Context* ctx, const res::ASResource* resource) {
    auto* manager = world::Manager::instance();
    if (!manager)
        return "";
    return world::TimeDivision::text(manager->getTimeMgr()->getTimeDivision());
}

}  // namespace ksys::as
