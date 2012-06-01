#include "mainwindow.h"

MainWindow::MainWindow():
    mWebView(0),
    mSearchEdit(0),
    mFileMenu(0),
    mOpenAct(0),
    mRefreshAct(0),
    mExitAct(0),
    mPage(0)
{
    createActions();
    createMenus();
    createCentralWidget();

    connect(mWebView, SIGNAL(linkClicked(QUrl)), this, SLOT(openLink(QUrl)));

    setFilePath("D:/Development/Qt/mup/mups/water.mup");
    openPage();
    refresh();
}

MainWindow::~MainWindow(){
    delete mPage;
}

void MainWindow::createActions(){
    mOpenAct = new QAction("Open", this);
    mOpenAct->setShortcuts(QKeySequence::Open);
    mOpenAct->setStatusTip("Open Mup file");
    connect(mOpenAct, SIGNAL(triggered()), SLOT(openWithDialog()));

    mRefreshAct = new QAction("Refresh", this);
    mRefreshAct->setShortcuts(QKeySequence::Refresh);
    mRefreshAct->setStatusTip("Refresh");
    connect(mRefreshAct, SIGNAL(triggered()), SLOT(refresh()));

    mExitAct = new QAction("Exit", this);
    mExitAct->setStatusTip("Exit the application");
    mExitAct->setShortcuts(QKeySequence::Quit);
    connect(mExitAct, SIGNAL(triggered()), SLOT(close()));
}

void MainWindow::createMenus(){
    mFileMenu = menuBar()->addMenu("File");
    mFileMenu->addAction(mOpenAct);
    mFileMenu->addAction(mRefreshAct);
    mFileMenu->addSeparator();
    mFileMenu->addAction(mExitAct);
}

void MainWindow::createCentralWidget(){
    QWidget* mainWidget = new QWidget();

    QGridLayout* centaralLayout = new QGridLayout();
    centaralLayout->setColumnStretch(1, 0);

    mWebView = new QWebView();
    mWebView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    mSearchEdit = new QLineEdit();

    centaralLayout->addWidget(mSearchEdit, 0, 0);
    centaralLayout->addWidget(mWebView, 1, 0);
    mainWidget->setLayout(centaralLayout);

    setCentralWidget(mainWidget);
    connect(mSearchEdit, SIGNAL(returnPressed()), SLOT(search()));
}

void MainWindow::openWithDialog(){
    setFilePath(QFileDialog::getOpenFileName(this, "Open Mup File", "", "*.mup"));
    openPage();
    refresh();
}

void MainWindow::openLink(const QUrl& url){
    mFileName = url.toString();
    qDebug() << "openLink" << mFileName;
    openPage();
    refresh();
}

void MainWindow::refresh(){
    qDebug() << mPage->toHtml();
    mWebView->setHtml(mPage->toHtml());
}

void MainWindow::openPage(){
    const QString& path = getFilePath();
    if (!path.isEmpty()){
        Q_ASSERT(path.endsWith(".mup"));

        QString mup = openFile(path);
        if(mup == "")
            return;
        QString textfileName = path;
        textfileName.replace(".mup", ".mtxt");
        QString text = openFile(textfileName);


        setPage(MupLoader::load(mup, text));
    }
}

QString MainWindow::openFile(const QString& fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, "Unable to open file", file.errorString());
        return "";
    }
    QTextStream out(&file);
    return out.readAll();
}

QString MainWindow::getFilePath() const{
    return mFileDirectory + mFileName;
}

void MainWindow::setFilePath(const QString& path){
    int slashPostion = path.lastIndexOf('/');
    mFileName = path.mid(slashPostion+1);
    mFileDirectory = path.mid(0, slashPostion+1);
}

void MainWindow::search(){
    qDebug() << "searching";

    QDir currentDir(mFileDirectory);
    const QStringList& dirEntryList = currentDir.entryList(QStringList() << "*.mtxt");

    SearchGenerator searcher(mSearchEdit->text());

    foreach(QString file, dirEntryList){
        QString mupFile = file;
        searcher.search(MupLoader::loadPageText(openFile(mFileDirectory + file)), mupFile.replace(".mtxt", ".mup"));
    }
    setPage(searcher.getResultPage());
    refresh();
}

void MainWindow::setPage(PageMarkup* page){
    if(mPage)
        delete mPage;
    mPage = page;
}
