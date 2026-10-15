#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "resResourceAttClient.h"

namespace ksys::res {

AttClientList::~AttClientList() {
    mClients.freeBuffer();
}

void AttClientList::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {}

bool AttClientList::parse_(u8* data, size_t size, sead::Heap* heap) {
    if (!data)
        return false;

    agl::utl::ResParameterArchive archive{data};
    const auto root = archive.getRootList();

    mAttPos.init(&mAttPosObj);
    mForceEdit.init(false, "ForceEdit", "強制編集", "", &mAttPosObj);
    addObj(&mAttPosObj, "AttPos");

    const auto AttClients = agl::utl::getResParameterList(root, "AttClients");
    if (int num; AttClients && (num = AttClients.getResParameterObjNum()) != 0) {
        mClients.allocBufferAssert(num, heap);
        for (auto it = mClients.begin(), end = mClients.end(); it != end; ++it) {
            it->client = nullptr;
            it->name.init("", "Name", "クライアントのキー名", "", &it->obj);
            it->file_name.init("", "FileName", "クライアントのデータファイル名", "", &it->obj);
            it->is_valid.init(true, "IsValid", "デフォルトの有効・無効状態", "", &it->obj);

            mAttClientsList.addObj(
                &it->obj, sead::FormatFixedSafeString<32>("%s%d", "AttClient_", it.getIndex()));
        }
    }

    addList(&mAttClientsList, "AttClients");

    applyResParameterArchive(archive);
    return true;
}

bool AttClientList::finishParsing_() {
    return true;
}

bool AttClientList::m7_() {
    for (auto& client : mClients)
        client.client = nullptr;
    return true;
}

void AttClientList::x(sead::Vector3f* out, act::Actor* actor,
                      const gsys::BoneAccessKey* key) const {
    if (isForceEdit()) {
        sead::Matrix34f mtx;
        mAttPos.edit(&mtx, actor, key);
        mtx.getTranslation(*out);
        return;
    }

    if (!actor->x_18(out))
        actor->getMtx().getTranslation(*out);
}

bool AttClientList::isForceEdit() const {
    return mForceEdit.ref();
}

}  // namespace ksys::res
