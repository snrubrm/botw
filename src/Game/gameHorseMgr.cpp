#include "Game/gameHorseMgr.h"

namespace uking {

bool HorseMgr::sub_7100E85334(const ksys::act::BaseProcLink& link) const {
    return mOwnedHorse == link;
}

}  // namespace uking
