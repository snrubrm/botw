#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Name from the CSV (NoCalcActor::*; the namespace is a guess). Factory 0x7100e19384: new(0x840) + inlined ctor
// (sets _1c0 = 3). RTTI static 0x71026021d8. An actor that is only calculated while its map object asks for it
// (Object flag 0x20000): the job push checks are skipped otherwise.
class NoCalcActor : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(NoCalcActor, ksys::act::Actor)
public:
    explicit NoCalcActor(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    bool shouldSkipJobPush_(ksys::act::JobType type) override;
    void onJobPush2_(ksys::act::JobType type) override;
};
KSYS_CHECK_SIZE_NX150(NoCalcActor, 0x840);

}  // namespace uking::act
