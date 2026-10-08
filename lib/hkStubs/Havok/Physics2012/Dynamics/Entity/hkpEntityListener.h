#pragma once

#include <Havok/Physics2012/Dynamics/Entity/hkpEntity.h>

// The listener sub-vtable at 0x7102543020 has the destructor pair followed
// by these five callbacks, matching the entity listener protocol.
class hkpEntityListener {
public:
    virtual ~hkpEntityListener() = default;
    virtual void entityAddedCallback(hkpEntity* entity) = 0;
    virtual void entityRemovedCallback(hkpEntity* entity) = 0;
    // Original 0x7100f69cd4 uses the entity's world+0x10 and invokes removal
    // then addition through listener slots 3 and 2. Emission beside the game's
    // derived listener is consistent with this native inline default.
    virtual void entityShapeSetCallback(hkpEntity* entity) {
        if (entity->getWorld()) {
            entityRemovedCallback(entity);
            entityAddedCallback(entity);
        }
    }
    virtual void entityDeletedCallback(hkpEntity* entity) {}  // 0x7100f69d2c
    virtual void entityMotionTypeSetCallback(hkpEntity* entity) {}  // 0x7100f69d30
};
