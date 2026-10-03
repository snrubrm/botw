#include "Game/Actor/actRideable.h"

namespace uking::act {

// In its own file: the original's RideableBase destructor calls this out-of-line (it is in another
// translation unit).
RideableBase::S2::~S2() {}

}  // namespace uking::act
