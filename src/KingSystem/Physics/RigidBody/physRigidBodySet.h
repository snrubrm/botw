#pragma once

#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <prim/seadNamable.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class RigidBody;
class RigidBodySetParamAccessor;
class SystemGroupHandler;
class UserTag;
class RigidBodyResource;

enum class Fixed : bool;
enum class MarkLinearVelAsDirty : bool;
enum class PreserveVelocities : bool;

class RigidBodySet : public sead::hostio::Node {
public:
    explicit RigidBodySet(const sead::SafeString& name);
    virtual ~RigidBodySet();

    const sead::SafeString& getName() const { return mName; }

    sead::PtrArray<RigidBody>& getRigidBodies() { return mRigidBodies; }
    const sead::PtrArray<RigidBody>& getRigidBodies() const { return mRigidBodies; }
    RigidBody* getRigidBody(int idx) const { return mRigidBodies[idx]; }

    void setFixedAndPreserveImpulse(Fixed fixed, MarkLinearVelAsDirty mark_linear_vel_as_dirty);
    void resetFrozenState();
    void setUseSystemTimeFactor(bool use);
    void clearFlag400000(bool clear);
    void setEntityMotionFlag200(bool set);
    void setFixed(Fixed fixed, PreserveVelocities preserve_velocities);

    void updateMotionTypeRelatedFlags();
    void triggerScheduledMotionTypeChange();

    bool hasActiveEntityBody() const;

    RigidBody* findBodyByHavokName(const sead::SafeString& name);
    // Returns a mutable pointer: Actor::findPhysicsBodyByName (const) calls this overload and returns
    // RigidBody*.
    RigidBody* findBodyByHavokName(const sead::SafeString& name) const;
    int findBodyIndexByHavokName(const sead::SafeString& name) const;

    void setUserTag(UserTag* tag);

    /// Set the specified handler for all rigid bodies whose type (entity/sensor) matches
    /// the layer type of the handler.
    void setSystemGroupHandler(SystemGroupHandler* handler);

    /// Set the specified handler for all rigid bodies whose type (entity/sensor) matches
    /// both `layer_type` and the layer type of the handler.
    void setSystemGroupHandler(SystemGroupHandler* handler, ContactLayerType layer_type);

    void setTransform(const sead::Matrix34f& mtx);

    void enableContactLayer(ContactLayer layer);
    void disableContactLayer(ContactLayer layer);
    void disableAllContactLayers();

    void setScaleAndUpdateImmediately(float scale);
    void setScale(float scale);
    void addToWorld();
    void removeFromWorld();
    bool removeFromWorldAndResetLinks();
    bool hasNoRigidBodyWithFlag8(bool require_motion_flag_1_to_be_unset);
    void callRigidBody_x_7(u8 type);

private:
    sead::SafeString mName;
    sead::PtrArray<RigidBody> mRigidBodies;
};

// 0x71012b034c: no members beyond the base (created with operator new(0x28) by
// ActorPhysics::initRigidBodies).
class RigidBodySet1 : public RigidBodySet {
public:
    explicit RigidBodySet1(const sead::SafeString& name);
    ~RigidBodySet1() override;

    // Placeholder name (0x71012b047c): fill the set with the bodies the accessor creates
    // (false if any creation fails, deleting the bodies created so far).
    bool sub_71012B047C(RigidBodySetParamAccessor* accessor, sead::Heap* heap);
};

// 0x71012afe48: created with operator new(0x40) by ActorPhysics::initRigidBodies, which passes
// a RigidBodyResource (the result of loadFromRomOrActorPack<RigidBodyResource>).
class RigidBodySet2 : public RigidBodySet {
public:
    RigidBodySet2(const sead::SafeString& name, RigidBodyResource* resource);
    ~RigidBodySet2() override;

    RigidBodyResource* _28;
    void* _30;
    u32 _38;

private:
    // Placeholder name (0x71012afeb8): delete every body, free the body array, then unload
    // and free the copied resource data.
    void sub_71012AFEB8();
};
static_assert(sizeof(RigidBodySet2) == 0x40);

}  // namespace ksys::phys
