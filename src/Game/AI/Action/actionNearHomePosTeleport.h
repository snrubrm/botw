#pragma once

#include "Game/AI/Action/actionLandTeleport.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NearHomePosTeleport : public LandTeleport {
    SEAD_RTTI_OVERRIDE(NearHomePosTeleport, LandTeleport)
public:
    explicit NearHomePosTeleport(const InitArg& arg);
    ~NearHomePosTeleport() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m40() override;
    bool m41() override;
};

}  // namespace uking::action
