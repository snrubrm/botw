#pragma once

#include "Game/AI/AI/aiTargetBeatCheck.h"
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class TargetBeatGetDrop : public TargetBeatCheck {
    SEAD_RTTI_OVERRIDE(TargetBeatGetDrop, TargetBeatCheck)
public:
    explicit TargetBeatGetDrop(const InitArg& arg);
    ~TargetBeatGetDrop() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool sub_71005BCCE0();
    void sub_71005BCF48();

    // static_param at offset 0x38
    const float* mSearchDist_s{};
    ksys::act::BaseProcLink _40;
    ksys::act::BaseProcLink _50;
    sead::Vector3f _60;
    bool _6c = false;
};
KSYS_CHECK_SIZE_NX150(TargetBeatGetDrop, 0x70);

}  // namespace uking::ai
