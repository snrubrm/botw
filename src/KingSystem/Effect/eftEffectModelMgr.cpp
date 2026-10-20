#include "KingSystem/Effect/eftEffectModelMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/Resource/resBfRes.h"
#include "KingSystem/System/StageInfo.h"
#include <gsys/gsysModelResource.h>
#include <gsys/gsysG3dResModelEx.h>
#include <nn/g3d/ResFile.h>
#include <nn/g3d/ResModel.h>
#include <cstring>

namespace ksys::eft {

// NON_MATCHING: model-count accumulation and formatted-message temporaries differ.
EffectModelData* EffectModelMgr::entry(sead::Heap* heap, act::Actor* actor,
                                        res::BfRes* resource, const char* name) {
    const char* actor_name = actor ? actor->getName().cstr() : "clusteredRenderer";
    auto* model_resource = resource->_50;
    const u32 model_count = model_resource->getResFile()->mModelCount;
    u32 effect_model_count = 0;
    for (u32 i = 0; i != model_count; ++i) {
        const sead::SafeString model_name(model_resource->getResModelEx(i)->getResModel()->GetName());
        effect_model_count += model_name.findIndex("_Fxmdl") != -1 ||
                              model_name.findIndex("_EffectModel") != -1;
    }
    if (effect_model_count == 0)
        return nullptr;
    if (u16(heap->getFreeSize() >> 16) <= 2) {
        sead::FormatFixedSafeString<128> label("EffectModelMgr::entry[%s]", actor_name);
        sead::FormatFixedSafeString<256> message("EffectModelMgr::entry[%s] メモリ不足で失敗",
                                                actor_name);
        const auto& map_type = StageInfo::getCurrentMapType();
        if (map_type == "GameTestField" || map_type == "GameTestDungeon")
            Effect::instance()->debugLog("%s\n", message.cstr());
        return nullptr;
    }

    mEntryCS.lock();
    mCS.lock();
    for (u64 i = 0; i < 64; ++i) {
        auto& data = mEntries[i];
        if (data._0 && std::strcmp(data.mName.cstr(), name) == 0 && data.mRes == resource) {
            ++data.mRefCount;
            mCS.unlock();
            if (data.mRes != resource) {
                sead::FormatFixedSafeString<128> label("EffectModelMgr::entry[%s]", actor_name);
                sead::FormatFixedSafeString<256> message(
                    "EffectModelMgr::entry[%s] 登録済みのリソースとは違うリソースポインタが渡された[res:%s: %p != %p]",
                    actor_name, name, resource, data.mRes);
                mEntryCS.unlock();
                return nullptr;
            }
            if (mDebugLog)
                Effect::instance()->debugLog(
                    "EffectModelMgr::entry() : [res:%s:%p][actor:%s:%p](ref=%d).\n",
                    name, resource, actor_name, actor, data.mRefCount);
            mEntryCS.unlock();
            return &data;
        }
    }
    mCS.unlock();
    mCS.lock();
    EffectModelData* data = nullptr;
    for (u64 i = 0; i < 64; ++i) {
        if (!mEntries[i]._0 && mEntries[i].mRefCount == 0) {
            data = &mEntries[i];
            break;
        }
    }
    if (!data) {
        mCS.unlock();
        sead::FormatFixedSafeString<128> label("EffectModelMgr::entry[%s]", actor_name);
        sead::FormatFixedSafeString<256> message(
            "EffectModelMgr::entry[%s] モデルリソースの確保に失敗[res:%s: %p]",
            actor_name, name, resource);
        mEntryCS.unlock();
        return nullptr;
    }
    data->mRefCount = 1;
    mCS.unlock();
    mCS.lock();
    const bool initialized = data->addEffectModel_0(heap, name, resource);
    if (!initialized)
        --data->mRefCount;
    data->_1 = false;
    data->_0 = initialized;
    mCS.unlock();
    if (!initialized) {
        if (mDebugLog)
            Effect::instance()->debugLog(
                "EffectModelMgr::entry() : [res:%s:%p][actor:%s:%p] initialize failed.\n",
                name, resource, actor_name, actor);
        mEntryCS.unlock();
        return nullptr;
    }
    if (mDebugLog)
        Effect::instance()->debugLog(
            "EffectModelMgr::entry() : [res:%s:%p][actor:%s:%p] entry ok(ref=%d)\n",
            name, resource, actor_name, actor, data->mRefCount);
    mEntryCS.unlock();
    return data;
}

bool EffectModelMgr::requestDeleteModel(act::Actor* actor, EffectModelData* data) {
    if (!data)
        return false;

    mCS.lock();
    data->decRefCnt();
    mCS.unlock();

    if (mDebugLog) {
        Effect::instance()->debugLog(
            "EffectModelMgr::requestDeleteModel() : [res:%s:%p][actor:%s:%p](ref=%d)\n",
            data->mName.cstr(), data->mRes, actor ? actor->getName().cstr() : "clusterdRenderer",
            actor, data->mRefCount);
    }
    return true;
}

bool EffectModelMgr::release(act::Actor* actor, EffectModelData* data) {
    if (!data)
        return false;

    if (mDebugLog) {
        Effect::instance()->debugLog(
            "EffectModelMgr::release() : [res:%s][actor:%s:%p](ref=%d)\n", data->mName.cstr(),
            actor ? actor->getName().cstr() : "clusterdRenderer", actor, data->mRefCount);
    }

    mCS.lock();
    data->finalize();
    mCS.unlock();
    return true;
}

}  // namespace ksys::eft
