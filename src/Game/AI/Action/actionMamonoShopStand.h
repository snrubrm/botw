#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MamonoShopStand : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MamonoShopStand, ksys::act::ai::Action)
public:
    explicit MamonoShopStand(const InitArg& arg);
    ~MamonoShopStand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    sead::Vector3f _1c = sead::Vector3f::zero;
    f32 _28 = 0.0f;
    u8 _2c[0x4];
};
KSYS_CHECK_SIZE_NX150(MamonoShopStand, 0x30);

}  // namespace uking::action
