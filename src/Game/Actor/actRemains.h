#pragma once

#include <basis/seadTypes.h>
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/Utils/Types.h"

class Unk_71024f15c0;

namespace uking::act {

// Name from the CSV (Remains::construct 0x71002ca1dc = new(0xbc0) + inlined ctor; Remains::m*).
// RTTI static 0x71025b3278, parent DynamicActor; vtable 0x71023ceee8 =
// DynamicActor's 163 slots (no new virtuals).
// Members are public: AI code reads them.
class Remains : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(Remains, ksys::act::DynamicActor)
public:
    explicit Remains(const CreateArg& arg);
    ~Remains() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    void m63() override;
    void initMaybe() override;
    void updateLodStuff(ksys::act::Actor* other) override;
    void calcMaybe() override;
    void updatePositionMaybe() override;
    Unk_7100d3cd74* m101() override;

    // 0x71002ca3ec (called from calcMaybe while _bb8 is set): moves the actor to a matrix taken
    // from its ASList (translation snapped from the map object / home position).
    void sub_71002CA3EC();

    /* 0xb90 */ Unk_71024f15c0* _b90 = nullptr;  // rail follower, created in prepareInit_
    /* 0xb98 */ Unk_7100d3cd74 _b98{this};       // m101
    /* 0xbb8 */ bool _bb8 = false;
    /* 0xbb9 */ bool _bb9 = true;
};
KSYS_CHECK_SIZE_NX150(Remains, 0xbc0);

}  // namespace uking::act
