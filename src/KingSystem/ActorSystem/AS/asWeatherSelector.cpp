#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::as {

WeatherSelector::WeatherSelector(const CreateArg&, s32, const res::ASResource*) {}

const char* WeatherSelector::m40(Context* ctx, const res::ASResource* resource) {
    auto* manager = world::Manager::instance();
    if (!manager)
        return "";
    sead::Vector3f pos;
    ctx->sub_7101258ABC()->getMtx().getTranslation(pos);
    return world::Manager::getWeatherTypeString(manager->sub_71010F337C(pos));
}

}  // namespace ksys::as
