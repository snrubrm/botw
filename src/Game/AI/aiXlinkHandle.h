#pragma once

#include <basis/seadTypes.h>
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2Util.h>

namespace uking::xlink {

// Inline xlink2 handle methods. They are inline-only in the original (the binary has no out-of-line
// copy; ~150 functions inline them). lib/xlink2 is a submodule, so they are free functions here
// instead of members; the names are the original's own: the debug format strings in the binary
// ("HandleSLink::fade(%s)", "HandleELink::fade(%s)", "HandleELink::fadeIfLoopEffect(%s)",
// "HandleSLink::fadeIfLoopSound(%s)", "HandleELink::kill(%s)") name the member functions.
//
// Each one is: if the handle's event exists and its create id still equals the handle's, log
// through the event's user instance (checkAndErrorCallInCalc + printLogFadeOrKill, with the asset
// key name) and forward to the event. The event is re-read from the handle after every call.

namespace detail {
inline const char* getKeyName(xlink2::Event* event) {
    return xlink2::solveOffset<const char>(event->getAssetCallTable()->keyNamePos);
}
}  // namespace detail

inline void fade(xlink2::HandleSLink& handle, s32 frames) {
    if (handle.getEvent() && handle.getEvent()->getCreateId() == u32(handle.getCreateId())) {
        auto* user = handle.getEvent()->getUserInstance();
        user->checkAndErrorCallInCalc("HandleSLink::fade(%s)", detail::getKeyName(handle.getEvent()));
        user->printLogFadeOrKill(handle.getEvent(), "HandleSLink::fade(%s)",
                                 detail::getKeyName(handle.getEvent()));
        handle.getEvent()->fade(frames);
    }
}

inline void fade(xlink2::HandleELink& handle, s32 frames) {
    if (handle.getEvent() && handle.getEvent()->getCreateId() == u32(handle.getCreateId())) {
        auto* user = handle.getEvent()->getUserInstance();
        user->checkAndErrorCallInCalc("HandleELink::fade(%s)", detail::getKeyName(handle.getEvent()));
        user->printLogFadeOrKill(handle.getEvent(), "HandleELink::fade(%s)",
                                 detail::getKeyName(handle.getEvent()));
        handle.getEvent()->fade(frames);
    }
}

inline void fadeIfLoopEffect(xlink2::HandleELink& handle) {
    if (handle.getEvent() && handle.getEvent()->getCreateId() == u32(handle.getCreateId())) {
        auto* user = handle.getEvent()->getUserInstance();
        user->checkAndErrorCallInCalc("HandleELink::fadeIfLoopEffect(%s)",
                                      detail::getKeyName(handle.getEvent()));
        user->printLogFadeOrKill(handle.getEvent(), "HandleELink::fadeIfLoopEffect(%s)",
                                 detail::getKeyName(handle.getEvent()));
        handle.getEvent()->fadeBySystem();
    }
}

inline void fadeIfLoopSound(xlink2::HandleSLink& handle) {
    if (handle.getEvent() && handle.getEvent()->getCreateId() == u32(handle.getCreateId())) {
        auto* user = handle.getEvent()->getUserInstance();
        user->checkAndErrorCallInCalc("HandleSLink::fadeIfLoopSound(%s)",
                                      detail::getKeyName(handle.getEvent()));
        user->printLogFadeOrKill(handle.getEvent(), "HandleSLink::fadeIfLoopSound(%s)",
                                 detail::getKeyName(handle.getEvent()));
        handle.getEvent()->fadeBySystem();
    }
}

inline void kill(xlink2::HandleELink& handle) {
    if (handle.getEvent() && handle.getEvent()->getCreateId() == u32(handle.getCreateId())) {
        auto* user = handle.getEvent()->getUserInstance();
        user->checkAndErrorCallInCalc("HandleELink::kill(%s)", detail::getKeyName(handle.getEvent()));
        user->printLogFadeOrKill(handle.getEvent(), "HandleELink::kill(%s)",
                                 detail::getKeyName(handle.getEvent()));
        handle.getEvent()->kill();
    }
}

}  // namespace uking::xlink
