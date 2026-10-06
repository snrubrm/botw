#pragma once

#include <container/seadObjList.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::action {

// Placeholder name (the object a gull's `_10` points to; only virtual slot 10 (vtable offset 0x50) is known: leave_ calls
// it after sub_7100287830).
class Unk_SwarmGullObject {
public:
    virtual ~Unk_SwarmGullObject();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
};

class SwarmGullMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwarmGullMove, ksys::act::ai::Action)
public:
    explicit SwarmGullMove(const InitArg& arg);
    ~SwarmGullMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    struct Gull;
    // 0x71002868bc (CSV swarmGullStuff; declared only; 436 B)
    void sub_71002868BC();
    // 0x7100287830 (declared only; 488 B): releases the gull's resources before its object is told to stop.
    void sub_7100287830(Gull* gull);

    // static_param at offset 0x20
    sead::SafeString mASName_s{};
    // map_unit_param at offset 0x30
    const int* mSubUnitNum_m{};
    // map_unit_param at offset 0x38
    const float* mCreateMaxRadius_m{};
    // map_unit_param at offset 0x40
    const float* mCreateMinRadius_m{};
    // map_unit_param at offset 0x48
    const float* mCreateHeightRange_m{};
    // map_unit_param at offset 0x50
    const float* mRoundMaxRadius_m{};
    // map_unit_param at offset 0x58
    const float* mRoundMinRadius_m{};
    // map_unit_param at offset 0x60
    const float* mCrySoundIntervalMin_m{};
    // map_unit_param at offset 0x68
    const float* mCrySoundIntervalMax_m{};
    struct Gull {
        ksys::act::BaseProcHandle _0;
        Unk_SwarmGullObject* _10 = nullptr;
        s32 _18 = -1;
    };
    Gull _70[10];
    sead::ObjList<sead::Vector3f> _1b0;
    s32 _1e0 = 0;
};

}  // namespace uking::action
