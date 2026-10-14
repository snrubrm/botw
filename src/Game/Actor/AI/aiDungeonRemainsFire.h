#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRemainsFire : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonRemainsFire, ksys::act::ai::Ai)
public:
    explicit DungeonRemainsFire(const InitArg& arg);
    ~DungeonRemainsFire() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mRailName_s{};
    sead::Matrix34f _48[3];
};
KSYS_CHECK_SIZE_NX150(DungeonRemainsFire, 0xd8);

}  // namespace uking::ai
