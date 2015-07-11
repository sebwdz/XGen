
#include        "include/ModelListOpen.hpp"

OpenItem::OpenItem() : QStandardItem()
{
    m_file = 0;
    //setEditable(false);
}

OpenItem::~OpenItem()
{

}

void        OpenItem::set_file(File *file)
{
    setText(file->get_name().c_str());
    if (dynamic_cast<Folder*>(file))
        setIcon(QIcon("Picture/folder.png"));
    m_file = file;
}

File       *OpenItem::get_file()
{
    return (m_file);
}
