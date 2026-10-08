#pragma once

class hkpEntity;

// The listener sub-vtable at 0x7102543020 has the destructor pair followed
// by these five callbacks, matching the entity listener protocol.
class hkpEntityListener {
public:
    virtual ~hkpEntityListener() = default;
    virtual void entityAddedCallback(hkpEntity* entity) = 0;
    virtual void entityRemovedCallback(hkpEntity* entity) = 0;
    virtual void entityShapeSetCallback(hkpEntity* entity);
    virtual void entityDeletedCallback(hkpEntity* entity);
    virtual void entityMotionTypeSetCallback(hkpEntity* entity);
};
