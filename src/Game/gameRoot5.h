#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <cstddef>
#include <heap/seadDisposer.h>
#include "Game/gameUnk_71024739f8.h"
#include "KingSystem/Utils/Types.h"

namespace uking {

// Name from the CSV (Root5::createInstance 0x71008bec78; sInstance 0x71025d1710). Holds the list of
// controller input sources (Unk_71024739f8::mListNode); Unk_710246d1e8 removes its source on
// destruction. Probably the input replay manager.
class Root5 {
    SEAD_SINGLETON_DISPOSER(Root5)
    Root5() { mSources.initOffset(offsetof(Unk_71024739f8, mListNode)); }
    // 0x71008bed18
    virtual ~Root5() {}

public:
    // 0x71008bed24
    void removeFromList(Unk_71024739f8* source);

private:
    sead::OffsetList<Unk_71024739f8> mSources;
};
KSYS_CHECK_SIZE_NX150(Root5, 0x40);

}  // namespace uking
