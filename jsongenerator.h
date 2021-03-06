#ifndef JSONGENERATOR_H
#define JSONGENERATOR_H

#include <QTextStream>
#include "generator.h"

QT_BEGIN_NAMESPACE
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class JsonGenerator : public Generator
{
public:
    JsonGenerator(QTreeWidget *treeWidget);

    bool write(QIODevice *device);

    ~JsonGenerator() {}

protected:
    void generateItem(QTreeWidgetItem *item, int depth, bool end);
    QString escapedAttribute(const QString &text);

    QString escs;
};

#endif // JSONGENERATOR_H

