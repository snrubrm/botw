#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>

// Counter record: full ctor 127F4B4 and EventMgr1 allocation E48810 establish size 0xc8.
// The existing RTTI name follows the four-slot native table at 2518B60.
class Unk_7102518b60 {
    SEAD_RTTI_BASE(Unk_7102518b60)
public:
    Unk_7102518b60();
    virtual ~Unk_7102518b60();

    void sub_710127F594();
    bool sub_710127F648() const;
    void sub_710127F668(s16 value);
    void sub_710127F6C8();
    bool sub_710127F6F4(const sead::SafeString& actor_name,
                      const sead::SafeString& game_data_name, bool initialize);

    // Complete registration, update and independent manager consumers establish these fields.
    /* 0x08 */ sead::FixedSafeString<64> mGameDataName;
    /* 0x60 */ sead::FixedSafeString<64> mActorName;
    /* 0xb8 */ s16 mPendingCounts[3];
    /* 0xc0 */ s32 mCount;
};
static_assert(sizeof(Unk_7102518b60) == 0xc8);
