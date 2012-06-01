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

    //! ��� �����, � ������� ��������.
    QString mFileName;

    //! �����, � ������� ��������.
    QString mFileDirectory;

    //! ������� ��������.
    PageMarkup* mPage;

private:
    // ������ ��� �������� ��������� ����
    void createActions();
    void createMenus();
    void createCentralWidget();

    void setPage(PageMarkup* page);

    //! ������ ���� @p path ��������� � ��������� � mFileDirectory � mFileName.
    void setFilePath(const QString& path);

    //! ���������� ������ ���� �������� �����.
    QString getFilePath() const;

    //! ��������� ���� �� ������� ���� @p mFileName, @return ����������� ������.
    QString openFile(const QString& mFileName);

    //! ��������� ������� ���� � mWebView
    void openPage();
};

#endif // MAINWINDOW_H
