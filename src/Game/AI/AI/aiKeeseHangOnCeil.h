#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeeseHangOnCeil : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KeeseHangOnCeil, ksys::act::ai::Ai)
public:
    explicit KeeseHangOnCeil(const InitArg& arg);
    ~KeeseHangOnCeil() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void calc_() override;

protected:
    // 0x710045258c (placeholder name): copies the first entry of the sensor `_260[1]` that the Unk_7102451470 filter
    // accepts into `out`.
    bool sub_710045258C(ksys::act::Unk_7100d78e50* out);
    // 0x7100452694 (placeholder name): sends the 0x8000006 message (`link`, `a2`, `a3`, `pos`) and passes it on to the
    // entries of the awareness list that are closer than 10.
    void sub_7100452694(ksys::act::BaseProcLink* link, s32 a2, s32 a3, const sead::Vector3f* pos);
    // 0x7100452800 (placeholder name): copies the first entry of the sensor `_260[0]` that the Unk_71024514c0 filter
    // accepts (and sub_71005D9FC0 does not reject) into `out`.
    bool sub_7100452800(ksys::act::Unk_7100d78e50* out);

    Unk_710235abc8 _38{mActor, 0x8000006};
    Unk_7102450528 _90;
    f32 _108 = 0;
};

}  // namespace uking::ai
