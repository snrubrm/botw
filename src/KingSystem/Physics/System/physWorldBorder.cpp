#include "KingSystem/Physics/System/physWorldBorder.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

WorldBorder::WorldBorder(ContactLayerType layer, hkpWorld* world)
    : hkpBroadPhaseBorder(world), mLayer(layer) {}

void WorldBorder::maxPositionExceededCallback(hkpEntity* entity) {
    auto* body = getRigidBody(*entity);
    if (!body)
        return;

    switch (body->getType()) {
    case RigidBody::Type::TerrainHeightField:
    case RigidBody::Type::StaticCompoundBody:
    case RigidBody::Type::TeraMesh:
        return;
    default:
        System::instance()->getRigidBodyRequestMgr()->onMaxPositionExceeded(mLayer, body);
        break;
    }
}

}  // namespace ksys::phys
