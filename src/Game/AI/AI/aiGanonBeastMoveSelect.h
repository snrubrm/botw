#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonBeastMoveSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonBeastMoveSelect, ksys::act::ai::Ai)
public:
    explicit GanonBeastMoveSelect(const InitArg& arg);
    ~GanonBeastMoveSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool sub_71003E51DC();
    bool sub_71003E5500(const sead::Vector3f* first, const sead::Vector3f* second);

protected:
    // static_param at offset 0x38
    const float* mDist_s{};
    // static_param at offset 0x40
    const float* mFrontOffset_s{};
    // static_param at offset 0x48
    const float* mWallDist_s{};
    // static_param at offset 0x50
    const bool* mIsMoveFinishEnd_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mCentralPoint_s{};
};

}  // namespace uking::ai
