#pragma once

#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokAnswerResponceRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokAnswerResponceRoot, ksys::act::ai::Ai)
public:
    explicit KorokAnswerResponceRoot(const InitArg& arg);
    ~KorokAnswerResponceRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

protected:
    void sub_7100457BB4();
    void sub_7100457EB8(const sead::Matrix34f& matrix, const sead::Vector3f& position);

    // map_unit_param at offset 0x38
    const float* mEffectDispSize_m{};
    // map_unit_param at offset 0x40
    const bool* mIsNoResponceSound_m{};
    // map_unit_param at offset 0x48
    sead::SafeString mEffectDispActorName_m{};
    // map_unit_param at offset 0x58
    const sead::Vector3f* mEffectDIspOffset_m{};
    ksys::act::ActorLinkConstDataAccess _60;
    bool _70{};
    u8 pad_0x71[0x7];
    bool _78{};
    bool _79{};
    Unk_71012419b4 _80;
    Unk_71012419b4 _a0;
};

}  // namespace uking::ai
