#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;

// Placeholder name (ctor 0x7101255764, TU 0x7101255680 - 0x7101256800): one bind of an ActorBindSet. Links an
// actor and two bones (`mKeyA` in the actor's model, `mKeyB` in the model of the second actor passed to set()).
// Size 0xb8. Flag bits of `mFlags`: 1 = set by the last argument of set(); 2 / 4 = the corresponding bone name was
// empty (no bone key).
struct ActorBindEntry {
    ActorBindEntry();

    // 0x7101255920: whether the linked actor (looked up with `other_proc`) has a model and valid bone keys.
    bool isValid(BaseProc* other_proc) const;
    // 0x71012557ac (the parameter names are guesses).
    bool set(Actor* actor, const sead::SafeString& bone_a, Actor* other, const sead::SafeString& bone_b,
             const sead::Matrix34f* mtx, bool flag);
    // 0x71012558f4
    void reset();

    /* 0x00 */ BaseProcLink mLink;
    /* 0x10 */ gsys::BoneAccessKeyEx mKeyA;
    /* 0x48 */ gsys::BoneAccessKeyEx mKeyB;
    /* 0x80 */ sead::Matrix34f mMtx = sead::Matrix34f::ident;
    /* 0xb0 */ u8 mFlags = 0;
};
KSYS_CHECK_SIZE_NX150(ActorBindEntry, 0xb8);

// Placeholder name (vtable 0x7102516f88, ctor 0x710125603c, D1 / D0 0x71012560a0 / 0x7101256140): an ActorBind that
// owns an array of `ActorBindEntry`. Without its own RTTI. Subclasses with inline storage (HorseObject's
// 16 entries) set `mEntries` to null before their members are destroyed.
class ActorBindSet : public ActorBind {
public:
    ActorBindSet(int count, ActorBindEntry* entries);
    ~ActorBindSet() override;

    // 0x71012639c / 0x71012563f8 / 0x7101256444 / 0x7101256534 / 0x7101256624 / 0x7101256714 (declared only)
    bool m4(BaseProc* proc) override;
    bool m5(BaseProc* proc) override;
    bool m6(BaseProc* proc) override;
    bool m7(BaseProc* proc) override;
    bool m8(BaseProc* proc) override;
    void m9(BaseProc* proc) override;

    // 0x7101256354: resets every entry.
    void resetAll();

    /* 0x28 */ u32 mCount;
    /* 0x30 */ ActorBindEntry* mEntries;
};
KSYS_CHECK_SIZE_NX150(ActorBindSet, 0x38);

}  // namespace ksys::act
