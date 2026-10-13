#include "KingSystem/ActorSystem/actDebug.h"
#include <prim/seadSafeString.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(ActorDebug)

const char* ActorDebug::getNullStr(HashUnused*) {
    return &sead::SafeString::cNullChar;
}

}  // namespace ksys::act

// NON_MATCHING: placeholder destructor; the original (0x7100d2b1ac) also destroys members or bases
// this class does not declare yet.
Unk_71024d8fa8::~Unk_71024d8fa8() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100d2b414) also destroys members or bases
// this class does not declare yet.
Unk_71024d8ff0::~Unk_71024d8ff0() = default;
