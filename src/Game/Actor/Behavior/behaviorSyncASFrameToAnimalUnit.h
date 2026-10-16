#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SyncASFrameToAnimalUnit : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SyncASFrameToAnimalUnit, ksys::act::ai::Behavior)
public:
    explicit SyncASFrameToAnimalUnit(const InitArg& arg);
    ~SyncASFrameToAnimalUnit() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const int* mSeqBank_s{};
    /* 0x30 */ const int* mTargetBone_s{};
};
KSYS_CHECK_SIZE_NX150(SyncASFrameToAnimalUnit, 0x38);

}  // namespace uking::behavior
