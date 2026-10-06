#pragma once

#include "Game/AI/AI/aiGiantArmorRoot.h"
#include "Game/gameUnkRttiClasses.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act {
class Actor;
class BaseProcLink;
}  // namespace ksys::act

namespace uking::act {
class GiantArmor;
}

namespace uking::ai {

// Placeholder name (vtable 0x71023f36d8; RTTI functions 0x71003f5970 / 0x71003f5a3c, D0 0x71003f5a98): the object at
// GiantArmorAsWeakPoint + 0x38 whose address the GiantArmor keeps at `_c10`. Its virtual computes the damage scale and
// level of a hit on the armor.
class Unk_71023f36d8 : public Unk_71023f3710 {
    SEAD_RTTI_OVERRIDE(Unk_71023f36d8, Unk_71023f3710)
public:
    // The hit description passed to the virtual (placeholder; only the fields that it reads).
    struct Info {
        u8 _0[4];
        /* 0x04 */ s32 _4;
        /* 0x08 */ s32 level;
        /* 0x0c */ bool _c;
        u8 _d[0x18 - 0xd];
        /* 0x18 */ ksys::act::BaseProcLink* attacker;
    };

    explicit Unk_71023f36d8(ksys::act::Actor* actor);

    // 0x71003f5860
    virtual void m4(f32* out_scale, s32* out_level, const Info* info);

    act::GiantArmor* _8 = nullptr;
};

class GiantArmorAsWeakPoint : public GiantArmorRoot {
    SEAD_RTTI_OVERRIDE(GiantArmorAsWeakPoint, GiantArmorRoot)
public:
    explicit GiantArmorAsWeakPoint(const InitArg& arg);
    ~GiantArmorAsWeakPoint() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    Unk_71023f36d8 _38{mActor};
};

}  // namespace uking::ai
