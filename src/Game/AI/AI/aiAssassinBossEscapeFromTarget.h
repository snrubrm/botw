#pragma once

#include <math/seadVector.h>
#include "Game/AI/AI/aiSimpleEscapeFromTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossEscapeFromTarget : public SimpleEscapeFromTarget {
    SEAD_RTTI_OVERRIDE(AssassinBossEscapeFromTarget, SimpleEscapeFromTarget)
public:
    explicit AssassinBossEscapeFromTarget(const InitArg& arg);
    ~AssassinBossEscapeFromTarget() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100315244();

protected:
    // static_param at offset 0x68
    const float* mCheckDist_s{};
    // static_param at offset 0x70
    sead::SafeString mAnchorName_s{};
    sead::Vector3f _80;
};
KSYS_CHECK_SIZE_NX150(AssassinBossEscapeFromTarget, 0x90);

}  // namespace uking::ai
