#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/System/MoviePlayer.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::evt {

// The TU's static initializer is 0x7100dbc720 (`_GLOBAL__sub_I_evtEventFlowMovie.cpp`).
namespace {
util::InitConstants sInitConstants;
util::InitTimeInfo sInitTimeInfo;
}  // namespace

// 0x7100dbc51c
f32 EventFlowMovie::getFrameCount() const {
    if (mMoviePath[0] == sead::SafeString::cNullChar)
        return mFrameCount;
    return MoviePlayer::instance()->mFrameCount;
}

// 0x7100dbc6ec (CSV evt::EventFlowMovie::getEventFlowType): 3 = movie without a path
s32 EventFlowMovie::getEventFlowType() const {
    return *mMoviePath == sead::SafeString::cNullChar ? 3 : 2;
}

// 0x7100dbc558
void EventFlowMovie::printStatus(sead::BufferedSafeString* out) {
    if (EventFlowBase::isPlaying())
        out->format("%5.2f 【ムービー再生】", getFrameCount());
    else
        out->format(_100->m7());
}

// 0x7100dbbce4
bool EventFlowMovie::m14() {
    if (mMoviePath[0] == sead::SafeString::cNullChar)
        return _72c > 120;
    return MoviePlayer::instance()->sub_71010B9C84();
}

}  // namespace ksys::evt
