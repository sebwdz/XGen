
#include        <QDir>

#include        "include/MainWidget.hpp"
#include        "include/Manager/Folder.hpp"

Folder::Folder(Folder *parent) : File(parent)
{
    m_name = "New Folder";
}

Folder::~Folder()
{

}

void                    Folder::add_file(File *file)
{
    file->set_parent(this);
    m_file.push_back(file);
}

std::vector<File*>     &Folder::get_file()
{
    return (m_file);
}

void            Folder::close()
{
    for (int it = 0; it < (int)m_widget.size(); it++)
        m_widget[it]->close();
    for (int it = 0; it < (int)m_file.size(); it++)
        m_file[it]->close();
}

void            Folder::remove_file(File *file)
{
    for (int it = 0; it < (int)m_file.size(); it++)
        if (m_file[it] == file)
        {
            file->close();
            delete file;
            m_file.erase(m_file.begin() + it);
            update();
            return ;
        }
}

void            Folder::add_widget_parent(MainWidget *widget)
{
    m_widget.push_back(widget);
}

void            Folder::close_widget_parent(MainWidget *widget)
{
    for (int it = 0; it < (int)m_widget.size(); it++)
    {
        if (m_widget[it] == widget)
        {
            m_widget.erase(m_widget.begin() + it);
            return ;
        }
    }
}

void        Folder::update()
{
    if (m_parent)
        m_parent->update();
    for (int it = 0; it < (int)m_widget.size(); it++)
        m_widget[it]->update();
}

void            Folder::load(std::ifstream &file)
{
    int         size;
    std::string tmp;

    File::load(file);
    file >> size;
    for (int it = 0; it < size; it++)
    {
        file >> tmp;
        if (tmp == "folder")
            m_file.push_back(new Folder(this));
        else
            m_file.push_back(new File(this));
        m_file.back()->load(file);
    }
}

void            Folder::save(std::ofstream &file)
{
    File::save(file);
    file << m_file.size() << std::endl;
    for (int it = 0; it < (int)m_file.size(); it++)
    {
        if (dynamic_cast<Folder*>(m_file[it]))
            file << "folder" << std::endl;
        else
            file << "file" << std::endl;
        m_file[it]->save(file);
    }
}
