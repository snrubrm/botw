#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::act {
class WolfLink;
}

namespace uking::ai {

class WolfLinkBattleRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkBattleRoot, ksys::act::ai::Ai)
public:
    explicit WolfLinkBattleRoot(const InitArg& arg);
    ~WolfLinkBattleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

protected:
    bool sub_7100601F84();
    bool sub_7100602654();
    bool sub_7100602CCC();
    bool sub_7100602E40();

    // static_param at offset 0x38
    const float* mAttackIntiationRange_s{};
    // static_param at offset 0x40
    const float* mChanceToBarkOnAttackFail_s{};
    // static_param at offset 0x48
    const bool* mUseChainAttack_s{};
    // dynamic_param at offset 0x50
    float* mKeepTargetRange_d{};
    f32 _58 = -1.0f;
    f32 _5c = 0.0f;
    act::WolfLink* _60{};
    bool _68 = false;
    bool _69 = false;
};
KSYS_CHECK_SIZE_NX150(WolfLinkBattleRoot, 0x70);

}  // namespace uking::ai
