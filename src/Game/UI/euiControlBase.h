#pragma once

#include <basis/seadTypes.h>
#include <cstddef>
#include <nn/font/font_Util.h>

namespace eui {

class LayoutEx;

// Circular intrusive list node with the layout of nn::util::IntrusiveListNode. lib/NintendoSDK only declares
// IntrusiveListImplementation::push_front (the original inlines it, e.g. in ButtonBase::On), so the inline
// pieces live here until the SDK header has them.
struct ListNode {
    ListNode() : prev(this), next(this) {}

    bool isLinked() const { return next != this; }
    // nn::util::IntrusiveListNode::LinkNext(node): inserts `first` right behind this node
    void linkNext(ListNode* first) {
        ListNode* last = first->prev;
        first->prev = this;
        last->next = next;
        next->prev = last;
        next = first;
    }

    // nn::util::IntrusiveListNode::LinkPrev(node): inserts `first` right before this node (push_back on a root)
    void linkPrev(ListNode* first) {
        ListNode* last = first->prev;
        first->prev = prev;
        last->next = this;
        prev->next = first;
        prev = last;
    }
    // nn::util::IntrusiveListNode::Unlink()
    void unlink() {
        ListNode* last = next;
        ListNode* node = last->prev;
        prev->next = last;
        last->prev = prev;
        node->next = this;
        prev = node;
    }

    ListNode* prev;
    ListNode* next;
};

// Base of the eui controls (buttons, animators' owners, the screens' child components...). Slot 0 is the class name,
// slot 1 the nn-style runtime type info, 2 / 3 the destructor, 4 the per-frame update.
class ControlBase {
public:
    virtual const char* getClassName() const { return "ControlBase"; }
    NN_RUNTIME_TYPEINFO_BASE()
    virtual ~ControlBase();
    virtual void Update(f32 dt) {}

    ControlBase();

    // The control behind a node of its owner's list (`_8` is the node)
    static ControlBase* fromNode(ListNode* node) {
        return reinterpret_cast<ControlBase*>(reinterpret_cast<char*>(node) - offsetof(ControlBase, _8));
    }
    static const ControlBase* fromNode(const ListNode* node) {
        return reinterpret_cast<const ControlBase*>(reinterpret_cast<const char*>(node) -
                                                    offsetof(ControlBase, _8));
    }

    // 0x8: an (initially empty) list of the control's children (guess; empty in every control seen so far)
    /* 0x08 */ ListNode _8;
    /* 0x18 */ const char* mName = nullptr;  // the name of the control's root pane (or of the layout)
    /* 0x20 */ LayoutEx* mLayout = nullptr;
};
static_assert(sizeof(ControlBase) == 0x28);

}  // namespace eui
