#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::ai {

class PlayerZoraRide : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerZoraRide, ksys::act::ai::Ai)
public:
    explicit PlayerZoraRide(const InitArg& arg);
    ~PlayerZoraRide() override;

    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    ksys::act::ModelBindInfo _38;
    bool _d8 = false;
    bool _d9 = false;
};
KSYS_CHECK_SIZE_NX150(PlayerZoraRide, 0xe0);

}  // namespace uking::ai
