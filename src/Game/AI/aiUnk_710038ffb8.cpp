#include "Game/AI/aiUnk_710038ffb8.h"
#include "Game/AI/aiUnk_7102357d20.h"

Unk_710038ffb8::~Unk_710038ffb8() {
    // Keep the original vtable store, as in upstream GameDataFlagSelector::~GameDataFlagSelector()
    // { ; } (commit 96101229).
    ;
}

Unk_71023e7d28::~Unk_71023e7d28() = default;

Unk_71023e7b98::~Unk_71023e7b98() = default;
Unk_71023e7be8::~Unk_71023e7be8() = default;
Unk_71023e7c10::~Unk_71023e7c10() = default;

s32 Unk_710038ffb8::sub_7100390A90() {
    _3c8 = 0x10;
    *_8 = 0;
    _3a0.reset();
    return 0;
}

void Unk_710038ffb8::sub_7100392230() {
    _10->getStaticParam(&_18, "ReactDelayMin");
    _10->getStaticParam(&_20, "ReactDelayMax");
    _10->getStaticParam(&_28, "DanceReactRand");
    _10->getStaticParam(&_30, "TalkEndDelayMin");
    _10->getStaticParam(&_38, "TalkEndDelayMax");
    _10->getStaticParam(&_40, "TalkChangeViewTargetTimerMin");
    _10->getStaticParam(&_48, "TalkChangeViewTargetTimerMax");
    _10->getStaticParam(&_50, "FortressTag");
    _10->getAITreeVariable(&_8, "IsNextActionReserved");
}
