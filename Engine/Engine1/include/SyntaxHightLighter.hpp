#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include        <QSyntaxHighlighter>

class           SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SyntaxHighlighter(QTextDocument *parent);
    ~SyntaxHighlighter();

    void        highlightBlock(const QString &text);
};

#endif // SYNTAXHIGHLIGHTER_H
