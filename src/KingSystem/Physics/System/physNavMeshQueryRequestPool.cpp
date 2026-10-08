#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/System/physHavokAI.h"

namespace ksys::phys {

void NavMeshQueryRequestPool::sub_71012A9EE8(Unk_7102372790* query) {
    query->_9 = true;
    if (_180.push(query))
        query->_8 = true;
}

void NavMeshQueryRequestPool::sub_71012AA000(Unk_7102372790* query) {
    query->_9 = true;
    if (_180.push(query))
        query->_8 = true;
}

bool NavMeshQueryRequestPool::sub_71012A9F68(Unk_7102372790* query) {
    if (_180.push(query)) {
        query->_8 = true;
        return true;
    }
    return false;
}

bool NavMeshQueryRequestPool::sub_71012AA080(Unk_7102372790* query) {
    if (_180.push(query)) {
        query->_8 = true;
        return true;
    }
    return false;
}

void NavMeshQueryRequestPool::sub_71012AA118(Unk_7102372790* query) {
    auto lock = sead::makeScopedLock(_8);
    if (_198 == query)
        _198 = nullptr;
    _108.remove(query);
    _120.remove(query);
}

void NavMeshQueryRequestPool::sub_71012AA1F0(NavMeshCharacter* nav) {
    auto lock = sead::makeScopedLock(_48);
    _138.erase(nav);
}

}  // namespace ksys::phys
