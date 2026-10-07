#include "KingSystem/System/PosTrackerUploadJob.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/PosTrackerUploader.h"

namespace ksys {

Unk_7100a8f2dc::Unk_7100a8f2dc() : mDelegate(this, &Unk_7100a8f2dc::sub_7100A8F310) {}

bool Unk_7100a8f2dc::sub_7100A8F310(void* arg) {
    if (mFlags.load() & 4)
        sub_7100A8FAA4();
    else
        sub_7100A8FCE4();
    return true;
}

bool Unk_7100a8f2dc::sub_7100A8F9F0(u64 nex_id) {
    auto* uploader = PosTrackerUploader::instance();
    if (nex_id == 0) {
        const u32 upper = gdt::getFlag_NexUniqueID_Upper(false);
        const u32 lower = gdt::getFlag_NexUniqueID_Lower(false);
        nex_id = (u64(upper) << 32) | lower;
    }
    const bool success = (mFlags.load() & 4) ?
        uploader->sub_7100A8CC48(mBuffer, mSize, nex_id, mHardMode) :
        uploader->sub_7100A8C770(mBuffer, mSize, nex_id, mBlock, mHardMode);
    if (success) {
        mState = 3;
        return true;
    }
    uploader->queueCleanUp();
    mState = 4;
    return false;
}

}  // namespace ksys
