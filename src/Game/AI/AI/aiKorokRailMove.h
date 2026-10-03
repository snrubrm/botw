#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokRailMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokRailMove, ksys::act::ai::Ai)
public:
    explicit KorokRailMove(const InitArg& arg);
    ~KorokRailMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    virtual void m34();
    virtual f32 m35();
    virtual ksys::map::Rail* m36();
    virtual void m37();
    virtual void m38(sead::Vector3f* diff, sead::Vector3f* pos) {
        diff->setSub(mActor->getMtx().getTranslation(), *pos);
    }
    virtual void m39();
    virtual void m40();
    virtual bool m41();

    void changeToMove();
    f32 sub_710045BA10();
    void sub_710045BA20();
    bool sub_710045BD08();
    void sub_710045BD18(f32 wait_frame);
    void changeToHeadToRail(const sead::Vector3f& pos);
    void sub_710045C3A8();

protected:
    // static_param at offset 0x38
    const float* mOnRailDistance_s{};
    // static_param at offset 0x40
    const float* mFarDistance_s{};
    // static_param at offset 0x48
    const bool* mIsIgnoreNoWaitStopPoint_s{};
    // map_unit_param at offset 0x50
    const float* mRailMoveSpeed_m{};
    Unk_71024f15c0 _58;
    s32 _b8 = 0;
};
KSYS_CHECK_SIZE_NX150(KorokRailMove, 0xc0);

}  // namespace uking::ai
