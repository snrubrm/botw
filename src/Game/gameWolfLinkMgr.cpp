#include "Game/gameWolfLinkMgr.h"
#include <limits>
#include "Game/Actor/actWolfLink.h"
#include "Game/gameRoot38.h"
#include "Game/gameUnk_71008ba8d8.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking {

// Flag names (initialised by the static initializer 0x7100683c6c; lane4 s85, placeholder names).
sead::SafeString sWolfLink_CurrentLife = "WolfLink_CurrentLife";
sead::SafeString sWolfLink_CurrentPos = "WolfLink_CurrentPos";
sead::SafeString sWolfLink_MaxLife = "WolfLink_MaxLife";
sead::SafeString sWolfLink_LastRecordedHearts = "WolfLink_LastRecordedHearts";
sead::SafeString sWolfLink_TodayFirstDetectedUID = "WolfLink_TodayFirstDetectedUID";
sead::SafeString sWolfLink_DiedToday = "WolfLink_DiedToday";
sead::SafeString sWolfLink_HasBeenUsed = "WolfLink_HasBeenUsed";

SEAD_SINGLETON_DISPOSER_IMPL(WolfLinkMgr)

// NON_MATCHING: written to emit the vtable; the original also resets _68 from a static id, deletes the _38 proc
// and disconnects mSlot explicitly
WolfLinkMgr::~WolfLinkMgr() {
    _28.reset();
    _80 = nullptr;
}

void WolfLinkMgr::init() {
    init_();
    ksys::gdt::Manager::instance()->addReinitCallback(mSlot);
}

void WolfLinkMgr::init_() {
    auto* gdm = ksys::gdt::Manager::instance();
    mCurrentLifeHandle = gdm->getS32Handle(sWolfLink_CurrentLife);
    mCurrentPosHandle = gdm->getVec3fHandle(sWolfLink_CurrentPos);
    mMaxLifeHandle = gdm->getS32Handle(sWolfLink_MaxLife);
    mDiedTodayHandle = gdm->getBoolHandle(sWolfLink_DiedToday);
}

bool WolfLinkMgr::sub_7100682CB4() const {
    return _60 == 2 && _80 && (_80->_1698 & 0x4000);
}

// NON_MATCHING: the original builds the flag as `1 << n` with n = 1 read back from a stack slot (probably a SEAD_ENUM
// bit index: sead::TypedBitFlag::makeMask); ours folds it to 2
bool WolfLinkMgr::sub_7100683088(bool a1) {
    if (_60 != 2 || !_80 || !_28.hasProc())
        return false;
    sead::BitFlag8 flags;
    if (a1)
        flags.setBit(1);
    const sead::Vector3f pos = _80->getMtx().getTranslation();
    return sub_7100682CE8(&pos, flags);
}

s32 WolfLinkMgr::sub_7100683120() {
    if (_28.hasProc() && _80) {
        if (auto* life = _80->getLife())
            return *life;
        return 1;
    }
    return -1;
}

s32 WolfLinkMgr::sub_7100683174() {
    if (_28.hasProc() && _80)
        return _80->getMaxLife();
    return -1;
}

sead::Vector3f WolfLinkMgr::sub_71006831BC() const {
    if (_28.hasProc() && _80)
        return _80->getMtx().getTranslation();
    const f32 nan = std::numeric_limits<f32>::quiet_NaN();
    return {nan, nan, nan};
}

bool WolfLinkMgr::sub_710068367C() {
    if (_60 == 1)
        return false;
    return _28.hasProc();
}

bool WolfLinkMgr::sub_7100683698() {
    if (_60 == 1)
        return false;
    return !_28.hasProc();
}

bool WolfLinkMgr::sub_7100683410() {
    auto* gdm = ksys::gdt::Manager::instance();
    const f32 nan = std::numeric_limits<f32>::quiet_NaN();
    sead::Vector3f pos{nan, nan, nan};
    s32 life = -1;
    if (!gdm)
        return false;
    if (!gdm->getVec3f(mCurrentPosHandle, &pos))
        return false;
    if (!gdm->getS32(mCurrentLifeHandle, &life))
        return false;
    if (ksys::util::isVectorInvalid(pos))
        return false;
    if (life < 1)
        return false;
    return sub_7100682CE8(&pos, {});
}

bool WolfLinkMgr::sub_7100683214(ksys::act::Actor* actor) {
    if (_60 != 2)
        return false;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!_28.hasProc() || !ksys::act::acquireActor(&_28, &accessor))
        return false;
    actor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0), actor, true);
    return true;
}

void WolfLinkMgr::sub_71006832C0() {
    if (_60 != 5 && _60 != 2)
        return;
    if (_80) {
        auto* gdm = ksys::gdt::Manager::instance();
        const sead::Vector3f pos = _80->getMtx().getTranslation();
        const s32* life_ptr = _80->getLife();
        const s32 life = life_ptr ? *life_ptr : 1;
        if (gdm->setS32(life, mCurrentLifeHandle) && gdm->setVec3f(pos, mCurrentPosHandle))
            gdm->setBool(life < 1, mDiedTodayHandle);
    }
    if (const s32* life = _80->getLife()) {
        const s32 value = *life;
        sub_7100682F80(_80, false);
        if (value < 1)
            return;
    } else {
        sub_7100682F80(_80, false);
    }
    _60 = 6;
}

void WolfLinkMgr::sub_71006833C8() {
    if (_60 != 6)
        return;
    if (eventMgrHasActiveEvent()) {
        _60 = 7;
        return;
    }
    sub_7100683410();
}

void WolfLinkMgr::sub_7100683790() {
    if (!_38.isAllocatedOrFailed())
        return;
    if (_38.isProcReady()) {
        auto* proc = _38.releaseAndWakeProc();
        if (auto* wolf_link = sead::DynamicCast<act::WolfLink>(proc)) {
            sub_7100683970(wolf_link);
            _60 = 2;
        }
    } else if (_38.hasProcCreationFailed()) {
        _38.deleteProcIfFailed();
        _60 = 3;
    }
}

void WolfLinkMgr::sub_710068386C() {
    if (!_80) {
        _60 = 0;
        return;
    }
    if (!_28.hasProc()) {
        sub_7100682F80(_80, false);
        return;
    }
    if (_80) {
        auto* gdm = ksys::gdt::Manager::instance();
        const sead::Vector3f pos = _80->getMtx().getTranslation();
        const s32* life_ptr = _80->getLife();
        const s32 life = life_ptr ? *life_ptr : 1;
        if (gdm->setS32(life, mCurrentLifeHandle) && gdm->setVec3f(pos, mCurrentPosHandle))
            gdm->setBool(life < 1, mDiedTodayHandle);
    }
    if (sub_7100683548()) {
        _60 = 5;
        _80->get68c() = true;
    }
}

void WolfLinkMgr::postCalc() {
    if (Root38::instance()->doNotFreezeScene())
        return;

    switch (_60) {
    case 1:
        sub_7100683790();
        break;
    case 2:
        sub_710068386C();
        break;
    case 5:
        if (_80) {
            if (sub_7100683548())
                break;
            _80->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
            _80->get68c() = false;
            _60 = 2;
        } else {
            _60 = 0;
        }
        break;
    case 7:
        if (!eventMgrHasActiveEvent())
            sub_7100683410();
        break;
    default:
        break;
    }
}

}  // namespace uking
