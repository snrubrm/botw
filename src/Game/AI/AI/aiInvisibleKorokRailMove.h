#pragma once

#include "Game/AI/AI/aiKorokRailMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class InvisibleKorokRailMove : public KorokRailMove {
    SEAD_RTTI_OVERRIDE(InvisibleKorokRailMove, KorokRailMove)
public:
    explicit InvisibleKorokRailMove(const InitArg& arg);
    ~InvisibleKorokRailMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    void m38(sead::Vector3f* diff, sead::Vector3f* pos) override;

protected:
    Unk_71012419b4 _c0;
};
KSYS_CHECK_SIZE_NX150(InvisibleKorokRailMove, 0xe0);

}  // namespace uking::ai
