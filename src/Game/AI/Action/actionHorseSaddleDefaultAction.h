#pragma once

#include "Game/Actor/actHorseBindSets.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseSaddleDefaultAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseSaddleDefaultAction, ksys::act::ai::Action)
public:
    explicit HorseSaddleDefaultAction(const InitArg& arg);
    ~HorseSaddleDefaultAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // Placeholder names (slots 32 / 33; 0x7100e57b80 / 0x7100e57b8c): the saddle's bind rotation and translation
    // (aiUnk_7101ec1800.h). HorseSaddleBindAction selects between the two pairs with its `IsZelda` param (Zelda: the
    // pair at 0x7101ec1800 / 0x7101ec180c).
    virtual const sead::Vector3f* m32();
    virtual const sead::Vector3f* m33();

    /* 0x20 */ act::Unk_71024e9710 _20;
    /* 0x1a38 */ u8 _1a38 = 0;
};

}  // namespace uking::action
