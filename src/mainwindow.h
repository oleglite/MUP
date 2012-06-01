#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWebKit/QWebView>
#include <QtGui>
#include "muploader.h"
#include "searchgenerator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    void openLink(const QUrl& url);

private slots:
    void openWithDialog();
    void refresh();
    void search();

private:
    // UI
    QWebView* mWebView;
    QLineEdit* mSearchEdit;
    QMenu* mFileMenu;

    // ACTIONS
    QAction* mOpenAct;
    QAction* mRefreshAct;
    QAction* mExitAct;

    //! Имя файла, с которым работаем.
    QString mFileName;

    //! Папка, в которой работаем.
    QString mFileDirectory;

    //! Текущая страница.
    PageMarkup* mPage;

private:
    // методы для создания элементов окна
    void createActions();
    void createMenus();
    void createCentralWidget();

    void setPage(PageMarkup* page);

    //! Полный путь @p path разбивает и сохраняет в mFileDirectory и mFileName.
    void setFilePath(const QString& path);

    //! Возвращает полный путь рабочего файла.
    QString getFilePath() const;

    //! Открывает файл по полному пути @p mFileName, @return извлеченные данные.
    QString openFile(const QString& mFileName);

    //! Открывает рабочий файл в mWebView
    void openPage();
};

#endif // MAINWINDOW_H
