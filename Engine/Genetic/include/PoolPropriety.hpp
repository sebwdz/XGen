#ifndef POOLPROPRIETY_HPP
#define POOLPROPRIETY_HPP

#include        <QSpinBox>
#include        <QGroupBox>
#include        <Genetic/GeneticalPool.hpp>

#include        "include/ProprietyWidget.hpp"

class           PoolPropriety : public QGroupBox
{
    Q_OBJECT
public:
    PoolPropriety();
    ~PoolPropriety();

    void        set_pool(GeneticalPool *pool);

    void        change();

public slots:
    void        valide();
private:

    QPushButton     *m_valide;
    QSpinBox        *m_len;
    QSpinBox        *m_height;
    QSpinBox        *m_size;
    GeneticalPool   *m_pool;
    ProprietyWidget *m_gentetic;
};

#endif // POOLPROPRIETY_HPP
