#ifndef GENETICPROPRIETY_CPP
#define GENETICPROPRIETY_CPP

#include        <QWidget>
#include        <QTextEdit>
#include        <QPushButton>

#include        <Genetic/GeneticalPool.hpp>

class           ProprietyWidget : public QWidget
{
    Q_OBJECT
public:
    ProprietyWidget();
    ~ProprietyWidget();

    void        set_pool(GeneticalPool *pool);

    void        change();
private:

    QTextEdit           *m_edit;
    GeneticalPool       *m_pool;
};

#endif // GENETICPROPRIETY_CPP
