
#include        "include/ModelListOpen.hpp"

ModelListOpen::ModelListOpen()
{

}

ModelListOpen::~ModelListOpen()
{

}

void        ModelListOpen::set_folder(Folder *folder)
{
    m_folder = folder;
    update();
}

void        ModelListOpen::update()
{
    clear();
    make_item(0, m_folder);
}

void        ModelListOpen::make_item(OpenItem *parent, File *file)
{
    OpenItem            *item;
    Folder              *folder;

    item = new OpenItem();
    item->set_file(file);
    if ((folder = dynamic_cast<Folder*>(file)))
    {
        for (int it = 0; it < (int)folder->get_file().size(); it++)
            make_item(item, folder->get_file()[it]);
    }
    if (parent)
        parent->appendRow(item);
    else
        appendRow(item);
}
