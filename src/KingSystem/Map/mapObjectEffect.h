#pragma once

#include <container/seadListImpl.h>
#include <math/seadMatrix.h>
#include "KingSystem/Utils/Types.h"

namespace sead { class Heap; }
namespace gsys { class Model; }
namespace ksys::xlink { class XLink; }

namespace ksys::map {

class ActorData;
class Object;

class Unk_7100D4D998 {
public:
    Unk_7100D4D998(ActorData* data, sead::Heap* heap);
    ~Unk_7100D4D998();

    void sub_7100D4DB08();

private:
    sead::ListNode mNode;
    xlink::XLink* mXLink;
    gsys::Model* mModel;
    sead::Matrix34f mMatrix;
    Object* mObject;
    f32 mValue;
    u8 _5c[4];
    bool mInitialized;
    u8 _61[7];
};
KSYS_CHECK_SIZE_NX150(Unk_7100D4D998, 0x68);

}  // namespace ksys::map
