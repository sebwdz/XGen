
#include        <QLayout>
#include        <QMessageBox>
#include        <QLabel>
#include        <string>
#include        <stdexcept>

#include        "include/ProprietyWidget.hpp"

ProprietyWidget::ProprietyWidget() : QWidget()
{
    QVBoxLayout     *layout;
    QLabel          *label;

    m_pool = 0;
    m_edit = new QTextEdit();
    layout = new QVBoxLayout();
    label = new QLabel("Genetic Propriety");

    layout->addWidget(label);
    layout->addWidget(m_edit);
    setLayout(layout);
}

ProprietyWidget::~ProprietyWidget()
{

}

void        ProprietyWidget::set_pool(GeneticalPool *pool)
{
    GeneticPropriety    *propriety;

    m_pool = pool;
    propriety = pool->get_propriety().get();
    m_edit->clear();
    m_edit->insertPlainText(QVariant(propriety->height).toString());
    m_edit->insertPlainText(" ");
    m_edit->insertPlainText(QVariant(propriety->len).toString());
    m_edit->insertPlainText("\n");
    for (int it = 0; it < (int)propriety->range.size(); it++)
    {
        m_edit->insertPlainText(QVariant(propriety->range[it].first).toString());
        m_edit->insertPlainText(" ");
        m_edit->insertPlainText(QVariant(propriety->range[it].second).toString());
        if (it < (int)propriety->range.size() - 1)
            m_edit->insertPlainText("\n");
    }
}

void        ProprietyWidget::change()
{
    std::string     str;
    std::size_t     pos;
    std::size_t     end;
    std::pair<int,int>  range;
    GeneticPropriety    *propriety;

    propriety = m_pool->get_propriety().get();
    if (!propriety)
        std::cout << "crash" << std::endl;
    try
    {
        str = m_edit->toPlainText().toStdString();
        pos = str.find_first_not_of("\t \n");
        end = str.find_first_of("\n \t", pos);
        propriety->height = atoi(str.substr(pos, end).c_str());
        pos = str.find_first_not_of("\n \t", end);
        end = str.find_first_of("\n\t ", pos);
        propriety->len = atoi(str.substr(pos, end).c_str());
        propriety->range.clear();
        pos = str.find_first_not_of("\n\t ", end);
        while (pos != std::string::npos)
        {
            end = str.find_first_of("\t\n ", pos);
            range.first = atoi(str.substr(pos, end).c_str());
            pos = str.find_first_not_of("\n\t ", end);
            end = str.find_first_of("\n \t", pos);
            range.second = atoi(str.substr(pos, end).c_str());
            propriety->range.push_back(range);
            pos = str.find_first_not_of("\n\t ", end);
        }
    }
    catch (std::out_of_range)
    {
        QMessageBox::critical(this, "Error", "Syntax Error with propriety !");
    }
}
