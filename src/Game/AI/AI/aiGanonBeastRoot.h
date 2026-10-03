#pragma once

#include "Game/AI/aiUnk_71023f18e8.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class GanonBeastRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonBeastRoot, ksys::act::ai::Ai)
public:
    explicit GanonBeastRoot(const InitArg& arg);
    ~GanonBeastRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x3e6254 (lane4 s23)
    void sub_71003E6254();

    struct Params {
        // aitree_variable at offset 0x38
        bool* mIsGanonBeastAngry_a{};
        // aitree_variable at offset 0x40
        void* mWeakPointAliveFlag_a{};
        // aitree_variable at offset 0x48
        void* mWeakPointActiveFlag_a{};
    };
    Params mParams;
    // The actor "rain" component (its "GrudeRainObject" / "GrudeRainObject2" static params are members
    // of it: offsets 0x90 / 0xa0).
    /* 0x50 */ Unk_71023f18e8 _50;
    // static_param at offset 0xc0
    const int* mGrudeInterval3_s{};
    // static_param at offset 0xc8
    const int* mGrudeInterval4_s{};
    // static_param at offset 0xd0
    const int* mGrudeInterval5_s{};
    // static_param at offset 0xd8
    const int* mGrudeCreateNum_s{};
    // static_param at offset 0xe0
    const int* mWeakPointASSlot_s{};
    // static_param at offset 0xe8
    const float* mGrudePlayerDist_s{};
    // static_param at offset 0xf0
    const float* mGrudeRandRange_s{};
    // static_param at offset 0xf8
    const float* mGrudeCenterOffset_s{};
    // static_param at offset 0x100
    sead::SafeString mInitWeakPointASName_s{};
    /* 0x110 */ ksys::act::BaseProcLink _110;
    /* 0x120 */ s32 _120 = 0;
    /* 0x124 */ s32 _124 = -1;
    /* 0x128 */ bool _128 = false;
};
KSYS_CHECK_SIZE_NX150(GanonBeastRoot, 0x130);

}  // namespace uking::ai
