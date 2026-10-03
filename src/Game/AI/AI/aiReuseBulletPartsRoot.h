#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ReuseBulletPartsRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ReuseBulletPartsRoot, ksys::act::ai::Ai)
public:
    explicit ReuseBulletPartsRoot(const InitArg& arg);
    ~ReuseBulletPartsRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    virtual bool m34();

    void sub_7100551DAC();

protected:
    Unk_7102450b88 _38;
    bool _88 = false;
};
KSYS_CHECK_SIZE_NX150(ReuseBulletPartsRoot, 0x90);

}  // namespace uking::ai
