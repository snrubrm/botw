#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

// Placeholder names (the objects live in the sound TUs around 0x710100000..0x710102400; declared only).
struct Unk_SpotBgmHandle {
    // 0x710101d9a4
    void sub_710101D9A4();

    u8 _0[8];
};

// The spot BGM instance a SpotBgmTriggerAction creates in init_ (size 0x3c0; its deleting destructor is vtable slot 1).
class Unk_SpotBgmInstance {
public:
    virtual ~Unk_SpotBgmInstance();

    Unk_SpotBgmHandle _8;
    u8 _10[0x368 - 0x10];
    /* 0x368 */ u32 _368;  // MusicianSpotBgmTriggerAction::enter_ sets bit 0x400
    u8 _36c[0x3c0 - 0x36c];
};

// Placeholder name (SoundMgr::_30::_48).
struct Unk_SpotBgmMgr {
    // 0x710ffbbe4 (SpotBgmTriggerAction::enter_) / 0x710ffbca0 (leave_)
    void sub_710FFBBE4(Unk_SpotBgmInstance* instance);
    void sub_710FFBCA0(Unk_SpotBgmInstance* instance);
};

// 0x710ffd7cc (172 B; declared only): SoundMgr::_30->_48, or null.
Unk_SpotBgmMgr* sub_710FFD7CC();

namespace uking::action {

class SpotBgmTriggerAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SpotBgmTriggerAction, ksys::act::ai::Action)
public:
    explicit SpotBgmTriggerAction(const InitArg& arg);
    ~SpotBgmTriggerAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mSound_d{};
    // map_unit_param at offset 0x30
    const bool* mIsStopWithoutReductionY_m{};
    // map_unit_param at offset 0x38
    sead::SafeString mSound_m{};
    Unk_SpotBgmInstance* _48 = nullptr;
};
KSYS_CHECK_SIZE_NX150(SpotBgmTriggerAction, 0x50);

}  // namespace uking::action
