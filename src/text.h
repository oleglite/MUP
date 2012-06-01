#ifndef TEXT_H
#define TEXT_H

#include <QStringList>
#include <QPair>
#include <QMap>

// пара текст, метаинформация
typedef QPair<QString, QStringList> TextElement;

class Text
{
public:
    static const int MIN_SEARCH_WORD_LENGTH = 2;

public:
    Text();
    ~Text();

    void add(const QString& name, const QString& text, const QStringList& meta);
    const QString* getText(const QString& name) const;

    bool isEmpty() const;
    QList<const TextElement*> getElementList() const;

private:
    QMap<QString, TextElement*> mText;

};

#endif // TEXT_H
