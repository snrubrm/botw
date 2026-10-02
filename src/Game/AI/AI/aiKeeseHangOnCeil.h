#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
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
    bool handleMessage_(const ksys::Message& message) override;

protected:
    Unk_710235abc8 _38{mActor, 0x8000006};
    Unk_7102450528 _90;
    f32 _108 = 0;
};

}  // namespace uking::ai
