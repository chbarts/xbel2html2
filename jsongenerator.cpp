#include <QtWidgets>

#include "jsongenerator.h"

JsonGenerator::JsonGenerator(QTreeWidget *treeWidget)
    : Generator(treeWidget)
{
}

bool JsonGenerator::write(QIODevice *device)
{
    int cnt = treeWidget->topLevelItemCount();
    out.setDevice(device);
    out.setCodec("UTF-8");
    out << "{\n";
    out << indent(1) << "\"Bookmarks\": {\n";

    for (int i = 0; i < cnt; ++i)
        generateItem(treeWidget->topLevelItem(i), 2, i == (cnt - 1));

    out << indent(1) << "}\n";
    out << "}\n";
    return true;
}

void JsonGenerator::generateItem(QTreeWidgetItem *item, int depth, bool end)
{
    QString tagName = item->data(0, Qt::UserRole).toString();
    if (tagName == "folder") {
        int cnt = item->childCount();
        out << indent(depth) << escapedAttribute(item->text(0)) << ": {\n";
        for (int i = 0; i < cnt; ++i)
            generateItem(item->child(i), depth + 1, i == (cnt - 1));
        out << indent(depth) << "}";
    } else if (tagName == "bookmark") {
        out << indent(depth) << escapedAttribute(item->text(0));
        if (!item->text(1).isEmpty())
            out << ": " << escapedAttribute(item->text(1));
    } else if (tagName == "separator") {
        out << indent(depth) << "{}";
    }

    if (!end)
        out << ',';
    out << '\n';
}
