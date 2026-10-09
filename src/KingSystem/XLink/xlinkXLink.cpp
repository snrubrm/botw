#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Sound/sndMiiSound.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "Game/gameScene.h"
#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include <aal/aalSoundSource.h>
#include <prim/seadScopedLock.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2SystemSLink.h>
#include <xlink2/xlink2ResourceAccessorSLink.h>
#include <xlink2/xlink2UserInstanceELink.h>
#include <xlink2/xlink2UserInstanceSLink.h>

namespace ksys::xlink {

XLink::RebuildArg::RebuildArg() = default;

void XLink::sub_7101230100(const RebuildArg& arg) {
    if (_48) {
        xlink2::UserInstance::RebuildArg rebuild_arg;
        rebuild_arg.rootMtx.setRawMtx(arg.rootMtx, 0);
        rebuild_arg.rootPos = arg.rootPos;
        rebuild_arg._18 = arg._10;
        _48->rebuild(rebuild_arg);
    }
    if (_50) {
        xlink2::UserInstance::RebuildArg rebuild_arg;
        rebuild_arg.rootMtx.setRawMtx(arg.rootMtx, 0);
        rebuild_arg.rootPos = arg.rootPos;
        rebuild_arg._18 = arg._10;
        _50->rebuild(rebuild_arg);
    }
}

as::ASList* XLink::getASList() const {
    return mActor ? mActor->getASList() : nullptr;
}

void XLink::sub_710123051C(aal::IAssetInfoReadable* reader) {
    if (_50)
        _50->setAssetInfoReader(reader);
}

// NON_MATCHING: fading-list bound scheduling and loop register allocation.
void XLink::sub_71012305AC() {
    for (auto& event : *_50->getEventList()) {
        for (auto& executor : event.getAliveAssetExecutors()) {
            auto* handle = static_cast<xlink2::AssetExecutorSLink&>(executor).getHandle();
            if (!handle->isPaused() && !handle->isVirtualized()) {
                auto* source = handle->getSoundSource();
                if (!source || !source->isInnerPaused())
                    continue;
            }
            handle->stop(-1.0f, 0.0f);
        }
        for (auto& executor : event.getFadeBySystemExecutors()) {
            auto* handle = static_cast<xlink2::AssetExecutorSLink&>(executor).getHandle();
            if (!handle->isPaused() && !handle->isVirtualized()) {
                auto* source = handle->getSoundSource();
                if (!source || !source->isInnerPaused())
                    continue;
            }
            handle->stop(-1.0f, 0.0f);
        }
    }
}

// NON_MATCHING: fading-list bound scheduling, loop registers and lock stack slot.
void XLink::sub_7101230968() {
    auto* user = _50;
    if (!user)
        return;
    sead::ScopedLock<xlink2::ILockProxy> lock(xlink2::SystemSLink::sLockProxy);
    for (auto& event : *user->getEventList()) {
        for (auto& executor : event.getAliveAssetExecutors()) {
            auto* handle = static_cast<xlink2::AssetExecutorSLink&>(executor).getHandle();
            if (handle->getSoundGroupName().findIndex("Voice") != -1)
                handle->stop(-1.0f, 0.0f);
        }
        for (auto& executor : event.getFadeBySystemExecutors()) {
            auto* handle = static_cast<xlink2::AssetExecutorSLink&>(executor).getHandle();
            if (handle->getSoundGroupName().findIndex("Voice") != -1)
                handle->stop(-1.0f, 0.0f);
        }
    }
}

void XLink::sub_7101230E18() {
    if (_50) {
        _50->searchAndEmit("Disappear_Ancient");
        sub_7101230968();
        _cc.setBit(25);
    }
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

void XLink::sub_7101230FC8(bool paused, bool skip_environment) {
    if (!_73.isZero())
        return;
    auto* user = _50;
    if (!user || user->getEventList()->size() == 0)
        return;
    auto* groups = aal::SystemAccessor::getGroupMgr();
    if (!groups)
        return;
    auto* world = groups->findGroup("World");
    aal::Group* env = nullptr;
    aal::Group* chemical = nullptr;
    if (skip_environment) {
        env = groups->findGroup("Env");
        chemical = groups->findGroup("Chemical");
    }
    sead::ScopedLock<xlink2::ILockProxy> lock(xlink2::SystemSLink::sLockProxy);
    for (auto& event : *user->getEventList()) {
        for (auto& executor : event.getAliveAssetExecutors()) {
            auto* handle = static_cast<xlink2::AssetExecutorSLink&>(executor).getHandle();
            auto* group = handle->getSoundGroup();
            if (aal::GroupMgr::isUnderAncestorOrSelf(group, env) ||
                aal::GroupMgr::isUnderAncestorOrSelf(group, chemical) ||
                !aal::GroupMgr::isUnderAncestorOrSelf(group, world))
                continue;
            if (_50->getResourceAccessor().getCustomParamValueBool(12, *executor.getAssetCallTable()))
                continue;
            handle->pause(sead::BitFlag8(2), paused, 0.1f);
        }
    }
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

void XLink::sleep(MaskBit bit) {
    if (_73.isOnBit(bit))
        return;
    if (_73.isZero()) {
        if (getSceneStatus() == 4) {
            _73.setBit(bit);
            sleep_();
        } else {
            Manager::instance()->queueSleep(this);
        }
    }
    _73.setBit(bit);
}

void XLink::sleep_() {
    if (_73.isZero())
        return;
    if (_48 && !_48->getBitFlag().isOnBit(1)) {
        _48->postCalc();
        _48->sleep();
    }
    if (!_50 || _50->getBitFlag().isOnBit(1))
        return;
    sub_71012305AC();
    _50->postCalc();
    _50->sleep();
    if (mMiiSound && mMiiSound->hasRequestedLoad())
        mMiiSound->requestUnloadMaybe();
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

void XLink::sub_71012313DC(u32 property, s32 value, bool force) {
    if (_48 && (force || _48->isPropertyAssigned(property)))
        _48->setPropertyValue(property, value);
    if (_50 && (force || _50->isPropertyAssigned(property)))
        _50->setPropertyValue(property, value);
}

void XLink::sub_7101231468(u32 property, f32 value, bool force) {
    if (_48 && (force || _48->isPropertyAssigned(property)))
        _48->setPropertyValue(property, value);
    if (_50 && (force || _50->isPropertyAssigned(property)))
        _50->setPropertyValue(property, value);
}

}  // namespace ksys::xlink
