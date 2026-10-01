#pragma once

#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {

// TODO
class RopeBase : public Actor {
    SEAD_RTTI_OVERRIDE(RopeBase, Actor)
public:
    ~RopeBase() override;

    bool shouldUnload() override;
    int getExtraHeapSize() override;

    // FIXME: figure out return types, parameters and names
    virtual void m148();
    virtual void m149();
    virtual void m150();

protected:
    // TODO
    u8 _840[0x8c0 - 0x840];
    BaseProcLink _8c0[2];
    u8 _8e0[0x95a - 0x8e0];
    bool _95a;
    u8 _95b[0x9d0 - 0x95b];
    BaseProcHandle _9d0;
    u8 _9e0[0xa00 - 0x9e0];
};

}  // namespace ksys::act
