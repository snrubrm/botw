#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace nn::gfx {
class ResShaderFile;
}

namespace eui {

class ArcResourceMgr {
public:
    class ArcResource : public sead::IDisposer {
    public:
        ArcResource(ArcResourceMgr* mgr, const sead::SafeString& name, void* data);
        ~ArcResource() override;

        /* 0x20 */ sead::ListNode mNode;
        /* 0x30 */ ArcResourceMgr* mMgr;
        /* 0x38 */ sead::FixedSafeString<64> mName;
        /* 0x90 */ u8* mData;
        /* 0x98 */ nn::gfx::ResShaderFile* mShaderResource;
    };

    ArcResourceMgr();
    virtual ~ArcResourceMgr();
    virtual void loadArchivesInDirectory(sead::Heap* heap, const sead::SafeString& path);
    virtual void loadArchive(sead::Heap* heap, const sead::SafeString& path);
    virtual u8* findArchiveData(const sead::SafeString& name) const;
    virtual void unloadAllArchives();
    virtual void addArchiveToList(ArcResource* archive);
    virtual void eraseArchiveFromList(ArcResource* archive);
    virtual ArcResource* findArcResource(const sead::SafeString& name) const;

protected:
    /* 0x08 */ sead::OffsetList<ArcResource> mArchives;
};
static_assert(sizeof(ArcResourceMgr) == 0x20);
static_assert(sizeof(ArcResourceMgr::ArcResource) == 0xa0);

}  // namespace eui
