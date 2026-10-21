#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::action {

class CreateEpona : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CreateEpona, ksys::act::ai::Action)
public:
    explicit CreateEpona(const InitArg& arg);
    ~CreateEpona() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAreaSearchCharacterRadius_s{};
    // static_param at offset 0x28
    const float* mAreaThreshold_s{};
    // static_param at offset 0x30
    const float* mAreaSearchRadius_s{};
    // static_param at offset 0x38
    const float* mCreateStartRate_s{};
    // 0x40 - 0x150: not decompiled yet (enter_ / calc_ are still stubs). The member is value-initialised, so the
    // whole block including the string is zeroed before the string is constructed (one memset in the constructor).
    struct Body {
        u8 _40[0x150 - 0x40]{};
        sead::FixedSafeString<48> _150;
    };
    Body mBody = Body();
    ksys::act::BaseProcHandle _198;
    ksys::phys::Unk_7102372790* _1a8{};
};
KSYS_CHECK_SIZE_NX150(CreateEpona, 0x1b0);

}  // namespace uking::action
