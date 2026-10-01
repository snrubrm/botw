#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeyLockedShutter : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KeyLockedShutter, ksys::act::ai::Ai)
public:
    explicit KeyLockedShutter(const InitArg& arg);
    ~KeyLockedShutter() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    Unk_7102450828 _38{0x1800005};
};

}  // namespace uking::ai
