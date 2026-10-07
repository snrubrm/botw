#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(Attention)

bool Attention::sub_7100D753B0() const {
    return (mFlagsE22.isOn(2) || (mFlagsE21 & 8)) && !mEnabled;
}

bool Attention::sub_7100D74114() const {
    if (!mEnabled)
        return false;
    const auto& lock = mLists[1];
    if (lock.mCount == 0)
        return false;
    return *lock.mEntries != nullptr;
}

bool Attention::sub_7100D742E8(s32 list) const {
    return mLists[list].mCount == 0;
}

// NON_MATCHING: the original tail-calls BaseProcLink::operator= (and stores the flag byte before the call)
void Attention::sub_7100D744B8(const BaseProcLink& link) {
    if (!link.hasProc())
        return;
    mFlagsE21 |= 4;
    mRequestedTarget = link;
}

bool Attention::sub_7100D74148(BaseProcLink* out) {
    if (mEnabled && mLists[1].mCount != 0) {
        if (auto* client = *mLists[1].mEntries) {
            if (auto* actor = client->getActor()) {
                out->acquire(actor, false);
                return true;
            }
        }
    }
    return false;
}

bool Attention::x(ActorLinkConstDataAccess* out) {
    if (out && mEnabled && mLists[1].mCount != 0) {
        if (auto* client = *mLists[1].mEntries) {
            if (auto* actor = client->getActor()) {
                out->acquire(actor);
                return true;
            }
        }
    }
    return false;
}

bool Attention::sub_7100D74208(u32* out) const {
    if (out && mEnabled && mLists[1].mCount != 0) {
        if (auto* client = *mLists[1].mEntries) {
            *out = client->sub_7100D724F4();
            return true;
        }
    }
    return false;
}

bool Attention::sub_7100D74258(const AttClient* client) const {
    s32 index = -1;
    if (client) {
        const auto& list = mLists[client->sub_7100D72534()];
        for (s32 i = 0; i < list.mCount; ++i) {
            if (list.mEntries[i] == client) {
                index = i;
                break;
            }
        }
    }
    return index != -1;
}

bool Attention::sub_7100D747D8(BaseProcLink* out) {
    if (auto* client = sub_7100D7457C(false, AttActionCodeValue(int(AttActionCode::None)))) {
        if (auto* actor = client->getActor()) {
            out->acquire(actor, false);
            return true;
        }
    }
    return false;
}

bool Attention::sub_7100D7482C(ActorLinkConstDataAccess* out) {
    if (out) {
        if (auto* client = sub_7100D7457C(false, AttActionCodeValue(int(AttActionCode::None)))) {
            if (auto* actor = client->getActor()) {
                out->acquire(actor);
                return true;
            }
        }
    }
    return false;
}

AttActionCodeValue Attention::sub_7100D74880() {
    if (auto* client = sub_7100D7457C(false, AttActionCodeValue(int(AttActionCode::None))))
        return client->sub_7100D72544();
    return 0x1800029;
}

bool Attention::sub_7100D748B8() const {
    if (auto* client = sub_7100D7457C(false, AttActionCodeValue(int(AttActionCode::None))))
        return int(client->sub_7100D72544()) != int(AttActionCode::Remind);
    return false;
}

bool Attention::sub_7100D748FC(AttActionCodeValue code) const {
    return sub_7100D7457C(true, code) != nullptr;
}

AttActionCodeValue Attention::sub_7100D74430(s32 list, s32 index) const {
    const auto& target_list = mLists[list];
    AttClient* client = nullptr;
    if (u32(index) < u32(target_list.mCount))
        client = target_list.mEntries[index];
    return client->sub_7100D72544();
}

bool Attention::sub_7100D74550() const {
    auto* client = sub_7100D7457C(false, AttActionCodeValue(int(AttActionCode::None)));
    return client && client->getActor();
}

void Attention::sub_7100D74D78(AttClient* client) {
    if (client) {
        sub_7100D74DD4(client);
        sub_7100D74FEC(client);
        sub_7100D750E0(client);
        sub_7100D751D4(client);
    }
}

void Attention::sub_7100D74FEC(AttClient* client) {
    if (const s32 idx = _a28.indexOf(client); idx != -1)
        _a28.erase(idx);
    if (const s32 idx = _a78.indexOf(client); idx != -1)
        _a78.erase(idx);
    if (const s32 idx = _ac8.indexOf(client); idx != -1)
        _ac8.erase(idx);
}

void Attention::sub_7100D750E0(AttClient* client) {
    if (const s32 idx = _b18.indexOf(client); idx != -1)
        _b18.erase(idx);
    if (const s32 idx = _b68.indexOf(client); idx != -1)
        _b68.erase(idx);
    if (const s32 idx = _bb8.indexOf(client); idx != -1)
        _bb8.erase(idx);
}

s32 Attention::getTargetCount(s32 list) const {
    return mLists[list].mCount;
}

void Attention::sub_7100D74504(u32 value) {
    if (value <= 1)
        _c4c = value;
}

void Attention::setPlayerLink(PlayerLink* link) {
    _c20 = link;
}

bool Attention::sub_7100D74488(ActorLinkConstDataAccess* out) {
    if (_c20)
        return _c20->getActorViaAccessor(out);
    return out->acquire(nullptr);
}

void Attention::sub_7100D744A8() {
    mFlagsE21 |= 1;
}

void Attention::sub_7100D74514(void* target) {
    mFlagsE22.reset(0xc);
    mFlagsE22.set(4);
    _dc0 = target;
}

void Attention::sub_7100D74530(AttActionCodeValue type, void* target) {
    mFlagsE22.reset(0xc);
    mFlagsE22.set(8);
    _db8 = type;
    _dc0 = target;
}

bool Attention::sub_7100D753D8(const AttClient* client) const {
    if (!client)
        return false;
    const AttClient* current = nullptr;
    if (mEnabled && mLists[1].mCount != 0)
        current = *mLists[1].mEntries;
    return current == client;
}

f32 Attention::sub_7100D75410() const {
    return _c30;
}

f32 Attention::sub_7100D75418() const {
    return _c34;
}

f32 Attention::sub_7100D75420() const {
    return _c38;
}

f32 Attention::sub_7100D75428() const {
    return _c3c;
}

bool Attention::sub_7100D75430() const {
    return _c20 ? _c20->isRidingHorse() : false;
}

bool Attention::sub_7100D75448() const {
    return _c20 ? _c20->m188() : false;
}

bool Attention::sub_7100D75460() const {
    return _c20 ? _c20->m203() : false;
}

bool Attention::sub_7100D75478() const {
    return _c20 ? _c20->m376() : false;
}

bool Attention::sub_7100D75490() const {
    return mFlagsE21 >> 1 & 1;
}

void Attention::setSomeFn(void* fn) {
    _c28 = fn;
}

void Attention::setController(void* controller) {
    _c18 = controller;
}

void Attention::setPauseState(bool paused) {
    mFlagsE22.changeBit(0, paused);
}

}  // namespace ksys::act
