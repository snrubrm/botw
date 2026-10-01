#include "Game/Actor/actUnk_7100d3cd74.h"
#include <basis/seadNew.h>
#include <codec/seadHashCRC32.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::act {

inline Unk_7100d3cd74::Unk1* Unk_7100d3cd74::find(const sead::SafeString& name) const {
    const u32 hash = sead::HashCRC32::calcStringHash(name.cstr());
    for (auto* entry : mList) {
        if (entry->mNameHash == hash)
            return entry;
    }
    return nullptr;
}

Unk_7100d3cd74::Unk_7100d3cd74(ksys::act::Actor* actor) : mActor(actor) {}

Unk_7100d3cd74::~Unk_7100d3cd74() {
    mActor = nullptr;
    for (auto& node : mList.robustRange()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&node.mData->mLink, &accessor);
        auto* data = node.mData;
        mList.erase(&node);
        delete data;
    }
}

void Unk_7100d3cd74::sub_7100D3CE30() {
    for (auto& node : mList.robustRange()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&node.mData->mLink, &accessor);
        auto* data = node.mData;
        mList.erase(&node);
        delete data;
    }
}

bool Unk_7100d3cd74::sub_7100D3CED8(const sead::SafeString& name, sead::Heap* heap) {
    Unk1* data = find(name);

    if (data) {
        ++data->mRefCount;
        return true;
    }

    data = new (heap) Unk1;
    if (!data)
        return false;
    data->mNameHash = sead::HashCRC32::calcStringHash(name.cstr());
    mList.pushBack(&data->mListNode);
    return true;
}

// NON_MATCHING: the MessageType temporary is at a different stack offset
bool Unk_7100d3cd74::sub_7100D3CFEC(const sead::SafeString& name) {
    Unk1* data = find(name);

    if (!data)
        return false;

    if (--data->mRefCount == 0) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&data->mLink, &accessor)) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x300000f),
                                nullptr, false);
        }
        mList.erase(&data->mListNode);
        delete data;
    }
    return true;
}

bool Unk_7100d3cd74::sub_7100D3D108(const sead::SafeString& name, ksys::act::BaseProc* proc) {
    Unk1* data = find(name);
    if (!data)
        return false;

    if (data->mLink.hasProc() && !data->mLink.hasProcById(proc)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&data->mLink, &accessor);
        return false;
    }

    data->mLink.acquire(proc, false);
    return true;
}

bool Unk_7100d3cd74::sub_7100D3D1E0(const sead::SafeString& name,
                                    const ksys::act::BaseProcLink& link) {
    Unk1* data = find(name);
    if (!data)
        return false;

    if (data->mLink.hasProc() && data->mLink != link) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&data->mLink, &accessor);
        return false;
    }

    data->mLink = link;
    return true;
}

ksys::act::BaseProcLink& Unk_7100d3cd74::getActorPartsActor(const sead::SafeString& name) {
    Unk1* data = find(name);

    if (data)
        return data->mLink;
    return ksys::act::getDummyBaseProcLink();
}

bool Unk_7100d3cd74::sub_7100D3D2B4(const sead::SafeString& name) {
    Unk1* data = find(name);

    if (!data)
        return false;
    data->mLink.reset();
    return true;
}

}  // namespace uking::act
