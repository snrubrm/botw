#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class SiteBossSwordAfterImageMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossSwordAfterImageMove, ksys::act::ai::Action)
public:
    explicit SiteBossSwordAfterImageMove(const InitArg& arg);
    ~SiteBossSwordAfterImageMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMoveFrame_s{};
    // map_unit_param at offset 0x28
    const int* mPatternID_m{};
    // aitree_variable at offset 0x30
    void* mSiteBossSwordAfterImageUnit_a{};
    ksys::Timer _38{};
    sead::Vector3f _44;
    sead::Vector3f _50;
    bool _5c = false;
    bool _5d = false;
    bool _5e = false;
    bool _5f = false;

    // Local class of the object the "SiteBossSwordAfterImageUnit" AI tree variable points to
    // (embedded in the action; vtable only referenced by this action's constructor).
    class Unit : public Unk_71025afb58 {
        SEAD_RTTI_OVERRIDE(Unit, Unk_71025afb58)
    public:
        Unit() = default;
        ~Unit() override = default;

        bool _8 = false;
        bool _9 = false;
    };

    Unit _60;
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordAfterImageMove, 0x70);

}  // namespace uking::action
