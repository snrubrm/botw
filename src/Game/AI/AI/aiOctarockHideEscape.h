#pragma once

#include "Game/AI/AI/aiOctarockEscape.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockHideEscape : public OctarockEscape {
    SEAD_RTTI_OVERRIDE(OctarockHideEscape, OctarockEscape)
public:
    explicit OctarockHideEscape(const InitArg& arg);
    ~OctarockHideEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    sead::Vector3f* m34() override { return &_68; }
    void m35() override;

protected:
    void sub_71004EBE08(sead::Vector3f* pos, f32 escape_dist, const sead::Vector3f& target_pos);


    // static_param at offset 0x60
    const float* mEscapeDist_s{};
    sead::Vector3f _68;
};
KSYS_CHECK_SIZE_NX150(OctarockHideEscape, 0x78);

}  // namespace uking::ai
