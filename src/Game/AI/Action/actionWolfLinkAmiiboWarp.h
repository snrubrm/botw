#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WolfLinkAmiiboWarp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WolfLinkAmiiboWarp, ksys::act::ai::Action)
public:
    explicit WolfLinkAmiiboWarp(const InitArg& arg);
    ~WolfLinkAmiiboWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleAck_(const ksys::MessageAck* ack) override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::Vector3f* mTargetPos_d{};
    Unk_71023cd530 _28{mActor, 0x80000a8};
};

}  // namespace uking::action
