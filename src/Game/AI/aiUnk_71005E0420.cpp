#include "Game/AI/aiUnk_71005E0420.h"
#include "Game/AI/aiUnk_71007377D4.h"

bool handleItemPickedMessageMaybe(const ksys::Message& message, Unk_71023e0020* listener,
                                  ksys::act::Actor* actor, ksys::act::Actor* other) {
    if (message.getType() != 0x8000071)
        return listener->sub_710070AEE4(message, actor, other);

    if (!other)
        other = actor;
    if (itemCanGetPouch(other) || itemCanNotGetPouch(other)) {
        listener->_3a = false;
        if (triggereGetItemDemoMaybe(other, listener->_38 == 1, false)) {
            listener->_39 = true;
        } else {
            listener->_30 = true;
            listener->_18 = message.getSource();
        }
    }
    return true;
}
