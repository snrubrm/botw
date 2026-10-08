#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Container/Array/hkArray.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpEntityListener.h>
#include <Havok/Physics2012/Dynamics/World/Listener/hkpWorldPostSimulationListener.h>

class hkpCharacterRigidBodyCinfo;
class hkpCharacterRigidBodyListener;
class hkpRigidBody;
struct hkpSurfaceInfo;

// Native ctor 0x710167853c and vtable 0x7102542fb8 establish the listener
// bases at +0x10/+0x18. Native D0 0x7101678858 frees 0x90 bytes; the derived
// game character reuses the native tail padding at +0x88 for its own fields.
class hkpCharacterRigidBody : public hkReferencedObject,
                              public hkpEntityListener,
                              public hkpWorldPostSimulationListener {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCharacterRigidBody)

    explicit hkpCharacterRigidBody(const hkpCharacterRigidBodyCinfo& info);
    ~hkpCharacterRigidBody() override;

    struct SupportInfo;
    virtual void checkSupport(const hkStepInfo& step, hkpSurfaceInfo& surface);
    virtual void getSupportInfo(const hkStepInfo& step, hkArray<SupportInfo>& support);
    virtual void getGround(const hkArray<SupportInfo>& support, hkBool use_dynamic,
                           hkpSurfaceInfo& surface);
    void entityAddedCallback(hkpEntity* entity) override;
    void entityRemovedCallback(hkpEntity* entity) override;
    void postSimulationCallback(hkpWorld* world) override;

    // Native 0x7101679858 / 0x7101679860.
    hkpRigidBody* getRigidBody() const;
    void setLinearVelocity(const hkVector4f& velocity);

    static const int m_magicNumber = 0x008df4a7;
    static const int m_notMagicNumber = 0x00fa2bb3;

    hkpRigidBody* m_character;                    // +0x20
    hkpCharacterRigidBodyListener* m_listener;   // +0x28
    hkVector4f m_up;                             // +0x30
    hkReal _40;
    hkReal _44;  // cosine of the maximum slope (ctor calls cos on cinfo+0x60)
    hkReal _48;
    hkReal _4c;
    hkReal _50;
    hkUint8 _54[0xc];
    hkVector4f m_velocity;                       // +0x60
    hkReal _70;
    hkUint8 _74[4];
    // The destructor owns an array here with 0x30-byte elements; its element
    // type and lifetime remain unknown. Do not synthesize its destructor.
    hkUint8 _78[0x10];
};
static_assert(sizeof(hkpCharacterRigidBody) == 0x90);
static_assert(offsetof(hkpCharacterRigidBody, m_character) == 0x20);
static_assert(offsetof(hkpCharacterRigidBody, m_up) == 0x30);
static_assert(offsetof(hkpCharacterRigidBody, m_velocity) == 0x60);
static_assert(offsetof(hkpCharacterRigidBody, _78) == 0x78);
