#include <QtWidgets>

#include "generator.h"

Generator::Generator(QTreeWidget *treeWidget)
    : treeWidget(treeWidget)
{
}

QString Generator::indent(int depth)
{
    const int indentSize = 4;
    return QString(indentSize * depth, ' ');
}


QString Generator::escapedText(const QString &text)
{
    QString result = text;
    result.replace("&", "&amp;");
    result.replace("<", "&lt;");
    result.replace(">", "&gt;");
    return result;
}

QString Generator::escapedAttribute(const QString &text)
{
    QString result = escapedText(text);
    result.replace("\"", "&quot;");
    result.prepend("\"");
    result.append("\"");
    return result;
}
