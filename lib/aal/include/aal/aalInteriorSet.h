#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>

namespace sead {
class Heap;
}

namespace aal {

class Interior;
enum class InteriorType : u32;

/// The interiors (one per speaker setup type) of an output device.
class InteriorSet : public sead::hostio::Node {
public:
    InteriorSet();
    virtual ~InteriorSet();

    void initialize(const sead::Buffer<InteriorType>& types, sead::Heap* heap);
    Interior* getInterior(s32 index) const;
    s32 getNumOfInterior() const;
    void setInteriorSize(f32 size);

private:
    sead::PtrArray<Interior> mInteriors;
    s32 mCurrentIndex;
};

}  // namespace aal
