
#include        <iostream>
#include        "EditWidget.hpp"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
}

SyntaxHighlighter::~SyntaxHighlighter()
{

}

void            SyntaxHighlighter::highlightBlock(const QString &text)
{
    int         it2;

    for (int it = 0; it < text.length(); it++)
    {
        if ((text.at(it).toAscii() == '$' ||
                text.at(it).toAscii() == '%' ||
                text.at(it).toAscii() == '@' ||
                text.at(it).toAscii() == ':' ||
                text.at(it).toAscii() == '&'))
        {
            if (!it || !text.at(it - 1).isLetterOrNumber())
            {
                for (it2 = 0; it + it2 < text.length(); it2++)
                {
                    if (text.at(it + it2).toAscii() == ' ' ||
                        text.at(it + it2).toAscii() == '\t' ||
                        text.at(it + it2).toAscii() == '{' ||
                        text.at(it + it2).toAscii() == '}')
                    break;
                }
                if (text.at(it).toAscii() == '$')
                    setFormat(it, it2, Qt::green);
                else if (text.at(it).toAscii() == ':')
                    setFormat(it, it2, Qt::blue);
                else if (text.at(it).toAscii() == '&')
                    setFormat(it, it2, Qt::darkCyan);
                else if (text.at(it).toAscii() == '%')
                    setFormat(it, it2, QColor(0, 200, 200));
                else
                    setFormat(it, it2, Qt::red);
                it += it2 - 1;
            }
        }
        else if (!text.at(it).isLetterOrNumber())
            setFormat(it, 1, Qt::yellow);
    }
}
