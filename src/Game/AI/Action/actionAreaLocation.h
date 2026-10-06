#pragma once

#include <mc/seadJobQueue.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

// Message 0x8000082 (sender Unk_71023677d8; placeholder name = sender vtable): the location the actor
// announces (message id string, priority, and the area id the UI looked up for the message id).
struct Unk_71023677d8_Payload {
    struct Data {
        // 0x7100903158 (declared only; in the listener's TU): copies the data. Placeholder name.
        void sub_7100903158(const Data& other);

        sead::FixedSafeString<256> mMessageId{sead::SafeString("")};
        s32 mPriority = -1;
        s32 mAreaId = -1;
        ksys::act::BaseProcLink mLink;
    };

    bool _0 = true;
    Data _8;
    sead::JobQueueLock mLock;
};

// vtable 0x71023677d8 (AreaLocation::_40; D2 / D0 / m2 at 0x71000a06ac / 0x71000a0d48 / 0x71000a0d80)
class Unk_71023677d8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(bool active) {
        sead::ScopedLock<sead::JobQueueLock> lock(&_18.mLock);
        _18._0 = active;
    }

    Unk_71023677d8_Payload _18;
};

namespace uking::action {

class AreaLocation : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AreaLocation, ksys::act::ai::Action)
public:
    explicit AreaLocation(const InitArg& arg);
    ~AreaLocation() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mLocationPriority_m{};
    // map_unit_param at offset 0x28
    sead::SafeString mMessageID_m{};
    bool _38 = false;
    Unk_71023677d8 _40{mActor, 0x8000082};
};

}  // namespace uking::action
