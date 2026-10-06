#pragma once

#include "Game/AI/AI/aiSiteBossRoot.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossBowRoot : public SiteBossRoot {
    SEAD_RTTI_OVERRIDE(SiteBossBowRoot, SiteBossRoot)
public:
    explicit SiteBossBowRoot(const InitArg& arg);
    ~SiteBossBowRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_7100575448(s32 index);
    void sub_7100576744(s32 index);

    // static_param at offset 0xf8
    const int* mArrowRainAttackPower_s{};
    // static_param at offset 0x100
    const int* mAtMinPower_s{};
    // static_param at offset 0x108
    const int* mReflectArrowAttackPower_s{};
    // static_param at offset 0x110
    sead::SafeString mDemoName_s{};
    u32 _120 = 0;
    bool _124 = false;
    ksys::act::BaseProcLink _128;
};
KSYS_CHECK_SIZE_NX150(SiteBossBowRoot, 0x138);

}  // namespace uking::ai
