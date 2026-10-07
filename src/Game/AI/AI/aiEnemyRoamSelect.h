#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class EnemyRoamSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRoamSelect, ksys::act::ai::Ai)
public:
    explicit EnemyRoamSelect(const InitArg& arg);
    ~EnemyRoamSelect() override;
    bool isChangeable() const override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool sub_71003B3720();
    // 0x71003b384c (placeholder name): picks the best "linked" actor of the map object (tag 0xc6bb51c0 and in the calc
    // state; the first one that sub_71006DE574 accepts wins, then sub_71006DE3D8, sub_71006DE4A4 and the rest) into _50
    // and sets the priority _74 (3 / 2 / 1 / 0); true when that is a different actor than before.
    bool sub_71003B384C();

protected:
    // static_param at offset 0x38
    const float* mHideGrassHeight_s{};
    // static_param at offset 0x40
    const float* mNotReturnDist_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mCentralPos_d{};
    ksys::act::BaseProcLink _50;
    ksys::act::BaseProcLink _60;
    u32 _70 = 0;
    s32 _74 = -1;
    bool _78 = false;
};

}  // namespace uking::ai
