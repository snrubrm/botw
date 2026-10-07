#include "Game/Actor/actObjBoardWoodTriangleUserTag.h"

namespace uking::act {

ObjBoardWoodTriangleUserTag::ObjBoardWoodTriangleUserTag(ksys::act::Actor* actor)
    : PhysicsUserTag(actor), mLastCollision{sead::Vector3f::zero, 0, 0, 0, 1,
                                          sead::Vector3f::zero, nullptr, sead::Vector3f::ey,
                                          0.0f, sead::Vector3f::zero, 0.0f} {}

ObjBoardWoodTriangleUserTag::~ObjBoardWoodTriangleUserTag() = default;

void ObjBoardWoodTriangleUserTag::m5(Unk5* arg) {
    PhysicsUserTag::m5(arg);
    mLastCollision = *arg;
}

}  // namespace uking::act
