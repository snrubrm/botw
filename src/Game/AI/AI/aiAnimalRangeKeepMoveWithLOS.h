#pragma once

#include <limits>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::act {
class WolfLink;
}

namespace uking::ai {

class AnimalRangeKeepMoveWithLOS : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalRangeKeepMoveWithLOS, ksys::act::ai::Ai)
public:
    explicit AnimalRangeKeepMoveWithLOS(const InitArg& arg);
    ~AnimalRangeKeepMoveWithLOS() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

protected:
    bool sub_7100309A88();
    void sub_7100309BAC();
    void sub_7100309D40();

    // static_param at offset 0x38
    const int* mFindPathBeginTimer_s{};
    // static_param at offset 0x40
    const int* mNoPathTimer_s{};
    // static_param at offset 0x48
    const float* mCloseStartDist_s{};
    // static_param at offset 0x50
    const float* mCloseEndDist_s{};
    // static_param at offset 0x58
    const float* mLeaveStartDist_s{};
    // static_param at offset 0x60
    const float* mLeaveEndDist_s{};
    // static_param at offset 0x68
    const float* mBattleEndDist_s{};
    // static_param at offset 0x70
    const float* mDistFailOnUnreachablePath_s{};
    f32 _78{};
    s32 _7c{};
    s32 _80{};
    f32 _84{};
    s32 _88{};
    s32 _8c{};
    sead::Vector3f _90{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                       std::numeric_limits<f32>::quiet_NaN()};
    act::WolfLink* _a0{};
    f32 _a8{};
    bool _ac{};
    bool _ad{};
};
KSYS_CHECK_SIZE_NX150(AnimalRangeKeepMoveWithLOS, 0xb0);

}  // namespace uking::ai
