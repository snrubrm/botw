#pragma once

#include <container/seadPtrArray.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiActorLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class RemainsWaterBulletController : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsWaterBulletController, ksys::act::ai::Ai)
public:
    // A bullet actor: link (registered in the battle info object) + creation handle.
    struct Unk1 {
        Unk_7102370e70 mLink;
        ksys::act::BaseProcHandle mHandle;
        bool _28;
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x30);

    explicit RemainsWaterBulletController(const InitArg& arg);
    ~RemainsWaterBulletController() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // Deletes the chase (type 0) / explode (type 1) bullets, or both (-1).
    void sub_7100546D30(s32 type);
    void sub_71005474E4();
    void sub_710054779C();
    void sub_71005478C8();
    void sub_7100547D20(s32 type);
    void sub_7100547FF4();
    // Fires the chase (type 0) or explode (type 1) bullets of the current phase.
    bool sub_7100548220(s32 type);
    void sub_71005484D4();
    void sub_7100548638();
    bool sub_7100548A38();
    bool sub_7100548D8C(s32 type);
    void sub_7100549108(Unk1* bullet);
    bool sub_7100548B34();

protected:
    ksys::act::Unk_7100d3bce4 _38{mActor};
    // static_param at offset 0x50
    const float* mInsideAreaRadius_s{};
    // static_param at offset 0x58
    const float* mFirstBulletTimer_s{};
    // static_param at offset 0x60
    const float* mSecondBulletTimer_s{};
    // static_param at offset 0x68
    const float* mNextBulletTimerSuccess_s{};
    // static_param at offset 0x70
    const float* mNextBulletTimerFail_s{};
    // static_param at offset 0x78
    sead::SafeString mChaseBulletNum_s{};
    // static_param at offset 0x88
    sead::SafeString mExplodeBulletNum_s{};
    // static_param at offset 0x98
    sead::SafeString mChaseBulletActorName_s{};
    // static_param at offset 0xa8
    sead::SafeString mExplodeBulletActorName_s{};
    // static_param at offset 0xb8
    const sead::Vector3f* mInsideAreaCenter_s{};
    // static_param at offset 0xc0
    const sead::Vector3f* mInsideAreaWidth_s{};
    // aitree_variable at offset 0xc8
    void* mRemainsWaterBattleInfo_a{};
    s32 _d0[4];  // chase bullet counts per phase (ChaseBulletNum)
    s32 _e0[4];  // explode bullet counts per phase (ExplodeBulletNum)
    Unk1 _f0[5];
    Unk1 _1e0[5];
    sead::FixedPtrArray<Unk1, 10> _2d0;
    sead::FixedPtrArray<Unk1, 1> _330;
    sead::Vector3f _348{0, 0, 0};
    sead::BoundBox3f _354;
    s32 _36c = 0;
    s32 _370 = 0;
    ksys::Timer _374{0, 0};
};
KSYS_CHECK_SIZE_NX150(RemainsWaterBulletController, 0x380);

}  // namespace uking::ai
