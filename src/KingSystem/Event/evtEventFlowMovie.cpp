#include "KingSystem/Event/evtEventFlow.h"

namespace ksys::evt {

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

}  // namespace ksys::evt
