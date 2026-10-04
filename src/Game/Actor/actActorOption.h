#pragma once

#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class ActorBind;
}

namespace uking::act {

// Name from the CSV (ActorOption::*; the namespace is a guess). Direct child of DynamicActor. Factory 0x71000001b4:
// new(0xbb0) + inlined ctor (`_1c0 = 1`). RTTI static: see data_symbols.
// TODO: incomplete (prepareInit_ = m18 and preDelete2_ = m20 not written: they create / destroy `_ba0` and `_ba8`).
class ActorOption : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(ActorOption, DynamicActor)
public:
    explicit ActorOption(const CreateArg& arg);
    ~ActorOption() override = default;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    bool shouldUnload(s32* a1) override;
    Actor* m31() override;
    Actor* m48() override;

    /* 0xb90 */ ksys::act::BaseProcLink _b90;
    /* 0xba0 */ ksys::act::BaseProcLink* _ba0 = nullptr;  // heap object (0x60 bytes)
    /* 0xba8 */ ksys::act::ActorBind* _ba8 = nullptr;     // a ModelBindInfo (heap)
};
KSYS_CHECK_SIZE_NX150(ActorOption, 0xbb0);

}  // namespace uking::act
