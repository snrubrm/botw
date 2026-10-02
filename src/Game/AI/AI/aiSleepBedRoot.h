#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"

namespace uking::ai {

// vtable 0x7102423268 (D0 0x710059a838 in this TU; m2/m3 are Unk_7102450648's)
class Unk_7102423268 : public Unk_7102450648 {
public:
    explicit Unk_7102423268(u32 type) : Unk_7102450648(type) {}
};

class SleepBedRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SleepBedRoot, ksys::act::ai::Ai)
public:
    explicit SleepBedRoot(const InitArg& arg);
    ~SleepBedRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    Unk_7102423268 _38{0x180000b};
    ksys::evt::BaseProcLinkForEvent _78;
};
KSYS_CHECK_SIZE_NX150(SleepBedRoot, 0x238);

}  // namespace uking::ai
