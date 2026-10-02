#include "Game/AI/Behavior/behaviorAirWallCollisionSpecify.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"

namespace uking::behavior {

AirWallCollisionSpecify::AirWallCollisionSpecify(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

void AirWallCollisionSpecify::m7() {
    if (_48 == *mAirWallCollision_m)
        return;
    bool set = true;
    switch (*mAirWallCollision_m) {
    case 1:
        _28.setFunction(&AirWallCollisionSpecify::sub_71006163B4);
        break;
    case 2:
        _28.setFunction(&AirWallCollisionSpecify::sub_7100616700);
        break;
    default:
        set = false;
        break;
    }
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* wall = sead::DynamicCast<ksys::act::AirWall>(actor)) {
        wall->sub_7100E245B8(set ? &_28 : nullptr);
        _48 = *mAirWallCollision_m;
    }
}

void AirWallCollisionSpecify::m8() {
    _48 = 3;
    if (_48 == *mAirWallCollision_m)
        return;
    bool set = true;
    switch (*mAirWallCollision_m) {
    case 1:
        _28.setFunction(&AirWallCollisionSpecify::sub_71006163B4);
        break;
    case 2:
        _28.setFunction(&AirWallCollisionSpecify::sub_7100616700);
        break;
    default:
        set = false;
        break;
    }
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* wall = sead::DynamicCast<ksys::act::AirWall>(actor)) {
        wall->sub_7100E245B8(set ? &_28 : nullptr);
        _48 = *mAirWallCollision_m;
    }
}

void AirWallCollisionSpecify::loadParams() {
    getMapUnitParam(&mAirWallCollision_m, "AirWallCollision");
}

}  // namespace uking::behavior
