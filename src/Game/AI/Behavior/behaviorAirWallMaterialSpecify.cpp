#include "Game/AI/Behavior/behaviorAirWallMaterialSpecify.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"

namespace uking::behavior {

AirWallMaterialSpecify::AirWallMaterialSpecify(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void AirWallMaterialSpecify::m8() {
    _48 = 3;
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* wall = sead::DynamicCast<ksys::act::AirWall>(actor))
        wall->sub_7100E245C0(&_28);
}

}  // namespace uking::behavior
