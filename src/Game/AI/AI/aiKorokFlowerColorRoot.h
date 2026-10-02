#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class KorokFlowerColorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokFlowerColorRoot, ksys::act::ai::Ai)
public:
    explicit KorokFlowerColorRoot(const InitArg& arg);
    ~KorokFlowerColorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mKorokFlowerColorNum_m{};
    bool _40 = false;
    Unk_71012419b4 _48;
};

}  // namespace uking::ai
