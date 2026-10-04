#pragma once

#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::act {

// Name from the CSV (Item::*; the namespace is a guess). Direct child of DynamicActor. Factory 0x71002c3a30:
// new(0xbb0) + inlined ctor (the ctor also exists out of line at 0x71002c3aa4). RTTI static: see data_symbols.
// TODO: incomplete (m18 / m20 / m63 / m64 / m69 / m79 / shouldUnload not written).
class Item : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(Item, DynamicActor)
public:
    explicit Item(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    Unk_71025ae680* m159() override { return _b90; }

    /* 0xb90 */ Unk_71025ae680* _b90 = nullptr;
    /* 0xb98 */ void* _b98 = nullptr;
    /* 0xba0 */ u32 _ba0 = 0;
    /* 0xba4 */ u32 _ba4 = 0;
    /* 0xba8 */ u8 _ba8 = 1;
    /* 0xba9 */ u8 _ba9 = 0;
};
KSYS_CHECK_SIZE_NX150(Item, 0xbb0);

}  // namespace uking::act
