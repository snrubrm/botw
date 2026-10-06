#pragma once

#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StoneOctarockWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StoneOctarockWait, ksys::act::ai::Ai)
public:
    explicit StoneOctarockWait(const InitArg& arg);
    ~StoneOctarockWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool isChangeable() const override;

protected:
    // inline-only in the original; name is a guess (the same sequence is inlined in enter_ and twice in calc_).
    bool isTerrorNoticed() const;

    struct Params {
        // static_param at offset 0x38
        const int* mGuardEndTime_s{};
        // static_param at offset 0x40
        const int* mNoticeTerrorLevel_s{};
    };
    Params mParams;
    Unk_71024519a8 _48;
    float _70 = 0;
    int _74 = 0;
    int _78 = 0;
};

}  // namespace uking::ai
