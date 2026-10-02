#include "Game/gameResetter.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(Resetter)

bool Resetter::finishedReset() const {
    return _20 == 0;
}

}  // namespace uking
