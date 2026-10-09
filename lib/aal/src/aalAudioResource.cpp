#include "aal/aalAudioResource.h"

namespace aal {

// 0x7101406F5C
void AudioResource::setFilename(const sead::SafeString* filename) {
    mFilename = filename;
}

}  // namespace aal
