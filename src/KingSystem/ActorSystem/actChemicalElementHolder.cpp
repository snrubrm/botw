#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actChemical.h"

namespace ksys::act {

// NON_MATCHING: the default SafeString initialization uses a different empty-string load.
Unk_71024dd490::CreateArg::CreateArg() : _0(0x400), _4(0x400), _18(nullptr) {}

void Unk_71024dd490::sub_7100D9AA84() {
    _c8 &= ~0x1f8;
    const auto lock = sead::makeScopedLock(_48);
    for (auto& chemical : mChemicals)
        chemical.sub_7100D8F0FC();
}

}  // namespace ksys::act
