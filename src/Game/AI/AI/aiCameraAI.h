#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

// Unnamed secondary base of CameraAI (vtable 0x7102459708): a virtual destructor and a pointer to the
// owner AI. The ctor (0x7100791ca8) and the vtable functions live in another translation unit.
class Unk_7102459708 {
public:
    explicit Unk_7102459708(ksys::act::ai::Ai* owner);
    virtual ~Unk_7102459708() = default;

    ksys::act::ai::Ai* mOwner;
};

namespace uking::ai {

class CameraAI : public ksys::act::ai::Ai, public Unk_7102459708 {
    SEAD_RTTI_OVERRIDE(CameraAI, ksys::act::ai::Ai)
public:
    explicit CameraAI(const InitArg& arg);
    ~CameraAI() override = default;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34(sead::Heap* heap) { return true; }
    virtual void m35(ksys::act::ai::InlineParamPack* params) {}
    virtual void m36() {}
    virtual void m37() {}
    virtual void m38() {}

protected:
};

}  // namespace uking::ai
