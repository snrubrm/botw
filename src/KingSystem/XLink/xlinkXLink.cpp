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

void XLink::x_4(bool paused) {
    if (paused) {
        if (!_cc.isOnBit(8)) {
            sub_7101230FC8(true, true);
            _cc.setBit(8);
        }
    } else if (_cc.isOnBit(8)) {
        sub_7101230FC8(false, true);
        _cc.resetBit(8);
    }
}

void XLink::sleepELink() {
    if (_48 && !_48->getBitFlag().isOnBit(1)) {
        _48->postCalc();
        _48->sleep();
    }
}

void XLink::resetELinkEvents() {
    if (_48)
        _48->killAll();
}

}  // namespace ksys::xlink
