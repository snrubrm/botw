#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Name from the CSV (SoundSystemActor::*; the namespace is a guess). Factory 0x710105a8c0: new(0x840) + inlined ctor (sets
// _1c0 = 15). RTTI static 0x7102610758.
// TODO: incomplete (no members / further overrides known yet).
class SoundSystemActor : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(SoundSystemActor, ksys::act::Actor)
public:
    explicit SoundSystemActor(const CreateArg& arg);
    ~SoundSystemActor() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
};
KSYS_CHECK_SIZE_NX150(SoundSystemActor, 0x840);

}  // namespace uking::act
