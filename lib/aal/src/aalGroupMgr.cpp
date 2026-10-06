#include "aal/aalGroupMgr.h"
#include "aal/aalGroup.h"
#include "aal/aalGroupLimiter.h"

namespace aal {

// 0x7100b80c60
void GroupMgr::resetDuckingVolume() {
    for (Group& group : mGroups)
        group.mDuckingVolume = 1.0f;
}

// 0x7100b81498
void GroupMgr::pushDescendantsAndSelfGroupArray(sead::PtrArray<Group>* groups, Group* group) {
    if (groups && group) {
        groups->pushBack(group);
        group->pushDescendantGroupArray(groups);
    }
}

// 0x7100b814d8
bool GroupMgr::isUnderAncestorOrSelf(const Group* group, const Group* ancestor) {
    if (group == ancestor)
        return true;
    if (group && ancestor) {
        for (const Group* parent = group->getParent(); parent; parent = parent->getParent()) {
            if (parent == ancestor)
                return true;
        }
    }
    return false;
}

// 0x7100b81528
void GroupMgr::updateActiveSoundLimiterStructure() {
    for (Group& group : mGroups)
        group.mLimiter->updateUpperActiveSoundLimitList();
}

// 0x7100b81584
void GroupMgr::updateRequestSoundLimiterStructure() {
    for (Group& group : mGroups)
        group.mLimiter->updateUpperRequestSoundLimitList();
}

// 0x7100b815e0
void GroupMgr::updateRequestIntervalLimiterStructure() {
    for (Group& group : mGroups)
        group.mLimiter->updateUsingRequestIntervalLimiter();
}

}  // namespace aal
