#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DoChangeOneTime : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DoChangeOneTime, ksys::act::ai::Ai)
public:
    explicit DoChangeOneTime(const InitArg& arg);
    ~DoChangeOneTime() override;
    void calc_() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    Unk_7102450648 _38{0x1800029};
};

}  // namespace uking::ai
