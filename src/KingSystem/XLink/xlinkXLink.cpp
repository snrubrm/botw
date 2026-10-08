#include "KingSystem/XLink/xlinkXLink.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include <xlink2/xlink2UserInstanceSLink.h>

namespace ksys::xlink {

void XLink::sub_710123051C(aal::IAssetInfoReadable* reader) {
    if (_50)
        _50->setAssetInfoReader(reader);
}

bool XLink::sub_7101230714() {
    if (_48 && _48->getEventList()->size() > 0) {
        _48->fadeIfLoopEffect();
        _48->postCalc();
        return false;
    }
    return true;
}

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

void XLink::sub_71012311D8(bool paused) {
    sub_7101230FC8(paused, false);
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

void XLink::toggle(MaskBit bit) {
    if (!_73.isOnBit(bit))
        return;
    const bool was_set = !_73.isZero();
    _73.resetBit(bit);
    if (!was_set || !_73.isZero())
        return;
    if (_48)
        _48->setIsActive(true);
    if (_50)
        _50->setIsActive(true);
}

void XLink::setMask(MaskBit bit) {
    if (_73.isOnBit(bit))
        return;
    if (_73.isZero()) {
        _73.setDirect(sead::BitFlag8::makeMask(bit));
        sleep_();
    }
    _73.setBit(bit);
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

void XLink::sub_7101231468(u32 property, f32 value, bool force) {
    if (_48 && (force || _48->isPropertyAssigned(property)))
        _48->setPropertyValue(property, value);
    if (_50 && (force || _50->isPropertyAssigned(property)))
        _50->setPropertyValue(property, value);
}

}  // namespace ksys::xlink
