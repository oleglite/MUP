#ifndef MUPELEMENT_H
#define MUPELEMENT_H

#include <QStringList>

class MupElement
{
public:
    MupElement(const QString& label, bool isSingle = false);

    void setStyle(QString);

    QString getLabel() const;
    QString getStyle() const;
    QString getGrouping() const;
    QString getType() const;

    // ���������� true ���� ������ ��� �������� ��� ���, �� �������� �� �����������
    virtual bool checkType(const QString&) const;

    QString toHtml();

    static QString getGroupFromStyle(QString& style, bool removeOn = 1);
    static QString toHtmlAttribute(const QString& name, const QString& value);

protected:
    virtual QString contentToHtml() = 0;
    virtual QString tagName() = 0;
    virtual QString groupElementOpenTag() = 0;
    virtual QString groupElementCloseTag() = 0;
    virtual QString tagAttributs();

protected:
    QString type;

private:
    QString label;
    QString style;
    QString grouping;

    bool isSingleTag;
};

#endif // MUPELEMENT_H
