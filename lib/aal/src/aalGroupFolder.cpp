#include "aal/aalGroup.h"
#include "aal/aalGroupMgr.h"

namespace aal {

// 0x7100bb6534: GroupFolder::GroupFolder is not decompiled yet (needs the Group constructor)

// 0x7100bb6574
void GroupFolder::stopAllSound(f32 fade_time) {
    for (auto* node = mTreeNode.child(); node; node = node->next())
        node->value()->stopAllSound(fade_time);
}

// 0x7100bb65bc
void GroupFolder::pauseAllSound(bool pause, f32 fade_time) {
    for (auto* node = mTreeNode.child(); node; node = node->next())
        node->value()->pauseAllSound(pause, fade_time);
}

// 0x7100bb660c
void GroupFolder::pauseAllSound(sead::BitFlag8 flags, bool pause, f32 fade_time) {
    for (auto* node = mTreeNode.child(); node; node = node->next())
        node->value()->pauseAllSound(flags, pause, fade_time);
}

// 0x7100bb666c
void GroupFolder::allowEmit(bool allow) {
    for (auto* node = mTreeNode.child(); node; node = node->next())
        node->value()->allowEmit(allow);
}

// 0x7100bb66ac
void GroupFolder::allowEmit(sead::BitFlag8 flags, bool allow) {
    for (auto* node = mTreeNode.child(); node; node = node->next())
        node->value()->allowEmit(flags, allow);
}

// 0x7100bb66fc
void GroupFolder::silence(bool silence, f32 fade_time) {
    for (auto* node = mTreeNode.child(); node; node = node->next())
        node->value()->silence(silence, fade_time);
}

// 0x7100bb674c
s32 GroupFolder::getStartWaitSoundNum() const {
    s32 num = 0;
    for (auto* node = mTreeNode.child(); node; node = node->next())
        num += node->value()->getStartWaitSoundNum();
    return num;
}

// 0x7100bb6798
bool GroupFolder::pushFrontChild_(Group* child) {
    if (!child)
        return false;
    auto* first = mTreeNode.child();
    if (!first) {
        pushBackChild_(child);
        return true;
    }
    Group* first_group = first->value();
    if (!first_group || first_group == child)
        return false;
    if (first_group->getObjName() == GroupMgr::getDummyGroupName())
        first_group->mTreeNode.insertAfterSelf(&child->mTreeNode);
    else
        mTreeNode.pushFrontChild(&child->mTreeNode);
    return true;
}

// 0x7100bb68cc
bool GroupFolder::pushBackChild_(Group* child) {
    if (!child)
        return false;
    mTreeNode.pushBackChild(&child->mTreeNode);
    return true;
}

// 0x7100bb68f8
bool GroupFolder::insertBeforeChild_(Group* child, Group* before) {
    if (!child || !before)
        return false;
    if (before->getObjName() == GroupMgr::getDummyGroupName())
        before->mTreeNode.insertAfterSelf(&child->mTreeNode);
    else
        before->mTreeNode.insertBeforeSelf(&child->mTreeNode);
    return true;
}

// 0x7100bb69f4
bool GroupFolder::insertAfterChild_(Group* child, Group* after) {
    if (!child || !after)
        return false;
    after->mTreeNode.insertAfterSelf(&child->mTreeNode);
    return true;
}

// 0x7100bb6a20: the grandchildren are moved to this folder
void GroupFolder::removeChild_(Group* child) {
    if (!child)
        return;
    auto* grandchild = child->mTreeNode.child();
    while (grandchild) {
        auto* next = grandchild->next();
        mTreeNode.pushBackChild(grandchild);
        grandchild = next;
    }
    child->mTreeNode.detachAll();
}

// 0x7100bb6bc8
bool GroupFolder::isSoundGroup() const {
    return false;
}

// 0x7100bb6bd0
bool GroupFolder::isGroupFolder() const {
    return true;
}

}  // namespace aal
