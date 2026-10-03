#pragma once

#include "Game/AI/Action/actionTeleportBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Teleport : public TeleportBase {
    SEAD_RTTI_OVERRIDE(Teleport, TeleportBase)
public:
    explicit Teleport(const InitArg& arg);
    ~Teleport() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    sead::Vector3f& m33() override { return _88; }
    void m36() override;

    // static_param at offset 0x78
    const float* mDistXZ_s{};
    // static_param at offset 0x80
    const float* mDistY_s{};
    sead::Vector3f _88 = sead::Vector3f::zero;
    sead::Vector3f _94 = sead::Vector3f::zero;
};

KSYS_CHECK_SIZE_NX150(Teleport, 0xa0);

}  // namespace uking::action
