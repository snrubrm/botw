#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactListener.h>
#include "KingSystem/Utils/Types.h"

class hkpCollidable;
class hkpContactPointEvent;
class hkpShape;

namespace sead {
class Heap;
}

namespace ksys::map {
class Object;
}

namespace ksys::phys {

class RigidBody;
class StaticCompoundRigidBodyGroup;
struct RigidBodyCollisionMasks;
enum class MotionType;

// Placeholder (vtable 0x71024f9570; object 0x18 bytes): a contact point listener attached to one rigid
// body of a character. The contact point callback rewrites the contact normal of steep faces so the
// body can climb them. `_10` gates the rewrite; the callback is still U.
class Unk_71024f9570 : public hkpContactListener {
public:
    explicit Unk_71024f9570(RigidBody* body) : mBody(body) {}
    // 0x7100fd0254 (placeholder name): flips the contact normal when the transformed face is steep.
    void contactPointCallback(const hkpContactPointEvent& event) override;
    // 0x7100fd01b4: attaches a new listener to `body`.
    static Unk_71024f9570* make(sead::Heap* heap, RigidBody* body);
    // 0x7100fd020c: detaches `listener` from its body and deletes it.
    static void destroy(Unk_71024f9570* listener);

    /* 0x08 */ RigidBody* mBody;
    /* 0x10 */ bool _10 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9570, 0x18);

// 0x7100fcfeb8 (placeholder name; a second copy of Unk_71024f9570::destroy that lives in the
// LayerContactPointInfo TU): detaches `listener` and deletes it.
void sub_7100FCFEB8(Unk_71024f9570* listener);

// 0x0000007100fd069c
MotionType motionTypeFromText(const sead::SafeString& text);

// 0x0000007100fd0810
u32 getMaterialMaskFromShape(const hkpShape& shape, const u32* shape_key,
                             const sead::Vector3f& position);

// 0x0000007100fd086c
bool getMaterialMaskFromCollidable(RigidBodyCollisionMasks* p_masks, u32* p_collision_filter_info,
                                   const hkpShape& shape, const u32* shape_key);

// 0x0000007100fd09d0
void getBodyGroupAndObjectFromSCShape(StaticCompoundRigidBodyGroup** p_body_group,
                                      map::Object** p_object, const hkpShape& shape,
                                      const u32* shape_key);

// 0x0000007100fd0a1c
u32 getCollisionFilterInfoFromCollidable(RigidBodyCollisionMasks* p_masks,
                                         u32* p_collision_filter_info,
                                         const hkpCollidable& collidable, const u32* shape_key);

}  // namespace ksys::phys
