#include "Game/AI/Behavior/behaviorAirWallMaterialSpecify.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/Physics/physMaterialMask.h"

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

void AirWallMaterialSpecify::sub_7100616964(ksys::phys::RigidBody* body) {
    if (auto* wall = sead::DynamicCast<ksys::act::AirWall>(mActor)) {
        ksys::phys::MaterialMask mask(ksys::phys::Material::Barrier, "DungeonAirWall",
                                      ksys::phys::FloorCode::None,
                                      ksys::phys::WallCode::NoDashUpAndNoClimb, false);
        wall->sub_7100E26784(&mask);
    }
}

}  // namespace uking::behavior
