#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

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
};

}  // namespace uking::action
