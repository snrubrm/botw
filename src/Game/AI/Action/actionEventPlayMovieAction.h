#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/StringBoard.h"

namespace uking::action {

class EventPlayMovieAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventPlayMovieAction, ksys::act::ai::Action)
public:
    explicit EventPlayMovieAction(const InitArg& arg);
    ~EventPlayMovieAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mFileName_d{};
    ksys::StringBoard _30;
    sead::FixedSafeString<32> _38;
    // Assigned in the ctor body as integers (the stores are mov/movk-built u64/u32 merged
    // into stp/str, after the string copy, so not NSDMIs). Bit patterns read as floats are
    // 474.498|1.5, -300.0 and 50.06|0.0.
    u64 _70;
    u64 _78;
    u64 _80;
};

KSYS_CHECK_SIZE_NX150(EventPlayMovieAction, 0x88);

}  // namespace uking::action
