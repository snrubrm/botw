#pragma once

#include "KingSystem/System/VFRValue.h"
#include "Game/AI/Action/actionStopASIgnite.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TurnIgnite : public StopASIgnite {
    SEAD_RTTI_OVERRIDE(TurnIgnite, StopASIgnite)
public:
    explicit TurnIgnite(const InitArg& arg);
    ~TurnIgnite() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x80
    const float* mRotSpd_s{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _90;
    sead::Matrix33f _9c;
    ksys::VFRValue _c0;
    u8 _cc[0x4];
};
KSYS_CHECK_SIZE_NX150(TurnIgnite, 0xd0);

}  // namespace uking::action
