#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Name from the CSV (MapConst::ctor 0x7100e8dde4, MapConst::m*; the namespace is a guess). A map object
// actor (RTTI static 0x71025b7208, vtable 0x71024ec790 (GOT value), size 0x850) that keeps its physics
// at the placement transform. The factory is not identified yet. MapConst::m71 (0x7100e8e010) calls the
// unnamed matrix comparison 0x7100700428 and is not written yet.
class MapConst : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(MapConst, ksys::act::Actor)
public:
    explicit MapConst(const CreateArg& arg);
    ~MapConst() override;

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;

public:
    void m63() override;

    /* 0x83c */ s32 _83c = 0;
    /* 0x840 */ f32 _840 = 0;  // traverse distance of the actor
    /* 0x844 */ bool _844 = true;
    /* 0x845 */ bool _845 = false;
    /* 0x846 */ bool _846 = false;
    /* 0x847 */ u8 _847;
    /* 0x848 */ bool _848 = false;
    /* 0x84c */ u32 _84c = 0;
};
KSYS_CHECK_SIZE_NX150(MapConst, 0x850);

}  // namespace uking::act
