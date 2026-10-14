#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceSystemFadeOut : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForceSystemFadeOut, ksys::act::ai::Action)
public:
    explicit ForceSystemFadeOut(const InitArg& arg);
    ~ForceSystemFadeOut() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool _1c = false;
    u8 _1d[0x3];

};
KSYS_CHECK_SIZE_NX150(ForceSystemFadeOut, 0x20);

}  // namespace uking::action
