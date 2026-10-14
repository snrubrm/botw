#include "Game/Actor/AI/aiVehicleSelector.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::ai {

VehicleSelector::VehicleSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

VehicleSelector::~VehicleSelector() = default;

void VehicleSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* proc = uking::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr);
    if (auto* vehicle = sead::DynamicCast<ksys::act::Actor>(proc)) {
        ksys::act::ActorLinkConstDataAccess accessor(vehicle);
        if (ksys::act::hasTag(vehicle, ksys::act::tags::IsVehicle)) {
            changeChild("乗り物である", params);
            return;
        }
    }
    changeChild("乗り物ではない", params);
}

}  // namespace uking::ai
