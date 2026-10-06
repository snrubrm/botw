#include "aal/aalAttenuationComponentListReflexer.h"

namespace aal {

template class AttenuationComponentListReflexer<Attenuator>;
template class AttenuationComponentListReflexer<Curve>;
template class AttenuationComponentListReflexer<AttenuationCulling>;
template class AttenuationComponentListReflexer<AttenuationDirectivity>;

}  // namespace aal
