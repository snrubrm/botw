#pragma once

#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CommonPickedItem : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CommonPickedItem, ksys::act::ai::Ai)
public:
    explicit CommonPickedItem(const InitArg& arg);
    ~CommonPickedItem() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual void m35();
    virtual const sead::SafeString& m36() { return mGetAttKeyName_s; }
    virtual void m37();
    virtual void m38();

protected:
    // static_param at offset 0x38
    const bool* mCanGetOnBurning_s{};
    // static_param at offset 0x40
    const bool* mIsControlNoticeDo_s{};
    // static_param at offset 0x48
    sead::SafeString mGetAttKeyName_s{};
    // map_unit_param at offset 0x58
    const bool* mIsPlayerPut_m{};
    // map_unit_param at offset 0x60
    sead::SafeString mDropTable_m{};
    // map_unit_param at offset 0x70
    sead::SafeString mDropActor_m{};
    // aitree_variable at offset 0x80
    int* mGetNumLeft_a{};
    Unk_71023e0020 _88{0x1800029};
    int _c8{};
    sead::Buffer<sead::FixedSafeString<64>> _d0;
    int _e0{};
};

}  // namespace uking::ai
