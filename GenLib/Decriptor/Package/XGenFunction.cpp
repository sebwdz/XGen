
#include                "Decriptor/Package/XGenFunction.hpp"

SMART(GeneticalNode)            XGenFunction::call(Decriptor *d, GeneticalNode *block, SMART(GeneticalNode) av)
{
    m_node->set_block(block);
    av->copy(d->get_fast()->get_ass(Chanel::hash("__av__")));
    return (d->turn(m_node.get()));
}
