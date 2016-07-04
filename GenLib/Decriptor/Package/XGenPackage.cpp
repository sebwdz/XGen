
#include                "Decriptor/Package/XGenFunction.hpp"

void                    XGenPackage::load(std::string const& file)
{
    GeneticalNode       node;
    node.load_file(file);
    load(&node);
}

void                    XGenPackage::load(GeneticalNode *node)
{
    XGenFunction        *function;

    for (unsigned int it = 0; it < node->get_son().size(); it++)
    {
        function = new XGenFunction();
        function->set_node(node->get_son_ref(it)->get_son_ref(0));
        add_package(node->get_son_ref(it)->get_key(), function);
        function->load(node->get_son_ref(it)->get_son_ref(1).get());
    }
}
