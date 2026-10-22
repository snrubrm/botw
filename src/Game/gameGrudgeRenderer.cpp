#include "Game/gameGraphics.h"
#include <gsys/gsysModel.h>
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

// 0x710128f4bc
// NON_MATCHING: the original loads the 20.0f reset distance from a file-scope object at 0x7102519120;
// clang folds our literal to an immediate.
void GrudgeRenderer::sub_710128F4BC(const sead::Camera* camera) {
    if ((_2ef8 & 1) == 0)
        return;
    camera->getWorldPosByMatrix(&_240);
    _264 = 20.0f;
    _268->requestDraw();
}
