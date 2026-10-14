#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/Resource/Actor/resResourceAttClient.h"
#include <math/seadBoundBox.h>
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {

ActorAttention::~ActorAttention() {
    mClients.freeBuffer();
}

ActorAttention* ActorAttention::make(const CreateArg& arg) {
    if (!arg.actor || !arg.param || !arg.heap)
        return nullptr;
    auto* list = arg.param->getRes().mAttClientList;
    if (!list)
        return nullptr;

    auto* attention = new (arg.heap) ActorAttention;
    if (!attention)
        return nullptr;
    attention->mList = list;
    attention->mActor = arg.actor;

    const s32 num_clients = list->getClients().size();
    if (num_clients > 0) {
        attention->mClients.tryAllocBuffer(num_clients, arg.heap);
        if (!attention->mClients.isBufferReady()) {
            delete attention;
            return nullptr;
        }
        s32 i = 0;
        for (auto& client : attention->mClients) {
            if (!client.init(arg.actor, &list->getClients()[i], arg.heap)) {
                delete attention;
                return nullptr;
            }
            ++i;
        }
    }

    if (attention->mList && attention->mActor && attention->mList->isForceEdit()) {
        const auto& node = attention->mList->getAttPos().node.ref();
        if (!node.isEmpty()) {
            if (auto* model = attention->mActor->getModel())
                attention->mBoneKey.search(model, node);
        }
    }
    attention->init();
    return attention;
}

void ActorAttention::init() {
    f32 max = -1.0f;
    for (auto& client : mClients) {
        const f32 value = client.sub_7100D72660();
        max = max > value ? max : value;
    }

    f32 radius = 0.0f;
    if (mActor) {
        if (auto* body = mActor->getPhysicsMainBody()) {
            sead::BoundBox3f box(sead::Vector3f::zero, sead::Vector3f::ones);
            body->getAabbInLocal(&box);
            const f32 min_x = sead::Mathf::abs(box.getMin().x);
            const f32 min_y = sead::Mathf::abs(box.getMin().y);
            const f32 min_z = sead::Mathf::abs(box.getMin().z);
            const f32 max_x = sead::Mathf::abs(box.getMax().x);
            const f32 max_y = sead::Mathf::abs(box.getMax().y);
            const f32 max_z = sead::Mathf::abs(box.getMax().z);
            const sead::Vector3f extent{min_x > max_x ? min_x : max_x, min_y > max_y ? min_y : max_y,
                                        min_z > max_z ? min_z : max_z};
            radius = extent.length();
        }
    }

    f32 value = 0.0f;
    if (mClients.size() != 0) {
        if (max < 0.0f)
            value = 1000.0f;
        else
            value = max + radius + 10.0f;
    }
    _58 = value;
}

void ActorAttention::sub_7100D73454(sead::Vector3f* out) const {
    if (mList)
        mList->x(out, mActor, &mBoneKey.getKey());
}

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

void ActorAttention::sub_7100D738EC() {
    for (auto& client : mClients)
        client.sub_7100D72178();
}

void ActorAttention::sub_7100D73924() {
    for (auto& client : mClients)
        client.sub_7100D721C0();
}

void ActorAttention::sub_7100D7395C() {
    for (auto& client : mClients)
        client.sub_7100D72320();
}

void ActorAttention::resetEnabled() {
    for (auto& client : mClients)
        client.resetEnabled();
}

}  // namespace ksys::act
