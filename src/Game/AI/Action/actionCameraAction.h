#pragma once

#include <xlink2/xlink2HandleSLink.h>
#include "Game/Actor/actCamera.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraAction : public ksys::act::ai::Action, public Unk_7102459708 {
    SEAD_RTTI_OVERRIDE(CameraAction, ksys::act::ai::Action)
public:
    explicit CameraAction(const InitArg& arg);
    ~CameraAction() override = default;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // m32, m35, m38, m39 and the destructor are inline (the original emits them in the first
    // subclass translation unit, CameraAbyss's).
    virtual bool m32(sead::Heap* heap) { return true; }
    virtual void m33();
    virtual void m34();
    virtual void m35() {}
    virtual void m36();
    virtual u64 m37();
    virtual int m38() { return 0; }
    virtual bool m39() { return true; }
    virtual void m40();
    virtual void m41();

    // 0x710074b590 / 0x710074b838: save the camera's six states into `states` / restore them.
    void sub_710074B590(act::Unk_71009214b8* states);
    void sub_710074B838(const act::Unk_71009214b8* states);
    // 0x710074bcb4: fades _30 if it was emitted.
    void sub_710074BCB4();

    xlink2::HandleSLink _30;
    // static_param at offset 0x40
    const bool* mBowFlag_s{};
    u8 _48 = 0;
};

}  // namespace uking::action
