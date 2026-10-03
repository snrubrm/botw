#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LinkageEnemyNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(LinkageEnemyNormal, EnemyNormal)
public:
    explicit LinkageEnemyNormal(const InitArg& arg);
    ~LinkageEnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m49(Unk1* out, s32 idx) override;
    void m50(Unk1* out, s32 idx) override;
    void calc_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void sub_71004839A4(const ksys::act::BaseProcLink& link);

protected:
    Unk_7102450558 _3d0;
};
KSYS_CHECK_SIZE_NX150(LinkageEnemyNormal, 0x420);

}  // namespace uking::ai
