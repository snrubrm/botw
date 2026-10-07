#pragma once

#include "KingSystem/ActorSystem/actPhysicsUserTag.h"

namespace uking::act {

// 2026-10-07: ctor0x710071f098, vtable0x7102451090, direct PhysicsUserTag subclass.
class ObjBoardWoodTriangleUserTag : public ksys::act::PhysicsUserTag {
    SEAD_RTTI_OVERRIDE(ObjBoardWoodTriangleUserTag, ksys::act::PhysicsUserTag)
public:
    explicit ObjBoardWoodTriangleUserTag(ksys::act::Actor* actor);
    ~ObjBoardWoodTriangleUserTag() override;
    void m5(Unk5* arg) override;

    /* 0x18 */ Unk5 mLastCollision;
};
KSYS_CHECK_SIZE_NX150(ObjBoardWoodTriangleUserTag, 0x60);

}  // namespace uking::act
