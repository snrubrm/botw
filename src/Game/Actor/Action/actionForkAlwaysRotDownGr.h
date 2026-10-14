#pragma once

#include <math/seadVector.h>
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwaysRotDownGr : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAlwaysRotDownGr, ksys::act::ai::Action)
public:
    explicit ForkAlwaysRotDownGr(const InitArg& arg);
    ~ForkAlwaysRotDownGr() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mGroundRotAngle_s{};
    ksys::VFRValue _28;
    sead::Vector3f _34;
    bool _40 = true;
    u8 _41[0x7];
};
KSYS_CHECK_SIZE_NX150(ForkAlwaysRotDownGr, 0x48);

}  // namespace uking::action
