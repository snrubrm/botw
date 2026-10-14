#pragma once

#include <math/seadBoundBox.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWaterNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsWaterNormal, ksys::act::ai::Ai)
public:
    explicit RemainsWaterNormal(const InitArg& arg);
    ~RemainsWaterNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool sub_710054B518();

protected:
    // static_param at offset 0x38
    const sead::Vector3f* mInsideAreaWidth_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mInsideAreaCenter_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mInsideAreaWidth02_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mInsideAreaCenter02_s{};
    bool _58 = false;
    sead::BoundBox3f _5c;
    sead::BoundBox3f _74;
};
KSYS_CHECK_SIZE_NX150(RemainsWaterNormal, 0x90);

}  // namespace uking::ai
