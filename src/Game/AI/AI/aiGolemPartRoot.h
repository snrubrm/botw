#pragma once

#include "Game/AI/AI/aiReuseBulletPartsRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemPartRoot : public ReuseBulletPartsRoot {
    SEAD_RTTI_OVERRIDE(GolemPartRoot, ReuseBulletPartsRoot)
public:
    explicit GolemPartRoot(const InitArg& arg);
    ~GolemPartRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool m34() override;

protected:
    // 0x71003fdcf8 (placeholder name): if the linked part (_c8) is asleep, wakes it up at `pos` (resets its matrix to
    // the identity with that translation).
    void sub_71003FDCF8(const sead::Vector3f* pos);

    // static_param at offset 0x90
    const float* mChemFieldScale_s{};
    // static_param at offset 0x98
    sead::SafeString mNormalAS_s{};
    // static_param at offset 0xa8
    sead::SafeString mActiveAS_s{};
    // aitree_variable at offset 0xb8
    bool* mGolemPartInitialIceMagic_a{};
    // aitree_variable at offset 0xc0
    bool* mGolemPartInitialBurn_a{};
    ksys::act::BaseProcLink _c8;
};

}  // namespace uking::ai
