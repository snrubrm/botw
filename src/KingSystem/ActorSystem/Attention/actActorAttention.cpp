#include "KingSystem/ActorSystem/Attention/actActorAttention.h"

namespace ksys::act {

s32 ActorAttention::getNumClients() const {
    return mClients.size();
}

AttClient* ActorAttention::getClientByIdx(s32 idx) {
    if (mClients.isIndexValid(idx))
        return &mClients(idx);
    return nullptr;
}

const AttClient* ActorAttention::getClientByIdx(s32 idx) const {
    if (mClients.isIndexValid(idx))
        return &mClients(idx);
    return nullptr;
}

const AttClient* ActorAttention::getClientByName(const sead::SafeString& name) const {
    s32 idx = -1;
    for (auto it = mClients.begin(), end = mClients.end(); it != end; ++it) {
        if (name == it->getName()) {
            idx = it.getIndex();
            break;
        }
    }
    if (idx == -1)
        return nullptr;
    return mClients.get(idx);
}

AttClient* ActorAttention::getClientByName(const sead::SafeString& name) {
    s32 idx = -1;
    for (auto it = mClients.begin(), end = mClients.end(); it != end; ++it) {
        if (name == it->getName()) {
            idx = it.getIndex();
            break;
        }
    }
    if (idx == -1)
        return nullptr;
    return mClients.get(idx);
}

bool ActorAttention::isClientEnabled(const sead::SafeString& name) const {
    const auto* client = getClientByName(name);
    if (!client)
        return false;
    return client->isEnabled();
}

bool ActorAttention::enableClient(const sead::SafeString& name) {
    auto* client = getClientByName(name);
    if (!client)
        return false;
    client->enable();
    return true;
}

bool ActorAttention::disableClient(const sead::SafeString& name) {
    auto* client = getClientByName(name);
    if (!client)
        return false;
    client->disable();
    return true;
}

void ActorAttention::enableAllClients() {
    for (auto& client : mClients)
        client.enable();
}

void ActorAttention::disableAllClients() {
    for (auto& client : mClients)
        client.disable();
}

}  // namespace ksys::act
