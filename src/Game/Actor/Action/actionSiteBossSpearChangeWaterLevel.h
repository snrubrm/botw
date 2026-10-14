#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSpearChangeWaterLevel : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossSpearChangeWaterLevel, ksys::act::ai::Action)
public:
    explicit SiteBossSpearChangeWaterLevel(const InitArg& arg);
    ~SiteBossSpearChangeWaterLevel() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsSignalOn_s{};
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
    bool _38 = false;
    u8 _39[3];
    sead::Vector3f _3c;
    f32 _48 = 0;
    f32 _4c = 0;
    f32 _50 = 0;
    u8 _54[0x4];
};
KSYS_CHECK_SIZE_NX150(SiteBossSpearChangeWaterLevel, 0x58);

}  // namespace uking::action
