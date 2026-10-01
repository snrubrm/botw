#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::phys {
class RigidBody;
}  // namespace ksys::phys

namespace ksys::act {

// TODO
class RopeBase : public Actor {
    SEAD_RTTI_OVERRIDE(RopeBase, Actor)
public:
    ~RopeBase() override;

    void m43(bool on) override;
    bool shouldUnload() override;
    void updatePositionMaybe() override;
    int getExtraHeapSize() override;

    // FIXME: figure out return types, parameters and names
    virtual void m148();
    virtual void m149();
    virtual void m150();

protected:
    // TODO
    u8 _840[0x860 - 0x840];
    sead::Buffer<phys::RigidBody*> _860;
    u8 _870[0x880 - 0x870];
    sead::Buffer<phys::RigidBody*> _880;
    u8 _890[0x8c0 - 0x890];
    BaseProcLink _8c0[2];
    u8 _8e0[0x92c - 0x8e0];
    s32 _92c;
    u8 _930[0x95a - 0x930];
    bool _95a;
    u8 _95b[0x9d0 - 0x95b];
    BaseProcHandle _9d0;
    u8 _9e0[0xa00 - 0x9e0];
};

}  // namespace ksys::act
