#pragma once

#include "KingSystem/System/VFRValue.h"
#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnetimeMoveASPlay : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(OnetimeMoveASPlay, OnetimeStopASPlay)
public:
    explicit OnetimeMoveASPlay(const InitArg& arg);
    ~OnetimeMoveASPlay() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const bool* mIsChangable_s{};
    ksys::VFRValue _50{0.0f};
    int _5c = 0;
    int _60 = 0;
    int _64 = 0;
};

}  // namespace uking::action
