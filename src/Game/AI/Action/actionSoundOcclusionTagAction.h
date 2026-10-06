#pragma once

#include <container/seadBuffer.h>
#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SoundOcclusionTagAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(SoundOcclusionTagAction, AreaTagAction)
public:
    explicit SoundOcclusionTagAction(const InitArg& arg);
    ~SoundOcclusionTagAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    sead::Buffer<Payload>* m6() override { return &_38; }

    sead::Buffer<Payload> _38;
    // static_param at offset 0x48
    const float* mOcclusionLevel_s{};
    s32 _50 = 0;
};

}  // namespace uking::action
