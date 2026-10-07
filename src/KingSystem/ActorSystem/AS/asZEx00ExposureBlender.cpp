#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::as {

ZEx00ExposureBlender::ZEx00ExposureBlender(const CreateArg&, s32, const res::ASResource*) {}

f32 ZEx00ExposureBlender::m38(Context* ctx, const res::ASResource* resource) {
    auto* manager = world::Manager::instance();
    if (!manager)
        return 0;
    return manager->getEnvMgr()->getExposure();
}

}  // namespace ksys::as
