#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class EnemyNoticeTerror : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNoticeTerror, ksys::act::ai::Ai)
public:
    explicit EnemyNoticeTerror(const InitArg& arg);
    ~EnemyNoticeTerror() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // Unnamed target record filled by m34.
    struct Unk {
        ksys::act::BaseProcLink _0;
        sead::Vector3f _10;
        u8 _1c = 0;
    };

    virtual bool m34(Unk* out);
    virtual void m35();
    virtual void m36();

    void sub_71003A7DD4();
protected:
    // static_param at offset 0x38
    const int* mWaitTime_s{};
    // static_param at offset 0x40
    const float* mNoWarnDist_s{};
    // static_param at offset 0x48
    const float* mNoWarnHeightMin_s{};
    // static_param at offset 0x50
    const float* mNoWarnHeightMax_s{};
    // static_param at offset 0x58
    const float* mNoTerrorDist_s{};
    Unk _60;
    Unk _80;
    f32 _a0{};
    int _a4{};
    int _a8{};
};

}  // namespace uking::ai
