#pragma once

#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

namespace gsys {

class Model;
class ModelInfo;
class ModelUnit;

// Native 0x7100c4bb40 installs the Node-derived vtable and initializes this
// 0x30-byte group. Model::createUnitGroup links groups through +0x28.
class ModelUnitGroup : public sead::hostio::Node {
public:
    struct CreateArg {
        // Native 0x7100c4baac constructs 256 SafeStrings and stores the count
        // at +0x1000. The second index uses SafeArray's unsigned bounds check.
        CreateArg(const sead::SafeString& first, const sead::SafeString& second);

        sead::SafeArray<sead::SafeString, 256> mNames;
        s32 mCount;
    };

    ModelUnitGroup(const CreateArg& arg, Model* model, sead::Heap* heap,
                   sead::Heap* hostio_heap);
    virtual ~ModelUnitGroup();

    // Native 0x7100c4bc9c selects a ModelInfo and returns its ModelUnit pointer.
    ModelUnit* setCurrent(s32 index);

private:
    Model* mModel;
    sead::PtrArray<ModelInfo> mUnits;
    ModelInfo* mCurrent;
    ModelUnitGroup* mNext;
};
static_assert(sizeof(ModelUnitGroup::CreateArg) == 0x1008);
static_assert(offsetof(ModelUnitGroup::CreateArg, mCount) == 0x1000);
static_assert(sizeof(ModelUnitGroup) == 0x30);

}  // namespace gsys
