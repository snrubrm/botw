#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AppearNearTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AppearNearTarget, ksys::act::ai::Ai)
public:
    explicit AppearNearTarget(const InitArg& arg);
    ~AppearNearTarget() override;
    bool isChangeable() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34(sead::Vector3f* out);
    virtual void m35(sead::Vector3f* out);
    virtual bool m36(const sead::Vector3f& pos);
    virtual void m37(const sead::Vector3f& pos);
    virtual void m38(sead::Matrix34f* mtx, const sead::Vector3f& pos);
    // 0x710030dbfc (placeholder name)
    void changeToSpawnPrepare();
    // 0x710030dfec (placeholder name): once the fade screen is not opened, clears `_8e` and restarts the AS list.
    void sub_710030DFEC();
    // 0x710030db14 (placeholder name): when the actor has tag 0xa4c7ba34 (no name known) and the fade screen is opened,
    // sets `_8e` and restarts the AS list at 0.
    void sub_710030DB14();

protected:
    // static_param at offset 0x38
    const float* mDist_s{};
    // static_param at offset 0x40
    const float* mTeraDist_s{};
    // map_unit_param at offset 0x48
    const int* mNearCreateAppearID_m{};
    // aitree_variable at offset 0x50
    bool* mIsStopFallCheck_a{};
    int _58{};
    Unk_7102451c10 _60;
    f32 _88{};
    bool _8c{};
    bool _8d{};
    bool _8e{};
};

}  // namespace uking::ai
