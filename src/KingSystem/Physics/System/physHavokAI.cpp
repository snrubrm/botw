#include "KingSystem/Physics/System/physHavokAI.h"
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

void HavokAI::sub_7100F8305C(NavMeshObjMaybe* obj) {
    obj->_a8 &= ~2u;
    obj->_a8 |= 1;
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}

void HavokAI::sub_7100F83118(NavMeshObjMaybe* obj) {
    obj->_a8 |= 4;
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}

void HavokAI::sub_7100F833A8(NavMeshObjMaybe* obj) {
    obj->_a8 &= ~1u;
    obj->_a8 |= 2;
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

bool HavokAI::startNavMeshSystemThread() {
    return _38->start();
}

}  // namespace ksys::phys
