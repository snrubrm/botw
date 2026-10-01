#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WholeDungeonRotateTag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WholeDungeonRotateTag, ksys::act::ai::Ai)
public:
    explicit WholeDungeonRotateTag(const InitArg& arg);
    ~WholeDungeonRotateTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34() { return false; }
    virtual bool m35() { return false; }
    virtual bool m36() { return false; }
    virtual bool m37() { return false; }
    virtual bool m38() { return _48 == _44; }
    virtual void m39() {}
    virtual void m40() {}
    virtual void m41() {}
    virtual void m42() {}
    virtual void m43(int x) {}
    virtual void m44();
    virtual void m45();

protected:
    // map_unit_param at offset 0x38
    const float* mTiltAngle_m{};
    f32 _40 = 0;
    int _44 = -1;
    int _48 = -1;
};
KSYS_CHECK_SIZE_NX150(WholeDungeonRotateTag, 0x50);

}  // namespace uking::ai
