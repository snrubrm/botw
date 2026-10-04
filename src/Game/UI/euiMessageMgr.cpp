#include "Game/UI/euiMessageMgr.h"
#include <new>

namespace eui {

SEAD_SINGLETON_DISPOSER_IMPL(MessageMgr)

MessageMgr::~MessageMgr() = default;

// NON_MATCHING: the same stores in the same unrolled loop, but the original reloads the white color once per three to
// four stores where ours reloads it after every second store (the element's two members).
// 0x7100be4508
void MessageMgr::allocGradationColors(sead::Heap* heap, s32 count) {
    mGradationColors.tryAllocBuffer(count, heap, 8);
}

// 0x7100be45ec
void MessageMgr::loadArchive(sead::Heap* heap, void* data, u32 size) {
    auto* archive = new (heap, 8) Archive(heap, this);
    archive->load(heap, data, size);
    mArchives.pushFront(archive);
}

// NON_MATCHING: same code; the original keeps the object pointer and the node pointer of the list walk in different
// registers (offset arithmetic of the intrusive list iteration).
// 0x7100be46a0
void MessageMgr::unloadArchive(void* data) {
    for (auto& archive : mArchives) {
        if (archive.mData == data) {
            archive.unload();
            mArchives.erase(&archive);
            delete &archive;
            return;
        }
    }
}

// 0x7100be473c
MessageSet* MessageMgr::getMessageSet(const sead::SafeString& name) {
    sead::FixedSafeString<256> path;
    path.format("%s.msbt", name.cstr());
    for (auto& archive : mArchives) {
        if (auto* set = archive.findMessageSet(path))
            return set;
    }
    return nullptr;
}

// 0x7100be4854
MessageSet* MessageMgr::getLayoutMessageSet(const sead::SafeString& name) {
    sead::FixedSafeString<256> path;
    path.format("LayoutMsg/%s.msbt", name.cstr());
    for (auto& archive : mArchives) {
        if (auto* set = archive.findMessageSet(path))
            return set;
    }
    return nullptr;
}

// 0x7100be496c
void MessageMgr::setGradationColor(u32 index, sead::Color4u8 top, sead::Color4u8 bottom) {
    GradationColor& color = mGradationColors[index];
    color.top = top;
    color.bottom = bottom;
}

// 0x7100be4988
void MessageMgr::m0() {}

// NON_MATCHING (D2 / D0): the original loads `mMgr` as the first statement (before the vtable store and the link
// test); ours loads it inside the branch. A leading `MessageMgr* mgr = mMgr;` would match (a local used once only for
// ordering: not applied).
// 0x7100be498c
MessageMgr::Archive::~Archive() {
    if (mNode.isLinked())
        mMgr->mArchives.erase(this);
}

// 0x7100be4a5c
void MessageMgr::Archive::load(sead::Heap* heap, void* data, u32 size) {
    mData = data;
    mArchive.initialize(heap, data, size);
    mMessageSets.tryAllocBuffer(mArchive.getResource()->getEntryNum(), heap, 8);
    SharcArchive::FileReader reader;
    mArchive.startFileReader(&reader);
    while (reader.readNext()) {
        if (reader.mEntry.name.findIndex(".msbt") >= 0)
            mMessageSets[reader.mIndex].initialize(
                const_cast<void*>(reader.mDevice.mArchive->getFileFast(reader.mIndex, nullptr)), heap);
    }
}

// 0x7100be4c48
void MessageMgr::Archive::unload() {
    for (auto& set : mMessageSets) {
        if (set.isInitialized())
            set.finalize();
    }
    mMessageSets.freeBuffer();
    mArchive.unload();
}

}  // namespace eui
