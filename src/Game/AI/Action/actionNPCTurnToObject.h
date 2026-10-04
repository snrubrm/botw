#pragma once

#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTurnToObject : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTurnToObject, ksys::act::ai::Action)
public:
    explicit NPCTurnToObject(const InitArg& arg);
    ~NPCTurnToObject() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710020a5e4 (declared only): the body of leave_ is out of line in the original.
    void sub_710020A5E4();
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mObjectId_d{};
    // dynamic_param at offset 0x28
    float* mTurnDirection_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mActorName_d{};
    int _40 = 0;
    sead::Vector3f _44;
    ksys::act::BaseProcLink _50;
    bool _60 = false;
    bool _61 = false;
};

}  // namespace uking::action
