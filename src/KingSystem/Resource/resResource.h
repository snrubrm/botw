#pragma once

#include <resource/seadResource.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class IResource {
public:
    virtual ~IResource() = default;
};

class Context {
    // BfRes context RTTI (1200990) derives from this root, typeinfo 25DBCD8.
    SEAD_RTTI_BASE(Context)
public:
    virtual ~Context() = default;
};

// Placeholder name (RTTI typeInfo static 0x71025dbf90): a load context subclass whose u32 at +0x60
// ResourceJpg::sub_71009CD408 returns (8 for any other context).
class Unk_71025dbf90 : public Context {
    SEAD_RTTI_OVERRIDE(Unk_71025dbf90, Context)
public:
    u8 _8[0x60 - 0x8];
    u32 _60;
};

class Resource : public sead::DirectResource, public IResource {
    SEAD_RTTI_OVERRIDE(Resource, sead::DirectResource)
public:
    Resource();
    ~Resource() override;

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;

    virtual bool needsParse() const { return false; }
    virtual bool m2_() { return true; }

    Context* getContext() const;
    void setContext(Context* context);
    // 0x71012012ec (lane3 s84: a member, ResourceJpg::sub_71009CD408 passes `this`): the context of the
    // resource being loaded (set by the load task around doLoad).
    Context* getCurrentLoadContext() const;

    void onDestroy();
    bool parse(Context*, sead::Heap* heap);
    bool finalize();
    bool finishParsing(Context* context);
    bool m7();

    static constexpr size_t cLoadDataAlignment = 4;

protected:
    virtual void onDestroy_() {}
    virtual bool parse_(u8* data, size_t size, sead::Heap* heap);
    virtual void finalize_() {}
    virtual bool finishParsing_() { return true; }
    virtual bool m7_() { return true; }
    virtual void m8_() {}

    u32 mAllocSize = 0;
    Context* mContext = nullptr;
};
KSYS_CHECK_SIZE_NX150(Resource, 0x38);

inline void Resource::doCreate_(u8*, u32, sead::Heap*) {}

inline bool Resource::parse_(u8*, size_t, sead::Heap*) {
    return true;
}

// Native 1210D1C sets this Context pointer around doLoad, clears it, then passes the
// same value to Resource::setContext. ResourceJpg's 9CD408 performs RTTI on the result.
void setCurrentLoadContext(Context* context);
void clearCurrentLoadContext();

}  // namespace ksys::res
