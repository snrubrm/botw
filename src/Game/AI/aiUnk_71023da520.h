#pragma once

#include "Game/AI/aiActorLink.h"

// Reference-counted object behind the "BeamActorLink" AI tree variable (BeamosCarried). Placeholder
// name = vtable address (0x71023da520; D2 is ActorLink's, D0 0x710032990c, RTTI functions
// 0x7100329790 / 0x71003298b0; RTTI static 0x71025b7b40). Created by
// Unk_71025afb58Ref<Unk_71023da520>::acquire (0x71003294c0).
class Unk_71023da520 : public ActorLink {
    SEAD_RTTI_OVERRIDE(Unk_71023da520, ActorLink)
public:
    /* 0x18 */ s32 mRefCount = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71023da520, 0x20);
