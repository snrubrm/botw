#include "Game/gameGraphics.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

// GrudgeRenderer's TU (0x710128d348 .. 0x71012915b8). Only this helper is decompiled so far.

bool sub_7101290034(const sead::Vector3f& start, const sead::Vector3f& displacement, sead::Vector3f* hit_pos) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.setGroundHit(ksys::phys::GroundHit::Grudge);
    query.setStartAndDisplacement(start, displacement);
    bool hit = false;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(hit_pos);
        hit = true;
    }
    return hit;
}
