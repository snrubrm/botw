#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GyroActivateTerminal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GyroActivateTerminal, ksys::act::ai::Ai)
public:
    explicit GyroActivateTerminal(const InitArg& arg);
    ~GyroActivateTerminal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    Unk_71023fa018 _38{0x1800012};
    bool _78 = false;
};

}  // namespace uking::ai
