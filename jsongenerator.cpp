#include <QtWidgets>

#include "jsongenerator.h"

JsonGenerator::JsonGenerator(QTreeWidget *treeWidget)
    : Generator(treeWidget)
{
    escs = QString("");

    for (int i = 0; i < 32; ++i)
        escs.append("\\u").append(QString::number(i, 16).rightJustified(4, '0'));
}

bool JsonGenerator::write(QIODevice *device)
{
    int cnt = treeWidget->topLevelItemCount();
    out.setDevice(device);
    out.setCodec("UTF-8");
    out << "{\n";
    out << indent(1) << "\"folderName\": \"Bookmarks\",\n";
    out << indent(1) << "\"contents\": [\n";

    for (int i = 0; i < cnt; ++i)
        generateItem(treeWidget->topLevelItem(i), 2, i == (cnt - 1));

    out << indent(1) << "]\n";
    out << "}\n";
    return true;
}

QString JsonGenerator::escapedAttribute(const QString &text)
{
    QString result = text;
    result.replace("\\", "\\\\");
    result.replace("\"", "\\\"");
    for (int i = 0; i < 32; ++i)
        result.replace(QChar(i), escs[i]);
    result.replace(QChar(0x7f), "\\u007f");
    result.prepend("\"");
    result.append("\"");
    return result;
}

void JsonGenerator::generateItem(QTreeWidgetItem *item, int depth, bool end)
{
    QString tagName = item->data(0, Qt::UserRole).toString();
    if (tagName == "folder") {
        int cnt = item->childCount();
        out << indent(depth) << "{ \"folderName\": " << escapedAttribute(item->text(0)) << ",\n";
        out << indent(depth) << "\"contents\": [\n";
        for (int i = 0; i < cnt; ++i)
            generateItem(item->child(i), depth + 1, i == (cnt - 1));
        out << indent(depth) << "  ]\n";
        out << indent(depth) << "}";
    } else if (tagName == "bookmark") {
        out << indent(depth) << "{ \"title\": " << escapedAttribute(item->text(0));
        if (!item->text(1).isEmpty())
            out << ", \"url\": " << escapedAttribute(item->text(1));
        out << " }";
    } else if (tagName == "separator") {
        out << indent(depth) << "{}";
    }

    if (!end)
        out << ',';
    out << '\n';
}
