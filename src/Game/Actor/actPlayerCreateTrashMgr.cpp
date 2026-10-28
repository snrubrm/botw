#include "Game/Actor/actPlayerCreateMgr.h"

namespace uking::act {

SEAD_SINGLETON_DISPOSER_IMPL(CreatePlayerTrashActorMgr)

CreatePlayerTrashActorMgr::~CreatePlayerTrashActorMgr() {
    _28.finish();
}

bool CreatePlayerTrashActorMgr::sub_7100667974() const {
    return _40 == 0;
}

void CreatePlayerTrashActorMgr::sub_7100667970() {}

}  // namespace uking::act
