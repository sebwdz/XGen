#ifndef FOLDER_HPP
#define FOLDER_HPP

#include        "OpenFile.hpp"

typedef struct  MainWidget MainWidget;

class       Folder : public File
{
public:
    Folder(Folder *parent = 0);
    virtual ~Folder();

    void                    add_file(File *file);
    std::vector<File*>      &get_file();

    void            add_widget_parent(MainWidget *widget);
    void            close_widget_parent(MainWidget *widget);

    void            close();
    void            remove_file(File *file);
    void            update();

    virtual void            load(std::ifstream &file);
    virtual void            save(std::ofstream &file);

protected:

    std::vector<File*>          m_file;
    std::vector<MainWidget*>    m_widget;
};

#endif // FOLDER_HPP
