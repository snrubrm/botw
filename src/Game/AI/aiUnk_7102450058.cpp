#include "Game/AI/aiUnk_7102450058.h"
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"

// NON_MATCHING: scheduling only (the original materialises 10.0f / -1.0f after the stores to
// +0x20 / +0x2c)
CarriedData::CarriedData(ksys::act::Actor* actor) : mActor(actor) {}

bool Unk_7102450298::init(sead::Heap* heap) {
    _30 = sub_7100F6D358(heap);
    return _30 != nullptr;
}

void Unk_7102450298::finalize() {
    if (_30) {
        ksys::phys::Constraint::destroy(_30);
        _30 = nullptr;
    }
}


void CarriedData::x_6() {
    if (auto* data = mActor->m100()) {
        if (sead::BitFlagUtil::countOnBit(data->_1d0) >= 1)
            data->sub_7100E504C0();
    }
}

void CarriedData::x_8() {
    auto* data = mActor->m100();
    if (!data || !(data->_1d8 & 4))
        return;
    u8 flags = data->_1d0;
    if (flags & 1) {
        if ((_2c & 1) || data->_100 == 2) {
            flags &= ~1;
            data->_1d0 = flags;
        }
    }
    if (sead::BitFlagUtil::countOnBit(flags) <= 0)
        x_12();
}

void CarriedData::x_12() {
    if (auto* data = mActor->m100()) {
        if (data->_1d8 & 4)
            data->sub_7100E5052C();
    }
}

void CarriedData::updateIsDroppedFlag() {
    _2c &= 0x7f;
    auto* drop_data = mActor->getDropData();
    if (drop_data && drop_data->isFlag1Set())
        return;
    if (mActor->isWaitRevivalForDrop())
        return;
    _2c |= 0x80;
}
