#include <gsys/gsysModelMgrCallback.h>

// 0x7100f1fe40 .. 0x7100f1fe5c: every default of the interface is a four-byte empty function in
// the original, so the out-of-line bodies are empty.
namespace gsys {

void IModelMgrCallback::onInitializeModelResource() {}

void IModelMgrCallback::onAddModel(Model*, sead::Heap*) {}

void IModelMgrCallback::onAddModelUnit() {}

void IModelMgrCallback::onSetUpModelUnitMaterialAndShape() {}

void IModelMgrCallback::onAddModelScene(ModelScene*, sead::Heap*) {}

void IModelMgrCallback::onRemoveModel(Model*) {}

void IModelMgrCallback::callback7() {}

void IModelMgrCallback::callback8() {}

}  // namespace gsys
