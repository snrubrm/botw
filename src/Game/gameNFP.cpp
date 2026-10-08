#include "Game/gameNFP.h"
#include <prim/seadScopedLock.h>

NFP* NFP::sInstance;  // 0x710260c120

void NFP::insertFunctions(uking::Unk_710243b770* listener) {
    _30->sub_F48478(listener);
}

void NFP::eraseFunctions(uking::Unk_710243b770* listener) {
    _30->sub_F484CC(listener);
}

void NFP::sub_F45E1C(const s32* amiibo_id) {
    _30->sub_F4851C(amiibo_id);
}

void NFP::sub_F45E24(const s32* amiibo_id) {
    _30->sub_F48570(amiibo_id);
}

bool NFP::returnFalse() const {
    return false;
}

bool NFP::sub_F45DC8() const {
    return (_30->_194 & 0x200) != 0;
}

bool NFP::sub_F45DFC() const {
    return (_30->_194 & 0x800) != 0;
}

bool NFP::sub_F45BB8() const {
    if (!_30)
        return false;
    return u32(_30->_d4 - 3) > 1;
}

void NFP::sub_F45CF0() {
    auto* thread = _30;
    thread->_194 |= 0x800;
    auto& queue = thread->_108;
    auto lock = sead::makeScopedLock(queue.mCS);
    const s32 index = queue.mWriteIndex;
    queue.mWriteIndex = (index + 1) % 16;
    queue.mRequests[index] = 2;
}

void NFP::sub_F45D5C() {
    auto* thread = _30;
    thread->_194 |= 0x800;
    auto& queue = thread->_108;
    auto lock = sead::makeScopedLock(queue.mCS);
    const s32 index = queue.mWriteIndex;
    queue.mWriteIndex = (index + 1) % 16;
    queue.mRequests[index] = 3;
}
