#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::phys {

class InstanceSet;
class RigidBody;
class RigidBodySetParam;
struct RigidBodyInstanceParam;

// Placeholder name (the binary has no RTTI name string for it; its vtable at 0x71024f89b0
// has a null typeinfo slot): the small accessor ActorPhysics::initRigidBodies builds on its
// stack ({vtable, InstanceSet*, RigidBodySetParam*}) and passes to the RigidBodySet1/2 init
// functions. Its four virtuals are called by those functions: m0 (body count), m1 (create the
// idx-th body), m2 (fill a RigidBodyInstanceParam for the idx-th body), m3 (float parameter
// of the idx-th body, 1.0 if out of range).
class RigidBodySetParamAccessor {
public:
    virtual int m0();
    virtual RigidBody* m1(s32 idx, sead::Heap* heap);
    virtual void m2(s32 idx, RigidBodyInstanceParam* param);
    virtual float m3(s32 idx);

private:
    InstanceSet* _8 = nullptr;
    RigidBodySetParam* _10 = nullptr;
};
KSYS_CHECK_SIZE_NX150(RigidBodySetParamAccessor, 0x18);

}  // namespace ksys::phys
