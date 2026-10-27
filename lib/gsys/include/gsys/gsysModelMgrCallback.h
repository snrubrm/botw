#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}

namespace gsys {

class Model;
class ModelScene;

// Model-renderer callback interface of the map / far / grudge renderers (the 12-slot secondary
// table at Unk_7100f185a4 +0x8, vtable 0x71024f42c8). Eight of its virtuals are four-byte empty
// defaults in the original (0x7100f1fe40 .. 0x7100f1fe5c); the renderer object overrides the
// other four (0x7100f1f2f8, 0x7100f1f1f4, 0x7100f1f0e8, 0x7100f1f170).
// The slots the empty defaults occupy are 0, 1, 2, 4, 5, 6, 7 and 8, so the unoverridden
// callback at index 3 and the three trailing virtuals are modelled as pure virtuals.
// The argument lists of the empty defaults cannot be recovered from the retail bodies; no
// override of those slots exists in the binary.
class IModelMgrCallback {
public:
    virtual void onInitializeModelResource();
    virtual void onAddModel(Model* model, sead::Heap* heap);
    virtual void onAddModelUnit();
    // 0x7100f1fd00 (a +8 adjusting thunk) forwards to the renderer's 0x7100f1f2f8.
    virtual void m3() = 0;
    virtual void onSetUpModelUnitMaterialAndShape();
    virtual void onAddModelScene(ModelScene* scene, sead::Heap* heap);
    virtual void onRemoveModel(Model* model);
    virtual void callback7();
    virtual void callback8();
    // 0x7100f1f1f4 / 0x7100f1f0e8 / 0x7100f1f170.
    virtual void m9() = 0;
    virtual void m10() = 0;
    virtual void m11() = 0;
};

}  // namespace gsys
