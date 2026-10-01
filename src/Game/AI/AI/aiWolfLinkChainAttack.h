#pragma once

#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::act {
class WolfLink;
}

namespace uking::ai {

class WolfLinkChainAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkChainAttack, ksys::act::ai::Ai)
public:
    explicit WolfLinkChainAttack(const InitArg& arg);
    ~WolfLinkChainAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    struct Unk1 {
        void* _0{};
        s32 _8 = -1;
        u32 _c = 0;
        u8 _10 = 0;
    };


    // static_param at offset 0x38
    const int* mNumAttacks_s{};
    // static_param at offset 0x40
    const float* mAnimalUnitRate_s{};
    // static_param at offset 0x48
    const float* mBeginEndAnimASPlayRate_s{};
    // static_param at offset 0x50
    const float* mTurnAnimPlayRate_s{};
    // static_param at offset 0x58
    const float* mAttackAnimPlayRate_s{};
    // static_param at offset 0x60
    const float* mAttackAnimMinDistance_s{};
    // static_param at offset 0x68
    const float* mAttackDistanceOffset_s{};
    // static_param at offset 0x70
    const bool* mIsInvincible_s{};
    // static_param at offset 0x78
    const bool* mIsIncrementHitOnMiss_s{};
    sead::SafeArray<s32, 10> _80{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    Unk1 _a8;
    bool _c0 = false;
    s32 _c4 = 0;
    act::WolfLink* _c8{};
};
KSYS_CHECK_SIZE_NX150(WolfLinkChainAttack, 0xd0);

}  // namespace uking::ai
