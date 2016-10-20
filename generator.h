#ifndef GENERATOR_H
#define GENERATOR_H

#include <QTextStream>

QT_BEGIN_NAMESPACE
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class Generator {
public:
    Generator(QTreeWidget *treeWidget);
    virtual bool write(QIODevice *device) = 0;
    virtual ~Generator() {}
protected:
    static QString indent(int depth);
    static QString escapedText(const QString &text);
    static QString escapedAttribute(const QString &text);

    QTreeWidget *treeWidget;
    QTextStream out;
};

#endif // GENERATOR_H

