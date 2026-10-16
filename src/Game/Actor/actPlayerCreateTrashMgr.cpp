#include "Game/Actor/actPlayerCreateMgr.h"

namespace uking::act {

CreatePlayerTrashActorMgr::~CreatePlayerTrashActorMgr() {
    _28.finish();
}

bool CreatePlayerTrashActorMgr::sub_7100667974() const {
    return _40 == 0;
}

}  // namespace uking::act
