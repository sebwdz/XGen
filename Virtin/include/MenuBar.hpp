#ifndef MENUBAR_HPP
#define MENUBAR_HPP

#include        <qmenubar.h>

class           MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MenuBar(QWidget *parent);
    ~MenuBar();

    void        new_workspace();
    void        open_workspace();
    void        add_widget();
    void        save_workspace();
    void        close_workspace();

public slots:

    void        slot_clicked_work(QAction *action);

private:

    QMenu       *m_work;

};

#endif // MENUBAR_HPP
