#include "KingSystem/XLink/xlinkXLink.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include <xlink2/xlink2UserInstanceSLink.h>

namespace ksys::xlink {

bool XLink::x_1() {
    if (_cc.isOnBit(9)) {
        if (_48 && _48->getEventList()->size() != 0)
            return true;
        if (_50 && _50->getEventList()->size() != 0)
            return true;
    }
    if (_48 && _48->getBitFlag().isOnBit(2))
        return true;
    if (_50 && _50->getBitFlag().isOnBit(2))
        return true;
    if (_48 && _48->isCurrentActionNeedToCalc())
        return true;
    if (_50 && _50->isCurrentActionNeedToCalc())
        return true;
    return false;
}

bool XLink::x_2() {
    if (_48 && _48->getEventList()->size() != 0)
        return false;
    if (_50 && _50->getEventList()->size() != 0)
        return false;
    return true;
}

}  // namespace ksys::xlink
