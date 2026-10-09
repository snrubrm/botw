#include "aal/aalAudioResource.h"
#include <resource/seadArchiveRes.h>
#include "aal/aalAssetInfo.h"
#include "aal/aalMemoryPoolManager.h"
#include "aal/aalSystem.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7101406E54
AudioResource::~AudioResource() {
    SystemAccessor::getSystem()->mMemoryPoolManager->requestDetachMemoryPool(&mMemoryPool);
    if (mArchive) {
        delete mArchive;
        mArchive = nullptr;
    }
    if (mOwnsFilename && mFilename) {
        delete mFilename;
        mFilename = nullptr;
    }
    if (mAssetInfos) {
        delete mAssetInfos;
        mAssetInfos = nullptr;
    }
}

// 0x7101406F5C
void AudioResource::setFilename(const sead::SafeString* filename) {
    mFilename = filename;
}

}  // namespace aal
