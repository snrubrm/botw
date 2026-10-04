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
    // 0x7101255a0c / 0x7101255d50 (placeholder names): copy the pose of the linked actor (or of its bone `mKeyA`),
    // multiplied by `mMtx`, to the bone `mKeyB` of `proc`'s model, or (flag 4: no `mKeyB`) to `proc` itself. The first
    // one is used for entries with flag 1 (it sets the bone's local matrix and scale), the second one for entries
    // without it (it sets the bone's world matrix). They return false for the other kind of entry or if the entry
    // is not valid.
    bool sub_7101255A0C(BaseProc* proc);
    bool sub_7101255D50(BaseProc* proc);

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

    // Placeholder name: the position in an entry array (an index and the array); returned by bindAll.
    struct Cursor {
        s32 index;
        ActorBindEntry* entries;
    };
    // 0x71012561e8: binds every bone of every unit of `other`'s model (to the bone with the same name in
    // `actor`'s model) to the entries starting at `cursor` (until the set's `mCount` entries are used);
    // returns the cursor behind the last bound entry (placeholder name).
    Cursor bindAll(Actor* actor, Actor* other, Cursor cursor, bool flag);

    // inline-only in the original; name is a guess: sead::Buffer::operator()-style bounds-clamped access
    // (an out-of-range index selects entry 0). Inlined in the leave_ of HorseReinsDefaultAction /
    // HorseSaddleDefaultAction (both loop over their constant entry count with it).
    ActorBindEntry& getEntry(s32 idx) {
        if (mCount <= u32(idx))
            return mEntries[0];
        return mEntries[idx];
    }

    /* 0x28 */ u32 mCount;
    /* 0x30 */ ActorBindEntry* mEntries;
};
KSYS_CHECK_SIZE_NX150(ActorBindSet, 0x38);

}  // namespace ksys::act
