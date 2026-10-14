#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PauseMenuPlayerRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PauseMenuPlayerRoot, ksys::act::ai::Ai)
public:
    explicit PauseMenuPlayerRoot(const InitArg& arg);
    ~PauseMenuPlayerRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    bool _38 = false;
    bool _39 = false;
};
KSYS_CHECK_SIZE_NX150(PauseMenuPlayerRoot, 0x40);

}  // namespace uking::ai
