#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PreyDead : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PreyDead, ksys::act::ai::Ai)
public:
    explicit PreyDead(const InitArg& arg);
    ~PreyDead() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSendRadius_s{};
    // static_param at offset 0x40
    const bool* mIsEmitForceEscapeSignal_s{};
    Unk_7102410070 _48{mActor, 0x80000a4};
    ksys::Timer _90;
    sead::Vector3f _9c;
};
KSYS_CHECK_SIZE_NX150(PreyDead, 0xa8);

}  // namespace uking::ai
