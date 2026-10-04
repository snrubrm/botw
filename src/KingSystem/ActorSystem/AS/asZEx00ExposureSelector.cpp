#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::as {

ZEx00ExposureSelector::ZEx00ExposureSelector() {}

f32 ZEx00ExposureSelector::m40(Context* ctx, u32 a2, const res::ASResource* resource) {
    auto* manager = world::Manager::instance();
    if (!manager)
        return 0;
    return manager->getEnvMgr()->getExposure();
}

}  // namespace ksys::as
