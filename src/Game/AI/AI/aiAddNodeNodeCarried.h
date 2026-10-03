#pragma once

#include "Game/AI/AI/aiAddCarriedBase.h"
#include "Game/AI/aiUnk_7102450058.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddNodeNodeCarried : public AddCarriedBase {
    SEAD_RTTI_OVERRIDE(AddNodeNodeCarried, AddCarriedBase)
public:
    explicit AddNodeNodeCarried(const InitArg& arg);
    ~AddNodeNodeCarried() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    ksys::act::ActorBind* m35() override;
    void m36() override;
    void m37(const sead::Matrix34f& mtx) override;
    bool m38() override;

protected:
    Unk_710244ed58 _c0;
    // static_param at offset 0x138
    sead::SafeString mMyNode_s{};
    // static_param at offset 0x148
    const sead::Vector3f* mNodeRotOffset_s{};
};
KSYS_CHECK_SIZE_NX150(AddNodeNodeCarried, 0x150);

}  // namespace uking::ai
