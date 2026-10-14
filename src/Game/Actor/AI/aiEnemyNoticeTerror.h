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
        Unk() = default;
        Unk(const Unk& other) {
            _0 = other._0;
            _1c = other._1c;
            _10 = other._10;
        }
        // Returns by value: the original's `_80 = _60` also builds (and destroys) a temporary copy.
        Unk operator=(const Unk& other) {
            _0 = other._0;
            _1c = other._1c;
            _10 = other._10;
            return *this;
        }

        ksys::act::BaseProcLink _0;
        sead::Vector3f _10;
        u8 _1c = 0;
    };

    virtual bool m34(Unk* out);
    virtual void m35();
    virtual void m36();

    void changeToNotice();

    // Placeholder names (lane1 s22).
    // 0x71003a7a88: whether no awareness entry (nearer than NoTerrorDist) is the remembered target
    // `_80`.
    bool sub_71003A7A88();
    // 0x71003a7b64: the position of the remembered target (`_60`, else `_80`); false without one.
    bool sub_71003A7B64(sead::Vector3f* out);
    // 0x71003a7c44: starts "眺める" towards the target position.
    void changeToGaze();

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
