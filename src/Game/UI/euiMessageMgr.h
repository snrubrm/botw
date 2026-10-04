#pragma once

#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <gfx/seadColor.h>
#include <heap/seadDisposer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "Game/UI/euiMessageSet.h"
#include "Game/UI/euiSharcArchive.h"

namespace eui {

// The UI message manager singleton (0x58 bytes): the loaded message archives (one per language / archive file; each
// archive holds one MessageSet per .msbt file) and the gradation colors of the texts.
class MessageMgr {
    SEAD_SINGLETON_DISPOSER(MessageMgr)
    SEAD_RTTI_BASE(MessageMgr)
    MessageMgr() { mArchives.initOffset(offsetof(Archive, mNode)); }
    virtual ~MessageMgr();

public:
    struct GradationColor {
        GradationColor() : top(sead::Color4u8::cWhite), bottom(sead::Color4u8::cWhite) {}

        sead::Color4u8 top;
        sead::Color4u8 bottom;
    };

    // A loaded message archive (0x58 bytes, sead RTTI; linked into MessageMgr::mArchives).
    class Archive : public sead::IDisposer {
        SEAD_RTTI_BASE(Archive)
    public:
        Archive(sead::Heap* heap, MessageMgr* mgr)
            : sead::IDisposer(heap, sead::IDisposer::HeapNullOption::UseSpecifiedOrContainHeap), mMgr(mgr) {}
        ~Archive() override;

        // 0x7100be4a5c: opens the archive and the message set of every .msbt file in it
        virtual void load(sead::Heap* heap, void* data, u32 size);
        // 0x7100be4c48
        virtual void unload();

        // inline-only in the original; name is a guess: the message set of the .msbt file `path` in this archive
        MessageSet* findMessageSet(const sead::SafeString& path) {
            const s32 index = mArchive.getResource()->convertPathToEntryID(path);
            if (index < 0)
                return nullptr;
            return &mMessageSets[index];
        }

        /* 0x20 */ sead::ListNode mNode;
        /* 0x30 */ SharcArchive mArchive;
        /* 0x38 */ sead::Buffer<MessageSet> mMessageSets;
        /* 0x48 */ MessageMgr* mMgr;
        /* 0x50 */ void* mData = nullptr;
    };

    // 0x7100be4508 (placeholder name)
    void allocGradationColors(sead::Heap* heap, s32 count);
    // 0x7100be45ec (virtual slot 4)
    virtual void loadArchive(sead::Heap* heap, void* data, u32 size);
    // 0x7100be46a0 (slot 5): unloads (and destroys) the archive that was loaded from `data`
    virtual void unloadArchive(void* data);
    // 0x7100be473c: the message set of `name` ("<name>.msbt") in the first archive that has it
    MessageSet* getMessageSet(const sead::SafeString& name);
    // 0x7100be4854 (placeholder name): the same for the layout texts ("LayoutMsg/<name>.msbt")
    MessageSet* getLayoutMessageSet(const sead::SafeString& name);
    // 0x7100be496c
    void setGradationColor(u32 index, sead::Color4u8 top, sead::Color4u8 bottom);

private:
    /* 0x28 */ sead::OffsetList<Archive> mArchives;
    /* 0x40 */ sead::Buffer<GradationColor> mGradationColors;
    /* 0x50 */ bool _50 = true;
};

}  // namespace eui
