#include "KingSystem/Physics/System/physHavokAI.h"
#include <thread/seadThread.h>
#include <thread/seadThreadUtil.h>
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace ksys::phys {

void HavokAI::destroyQuery(Unk_7102372790* query) {
    _40->sub_71012A9EE8(query);
}

void HavokAI::sub_7100F83A94(Unk_7102372790* query) {
    _40->sub_71012AA000(query);
}

void HavokAI::sub_7100F83A9C(Unk_7102372790* query) {
    _40->sub_71012AA080(query);
}

bool HavokAI::submitQuery(Unk_7102372790* query) {
    return _40->sub_71012A9F68(query);
}

void HavokAI::sub_7100F82BCC(NavMeshCharacter* nav) {
    nav->_220 &= ~2u;
    nav->_220 |= 1;
    HavokAI* pending = nav->_20.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_138.push(nav);
}

void HavokAI::sub_7100F82C88(NavMeshCharacter* nav) {
    nav->inlineReset();
    nav->_220 &= ~1u;
    nav->_220 |= 2;
    HavokAI* pending = nav->_20.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_138.push(nav);
}

void HavokAI::sub_7100F8305C(NavMeshObjMaybe* obj) {
    obj->_a8.reset(NavMeshObjMaybe::Flag::_2);
    obj->_a8.set(NavMeshObjMaybe::Flag::_1);
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}

void HavokAI::sub_7100F83118(NavMeshObjMaybe* obj) {
    obj->_a8.set(NavMeshObjMaybe::Flag::_4);
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}

void HavokAI::sub_7100F833A8(NavMeshObjMaybe* obj) {
    obj->_a8.reset(NavMeshObjMaybe::Flag::_1);
    obj->_a8.set(NavMeshObjMaybe::Flag::_2);
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}

void HavokAI::sub_7100F83580(NavMeshObj2Maybe* obj) {
    obj->_80 &= ~2u;
    obj->_80 |= 1;
    HavokAI* pending = obj->_78.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_168.push(obj);
}

void HavokAI::sub_7100F8363C(NavMeshObj2Maybe* obj) {
    obj->_80 |= 4;
    HavokAI* pending = obj->_78.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_168.push(obj);
}

// NON_MATCHING: the original orders the two flag updates differently on each path (b: clear 0x10 first; !b: clear 8
// first); matches with `if (on) { reset(_10); change(_8, on); } else { reset(_8); change(_10, !on); }`
void HavokAI::sub_7100F831C0(NavMeshObjMaybe* obj, bool on) {
    obj->_a8.change(NavMeshObjMaybe::Flag::_10, !on);
    obj->_a8.change(NavMeshObjMaybe::Flag::_8, on);
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}

// NON_MATCHING: same as sub_7100F831C0 (flags 0x40 / 0x20)
void HavokAI::sub_7100F832B4(NavMeshObjMaybe* obj, bool on) {
    obj->_a8.change(NavMeshObjMaybe::Flag::_40, !on);
    obj->_a8.change(NavMeshObjMaybe::Flag::_20, on);
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}

void HavokAI::sub_7100F857F4(Unk_NavMeshCallback* callback, const sead::BoundBox3f* aabb) {
    if (sead::ThreadMgr::instance()->getCurrentThread() != _38) {
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(
            sead::ThreadMgr::instance()->getCurrentThread()->getPriority()));
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(_38->getPriority()));
    }

    if (_90.tryLock()) {
        sub_7100F854C4(callback, aabb);
        _90.unlock();
    } else if (_c8.tryLock()) {
        sub_7100F8565C(callback, aabb);
        _c8.unlock();
    }
}

bool HavokAI::startNavMeshSystemThread() {
    return _38->start();
}

void HavokAI::sendStepMessageToNavMeshSysThread(f32 dt) {
    _38->sub_7100F895FC(dt);
}

void HavokAI::sub_7100F8185C() {
    _38->_10c = false;
}

}  // namespace ksys::phys
