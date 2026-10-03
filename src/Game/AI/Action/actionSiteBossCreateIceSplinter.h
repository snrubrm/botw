#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossCreateIceSplinter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossCreateIceSplinter, ksys::act::ai::Action)
public:
    explicit SiteBossCreateIceSplinter(const InitArg& arg);
    ~SiteBossCreateIceSplinter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x30
    int* mIgnitionNum_d{};
    bool _38 = false;
    u8 _39[0x3];
    s32 _3c[2]{};
    s32 _44[2]{};
    u8 _4c[0x4];
};
KSYS_CHECK_SIZE_NX150(SiteBossCreateIceSplinter, 0x50);

}  // namespace uking::action
