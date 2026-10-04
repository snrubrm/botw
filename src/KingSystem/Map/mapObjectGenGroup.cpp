#include "KingSystem/Map/mapObjectGenGroup.h"

namespace ksys::map {

bool GenGroup::sub_7100D50E44(bool a1) {
    if (a1) {
        _10.increment();
        return true;
    }
    if (mInitState == 3)
        return false;
    _14.increment();
    return true;
}

void GenGroup::sub_7100D50E90(bool a1) {
    if (a1) {
        _10.decrement();
        mInitState = 0;
        return;
    }
    _14.decrement();
    if (mHasCreateOrDeleteLinks)
        mInitState = 3;
    else if (mInitState == 2)
        mInitState = _18 != 0;
}

}  // namespace ksys::map
