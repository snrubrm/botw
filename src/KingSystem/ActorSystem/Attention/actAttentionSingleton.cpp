#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include <mc/seadCoreInfo.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(Attention)

bool Attention::sub_7100D753B0() const {
    return (mFlagsE22.isOn(2) || (mFlagsE21 & 8)) && !mEnabled;
}

bool Attention::sub_7100D74114() const {
    if (!mEnabled)
        return false;
    const auto& lock = mLists[1];
    if (lock.size() == 0)
        return false;
    return lock.unsafeAt(0) != nullptr;
}

bool Attention::sub_7100D742E8(s32 list) const {
    return mLists[list].size() == 0;
}

// NON_MATCHING: the original tail-calls BaseProcLink::operator= (and stores the flag byte before the call)
void Attention::sub_7100D744B8(const BaseProcLink& link) {
    if (!link.hasProc())
        return;
    mFlagsE21 |= 4;
    mRequestedTarget = link;
}

bool Attention::sub_7100D74148(BaseProcLink* out) {
    if (mEnabled && mLists[1].size() != 0) {
        if (auto* client = mLists[1].unsafeAt(0)) {
            if (auto* actor = client->getActor()) {
                out->acquire(actor, false);
                return true;
            }
        }
    }
    return false;
}

bool Attention::x(BaseProcAccessor* out) {
    if (out && mEnabled && mLists[1].size() != 0) {
        if (auto* client = mLists[1].unsafeAt(0)) {
            if (auto* actor = client->getActor()) {
                out->acquire(actor);
                return true;
            }
        }
    }
    return false;
}

bool Attention::sub_7100D74208(u32* out) const {
    if (out && mEnabled && mLists[1].size() != 0) {
        if (auto* client = mLists[1].unsafeAt(0)) {
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
        for (s32 i = 0; i < list.size(); ++i) {
            if (list.unsafeAt(i) == client) {
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

bool Attention::sub_7100D7482C(BaseProcAccessor* out) {
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
    if (u32(index) < u32(target_list.size()))
        client = target_list.unsafeAt(index);
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

bool Attention::sub_7100D7430C(s32 list, s32 index, BaseProcLink* out) {
    if (index >= 0 && index < mLists[list].size()) {
        if (auto* client = mLists[list].at(index)) {
            if (auto* actor = client->getActor()) {
                out->acquire(actor, false);
                return true;
            }
        }
    }
    return false;
}

bool Attention::x_0(s32 list, s32 index, BaseProcAccessor* out) {
    if (index >= 0 && out && index < mLists[list].size()) {
        if (auto* client = mLists[list].at(index)) {
            if (auto* actor = client->getActor()) {
                out->acquire(actor);
                return true;
            }
        }
    }
    return false;
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
    return mLists[list].size();
}

void Attention::sub_7100D74504(u32 value) {
    if (value <= 1)
        _c4c = value;
}

void Attention::setPlayerLink(PlayerLink* link) {
    _c20 = link;
}

bool Attention::sub_7100D74488(BaseProcAccessor* out) {
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
    if (mEnabled && mLists[1].size() != 0)
        current = mLists[1].unsafeAt(0);
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

namespace ksys::act {

// NON_MATCHING: member addresses are scheduled differently around the first link reset.
Attention::~Attention() = default;

// NON_MATCHING: fixed-array selection and branch scheduling differ.
void Attention::sub_7100D74920(AttClient* client) {
    if (!client || !client->getActor() || !client->sub_7100D72144() || client->getScore() < 0.0f)
        return;

    const u32 core = sead::CoreInfo::getPlatformCoreId(sead::CoreInfo::getCurrentCoreId());
    const s32 type = client->sub_7100D72534();
    auto& list = _28[core][type];
    if (mFlagsE21 & 8) {
        if (!_da8.hasProc())
            return;
        if (type == int(AttType::Lock) || type == int(AttType::SwordSearch)) {
            if (!_da8.hasProcById(client->getActor()))
                return;
        }
    }
    if (type == int(AttType::Action)) {
        const auto code = client->sub_7100D72544();
        if (int(_c10) != int(AttActionCode::None) &&
            (int(_c10) == int(AttActionCode::Pick) || int(_c10) == int(AttActionCode::Catch) ||
             int(_c10) == int(AttActionCode::Awake)) &&
            int(code) != int(_c10) && !(_c14 >= 30.0f))
            return;
    }

    if (list.isEmpty())
        list.pushBack(client);
    else
        sub_7100D74BDC(client, list, 0);
    if (type == int(AttType::Lock) && mLists[type].indexOf(client) != -1) {
        // The three fixed arrays are separately declared members.
        auto& extra = core == 1 ? _a78 : core == 2 ? _ac8 : _a28;
        if (extra.indexOf(client) == -1)
            extra.pushBack(client);
    }
}

// NON_MATCHING: the replacement call is shared before the state-specific conditions.
void Attention::sub_7100D751D4(AttClient* client) {
    if (!client)
        return;
    const s32 index = mLists[client->sub_7100D72534()].indexOf(client);
    if (index == -1)
        return;
    const s32 type = client->sub_7100D72534();
    mLists[type].erase(index);
    if (type != int(AttType::Lock))
        return;
    const u8 state = mEnabled;
    if (state > 3)
        return;
    auto& lock = mLists[int(AttType::Lock)];
    if (auto* replacement = sub_7100D7704C())
        lock.pushBack(replacement);
    switch (state) {
    case 0:
        return;
    case 1:
        if (index != 0 && lock.size() > 1)
            return;
        break;
    case 2:
        if (index != 0 || (!lock.isEmpty() && (mFlagsE21 & 2)))
            return;
        break;
    case 3:
        if (index != 0)
            return;
        break;
    }
    mEnabled = 0;
    _c44 = 0.0f;
}

// NON_MATCHING: the separately declared backup arrays change selection; popFront calls erase.
AttClient* Attention::sub_7100D7704C() {
    f32 best_score = -1.0f;
    s32 best = -1;
    for (s32 i = 0; i < 3; ++i) {
        auto& list = i == 1 ? _b68 : i == 2 ? _bb8 : _b18;
        while (!list.isEmpty() && mLists[int(AttType::Lock)].indexOf(list.front()) != -1)
            list.popFront();
        if (!list.isEmpty() && best_score < list.front()->getScore()) {
            best_score = list.front()->getScore();
            best = i;
        }
    }
    if (best == -1)
        return nullptr;
    auto& list = best == 1 ? _b68 : best == 2 ? _bb8 : _b18;
    return list.popFront();
}

// NON_MATCHING: the original unrolls the three core groups.
void Attention::sub_7100D74DD4(AttClient* client) {
    const s32 type = client->sub_7100D72534();
    u32 removed = 0;
    for (u32 core = 0; core < 3; ++core) {
        auto& list = _28[core][type];
        while (!list.isEmpty()) {
            const s32 index = list.indexOf(client);
            if (index == -1)
                break;
            if (removed) {
                sead::FormatFixedSafeString<128> message("今のコア  [%08X]\n削除済コア[%08X]\n",
                                                         1u << core, removed);
            }
            list.erase(index);
            removed |= 1u << core;
        }
    }
}

}  // namespace ksys::act
