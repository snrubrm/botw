#pragma once

#include <container/seadListImpl.h>
#include <math/seadMatrix.h>
#include "KingSystem/Utils/Types.h"

namespace sead { class Heap; }
namespace gsys { class Model; }
namespace ksys::xlink { class XLink; }
namespace ksys::act { class Unk_71024e6428; }
class Unk_710250c840;

namespace ksys::map {

class ActorData;
class Object;

class Unk_7100D4D998 {
public:
    Unk_7100D4D998(ActorData* data, sead::Heap* heap);
    ~Unk_7100D4D998();

    void sub_7100D4DB08();

private:
    // Carried activation 10C88F4 and element setup E3AA34 copy this XLink
    // into the chemical element; construction and teardown establish its type.
    friend class ::Unk_710250c840;
    friend class ksys::act::Unk_71024e6428;

    sead::ListNode mNode;
    xlink::XLink* mXLink;
    gsys::Model* mModel;
    sead::Matrix34f mMatrix;
    Object* mObject;
    f32 mValue;
    u32 _5c;
    bool mInitialized;
    u8 _61[7];
};
KSYS_CHECK_SIZE_NX150(Unk_7100D4D998, 0x68);

}  // namespace ksys::map
