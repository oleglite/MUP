#ifndef STYLE_H
#define STYLE_H

#include <QtCore>
#include <QDebug>



class Style
{
    friend class Style;
    friend QDebug operator<<(QDebug, const Style&);
    typedef QMap<QString, QString> StringMap;

public:
    Style(const QString& type, StringMap* attributes = 0, Style* inherit = NULL);

    void setAttribute(const QString& name, const QString& value);
    QString getAttribute(const QString& name);

    QString getType();

    QString toCss();

private:
    QString type;
    StringMap attributes;

    static void copyWithReplace(StringMap& to, StringMap& from);
    bool boolAttribute(const QString&);
};

QDebug operator<<(QDebug, const Style&);

#endif // STYLE_H
