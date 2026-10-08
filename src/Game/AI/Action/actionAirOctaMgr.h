#pragma once

#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace uking::action {

// Awareness filters (like uking::ai::Unk_7102401238, which accepts flying balloons: _7102362ea8 accepts player
// actors, _7102362ed0 flying balloons); each has its own vtable
// (0x7102362ea8 / 0x7102362ed0), `m2` and D0 at 0x7100087f54 / 0x7100087f30 and 0x7100088038 / 0x7100088014.
// Placeholder names.
class Unk_7102362ea8 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

class Unk_7102362ed0 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

class AirOctaMgr : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AirOctaMgr, ksys::act::ai::Action)
public:
    explicit AirOctaMgr(const InitArg& arg);
    ~AirOctaMgr() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mLeaveDistance_s{};
    // static_param at offset 0x28
    const float* mLeaveDownY_s{};
    // static_param at offset 0x30
    const float* monGraundEscapeDist_s{};
    // static_param at offset 0x38
    const float* mPlayerLostTime_s{};
    // map_unit_param at offset 0x40
    const float* mMoveDis_m{};
    // map_unit_param at offset 0x48
    const bool* mReactHorn_m{};

    // The members from 0x50 follow the constructor 0x7100085354 / destructor 0x7100085618; the types of the
    // elements of _60 (0x18 bytes, a link first) and of the members in the padding are unknown.
    struct Unk60 {
        ksys::act::BaseProcLink link;
        u64 _10;
    };
    sead::Vector3f _50 = sead::Vector3f::zero;
    sead::Buffer<Unk60> _60;
    ksys::act::BaseProcLink _70;
    Unk_7102450528 _80;
    f32 _f8 = 1.0f;
    bool _fc = false;
    ksys::act::BaseProcLink _100;
    u8 _110[0x358 - 0x110];
    Unk_7102362e80 _358{mActor, 0x80000cc};
};

}  // namespace uking::action
