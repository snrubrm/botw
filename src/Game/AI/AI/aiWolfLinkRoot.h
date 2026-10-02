#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/VFRValue.h"

namespace ksys::res {
class GParamListObjectWolfLink;
}

namespace uking::act {
class WolfLink;
}

namespace uking::ai {

// vtable 0x7102432d40: damage callback embedded in WolfLinkRoot (no RTTI of its own; `call`
// 0x710060b8d8 reads its last argument as an object of an unknown RTTI class (GOT 0x7102579518)).
class Unk_7102432d40 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x7102432d78: damage callback embedded in WolfLinkRoot (no RTTI of its own; `call`
// 0x710060ba10 calls the unnamed 0x71002c802c). The link is acquired with the owner actor.
class Unk_7102432d78 : public dmg::DamageCallback {
public:
    explicit Unk_7102432d78(ksys::act::Actor* actor) { _28.acquire(actor, false); }

    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    ksys::act::BaseProcLink _28;
};

class WolfLinkRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkRoot, ksys::act::ai::Ai)
public:
    explicit WolfLinkRoot(const InitArg& arg);
    ~WolfLinkRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    virtual bool m34();
    virtual bool m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();

    void sub_710060B508();
    void sub_710060B700();

protected:
    sead::Vector3f _38{0, 0, 0};
    ksys::VFRValue _44;
    sead::Vector3f _50{0, 0, 0};
    Unk_7102451ba0 _60;
    Unk_7102432d40 _88;
    Unk_7102432d78 _b0{mActor};
    act::WolfLink* _e8{};
    const ksys::res::GParamListObjectWolfLink* _f0{};
    bool _f8 = false;
};
KSYS_CHECK_SIZE_NX150(WolfLinkRoot, 0x100);

}  // namespace uking::ai
