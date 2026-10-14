#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ShortRangeBattleAlignment : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ShortRangeBattleAlignment, ksys::act::ai::Behavior)
public:
    explicit ShortRangeBattleAlignment(const InitArg& arg);
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mMode_s{};
    /* 0x30 */ const float* mOffsetY_s{};
};
KSYS_CHECK_SIZE_NX150(ShortRangeBattleAlignment, 0x38);

}  // namespace uking::behavior
