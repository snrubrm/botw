#pragma once

#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class CollisionInfo;
class ContactPointInfo;
class MaterialMask;
class RigidBody;
}  // namespace ksys::phys

namespace ksys::act {

// Names from the CSV (AreaActor::ctor 0x7100e252b8, AirWall::construct 0x7100e2452c: new(0x8a0), Area::construct
// 0x7100e24c34: new(0x898), SweepCollision::construct 0x7100e29070: new(0x890)). AirWall's RTTI static is at
// 0x71025afe68. The namespace is a guess. Base of the "area" actors that own a collision body: the body
// (_840), its collision info (_848) and contact point info (_850) are created by initPhysics (0x7100e2552c).
// Six new virtuals (slots 148-153; the ctor stores the secondary vtables at +0x4f0 / +0x518).
// TODO: incomplete (initPhysics / shouldInit_ / prepareInit_ / getShape and the other overrides are not written).
class AreaActor : public Actor {
    SEAD_RTTI_OVERRIDE(AreaActor, Actor)
public:
    explicit AreaActor(const CreateArg& arg);
    ~AreaActor() override = default;

    void preDelete2_(const PreDeleteArg& arg) override;
    int getCalcTiming() override { return 0; }

    /* 148 */ virtual void m148() {}
    // Binds the collision / contact point info to the body.
    /* 149 */ virtual void m149(phys::RigidBody* body);
    // Calls the member function `_878` with a default (0) MaterialMask.
    /* 150 */ virtual void m150();
    /* 151 */ virtual void m151() {}
    // The contact layer of the body.
    /* 152 */ virtual phys::ContactLayer m152();
    /* 153 */ virtual void* m153() { return nullptr; }

    // 0x7100e2677c: `_88a = 0`.
    void sub_7100E2677C();
    bool sub_7100E26A80();
    void sub_7100E26A28(bool enable);

    /* 0x840 */ phys::RigidBody* _840 = nullptr;
    /* 0x848 */ phys::CollisionInfo* _848 = nullptr;
    /* 0x850 */ phys::ContactPointInfo* _850 = nullptr;
    /* 0x858 */ BaseProcLink _858;
    /* 0x868 */ sead::Vector3f _868 = sead::Vector3f::ones;
    /* 0x878 */ void (AreaActor::*_878)(phys::MaterialMask*) = nullptr;
    /* 0x888 */ u8 _888 = 5;
    /* 0x889 */ u8 _889 = 4;
    /* 0x88a */ u8 _88a = 2;
    /* 0x88b */ u8 _88b = 0;
    /* 0x88c */ u8 _88c = 0;
    /* 0x88d */ u8 _88d = 0;
};
KSYS_CHECK_SIZE_NX150(AreaActor, 0x890);

class AirWall : public AreaActor {
    SEAD_RTTI_OVERRIDE(AirWall, AreaActor)
public:
    using RigidBodyCallback = sead::IDelegate1<phys::RigidBody*>;

    explicit AirWall(const CreateArg& arg);
    static BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    // 0x7100e245b8 / 0x7100e245c0: set _890 / _898 and update the rigid bodies (sub_7100E2677C).
    void sub_7100E245B8(RigidBodyCallback* callback);
    void sub_7100E245C0(RigidBodyCallback* callback);

    void preDelete2_(const PreDeleteArg& arg) override;
    void m149(phys::RigidBody* body) override;
    void m151() override;
    phys::ContactLayer m152() override;

    /* 0x890 */ RigidBodyCallback* _890 = nullptr;
    /* 0x898 */ RigidBodyCallback* _898 = nullptr;
};
KSYS_CHECK_SIZE_NX150(AirWall, 0x8a0);

// Name from the CSV (Area::*; Area::construct 0x7100e24c34).
class Area : public AreaActor {
    SEAD_RTTI_OVERRIDE(Area, AreaActor)
public:
    explicit Area(const CreateArg& arg);
    static BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    void m149(phys::RigidBody* body) override;
    void m151() override;
    phys::ContactLayer m152() override;

    /* 0x890 */ phys::SensorCollisionMask _890{phys::SensorCollisionMask::CustomReceiverTag{}};
};
KSYS_CHECK_SIZE_NX150(Area, 0x898);

// Name from the CSV (SweepCollision::*; SweepCollision::construct 0x7100e29070).
class SweepCollision : public AreaActor {
    SEAD_RTTI_OVERRIDE(SweepCollision, AreaActor)
public:
    explicit SweepCollision(const CreateArg& arg);
    static BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    void m151() override;
    phys::ContactLayer m152() override;
};
KSYS_CHECK_SIZE_NX150(SweepCollision, 0x890);

}  // namespace ksys::act
