#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerGrab : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerGrab, ksys::act::ai::Ai)
public:
    explicit PlayerGrab(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

    bool isFinished() const override;
    bool isChangeable() const override;

protected:
    bool _38 = false;
    bool _39 = false;
};
KSYS_CHECK_SIZE_NX150(PlayerGrab, 0x40);

}  // namespace uking::ai
