#pragma once

#include <container/seadObjArray.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {
class MoveAndFreeFallGondola;
}

namespace uking::action {

class DgnObjDlcGondolaCreateTag : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DgnObjDlcGondolaCreateTag, ksys::act::ai::Action)
public:
    explicit DgnObjDlcGondolaCreateTag(const InitArg& arg);
    ~DgnObjDlcGondolaCreateTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;
    void sub_7100056294();
    void sub_710005637C(ksys::act::BaseProcHandle* handle, f32 offset_time);
    void sub_710005671C(ksys::act::BaseProcHandle* handle);
    void sub_7100056CD4(ksys::act::BaseProcLink* link, const ksys::Message* message);
    ai::MoveAndFreeFallGondola* sub_7100056E70(ksys::act::ai::ActionBase* action);

    // static_param at offset 0x20
    sead::SafeString mActorName_s{};
    // map_unit_param at offset 0x30
    const float* mIntervalTime_m{};
    // map_unit_param at offset 0x38
    const float* mRailMoveSpeed_m{};
    // The constructor initializes 32 and 64 link slots and their pointer arrays.
    sead::FixedObjArray<ksys::act::BaseProcLink, 32> _40;
    sead::FixedObjArray<ksys::act::BaseProcLink, 64> _360;
    ksys::act::BaseProcHandle _980[6];

    Unk_710235cec8 _9e0;
    f32 _a30 = 0.0f;
    u8 _a34[4];
};
KSYS_CHECK_SIZE_NX150(DgnObjDlcGondolaCreateTag, 0xa38);

}  // namespace uking::action
