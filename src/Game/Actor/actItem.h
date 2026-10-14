#pragma once

#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::act {
class Unk_7102357908;
}

namespace uking::act {

// Name from the CSV (Item::*; the namespace is a guess). Direct child of DynamicActor. Factory 0x71002c3a30:
// new(0xbb0) + inlined ctor (the ctor also exists out of line at 0x71002c3aa4). RTTI static: see data_symbols.
class Item : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(Item, DynamicActor)
public:
    explicit Item(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    // CSV m18 / m20.
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    bool shouldUnload(s32* a1) override;
    void m63() override;
    // CSV m64 / m69.
    void initMaybe() override;
    void calcMaybe() override;
    void m79() override;

    Unk_71025ae680* m159() override { return _b90; }

    /* 0xb90 */ Unk_71025ae680* _b90 = nullptr;
    /* 0xb98 */ Unk_7102357908* _b98 = nullptr;
    // Drop timer (IsDrop items): _ba0 chases _ba4 (GlobalParameter value); the damage manager is disabled meanwhile.
    /* 0xba0 */ f32 _ba0 = 0;
    /* 0xba4 */ f32 _ba4 = 0;
    /* 0xba8 */ bool _ba8 = true;
    /* 0xba9 */ bool _ba9 = false;  // set once the item is more than 0.05 away (XZ) from its placement position
};
KSYS_CHECK_SIZE_NX150(Item, 0xbb0);

}  // namespace uking::act
