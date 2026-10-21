#include "Game/gameRoot5.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(Root5)

void Root5::removeFromList(Unk_71024739f8* source) {
    mSources.erase(source);
}

}  // namespace uking
