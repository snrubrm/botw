#pragma once

#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>

// Existing global identity from the location-record table at 0x710249c5e8.
// Manager::parseLocations fills these fields; UiSubsys1's map-marker producer
// at 0x710095c0a8 reads the position at +0x18 from the same pooled records.
class Unk_710249c5e8 {
    SEAD_RTTI_BASE(Unk_710249c5e8)
public:
    virtual ~Unk_710249c5e8();

    /* 0x08 */ s32 mShowLevel = -1;
    /* 0x0c */ s32 mType = -1;
    /* 0x10 */ const char* mMessageId = nullptr;
    /* 0x18 */ sead::Vector3f mPosition = {0, 0, 0};
};
static_assert(sizeof(Unk_710249c5e8) == 0x28);
static_assert(offsetof(Unk_710249c5e8, mPosition) == 0x18);
