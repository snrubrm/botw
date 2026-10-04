#pragma once

#include "Game/AI/Action/actionChemicalPhysBall.h"
#include "Game/AI/aiUnk_710244ECF0.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RodMagicPhysBall : public ChemicalPhysBall {
    SEAD_RTTI_OVERRIDE(RodMagicPhysBall, ChemicalPhysBall)
public:
    explicit RodMagicPhysBall(const InitArg& arg);
    ~RodMagicPhysBall() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m33() override;
    int m36() override;

    // static_param at offset 0xb8
    sead::SafeString mCreateActorName_s{};
    // static_param at offset 0xc8
    const int* mChemicalType_s{};
    // static_param at offset 0xd0
    const float* mBgCheckHeight_s{};
    /* 0xd8 */ ksys::act::BaseProcLink _d8;
    /* 0xe8 */ Unk_710244ecf0 _e8;
    /* 0x160 */ bool _160 = false;
    bool _161 = false;
    struct Entry {
        void* _0 = nullptr;
        s32 _8 = 0;
    };
    /* 0x168 */ Entry _168[4];
    /* 0x1a8 */ struct Unk1a8 {
        void* _0;
        u32 _8;
        bool _c;
        u8 _d[3];
    } _1a8{};
    // 0x710023b234 (declared only): out of line in the original.
    void sub_710023B234(Unk1a8* out);
};

}  // namespace uking::action
