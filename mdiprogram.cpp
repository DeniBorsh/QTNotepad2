#include "mdiprogram.h"

MDIProgram::MDIProgram(QWidget *parent) : QMainWindow(parent) {
    auto actionNew = new QAction("New File", 0);
    actionNew->setText("&New");
    actionNew->setShortcut(QKeySequence("CTRL+N"));
    actionNew->setToolTip("New Document");
    actionNew->setStatusTip("Create a new file");
    actionNew->setWhatsThis("Create a new file");
    //actionNew->setIcon(QPixmap(":/newfile.png");
    connect(actionNew, SIGNAL(triggered()), SLOT(slotNewDoc()));

    auto actionOpen = new QAction("Open File", 0);
    actionOpen->setText("&Open...");
    actionOpen->setShortcut(QKeySequence("CTRL+O"));
    actionOpen->setToolTip("Open Document");
    actionOpen->setStatusTip("Open an existing file");
    actionOpen->setWhatsThis("Open an existing file");
    //actionOpen->setIcon(QPixmap(":/openfile.png");
    connect(actionNew, SIGNAL(triggered()), SLOT(slotLoad()));

    auto actionSave = new QAction("Save File", 0);
    actionSave->setText("&Save");
    actionSave->setShortcut(QKeySequence("CTRL+S"));
    actionSave->setToolTip("Save Document");
    actionSave->setStatusTip("Save the file to disk");
    actionSave->setWhatsThis("Save the file to disk");
    //actionSave->setIcon(QPixmap(":/savefile.png");
    connect(actionNew, SIGNAL(triggered()), SLOT(slotSave()));

    QToolBar* fileOperations = new QToolBar("File Operations");
    fileOperations->addAction(actionNew);
    fileOperations->addAction(actionOpen);
    fileOperations->addAction(actionSave);
    addToolBar(Qt::TopToolBarArea, fileOperations);

    QMenu* fileMenu = new QMenu("&File");
    fileMenu->addAction(actionNew);
    fileMenu->addAction(actionOpen);
    fileMenu->addAction(actionSave);
    fileMenu->addAction("Save &As...", this, SLOT(slotSaveAs()));
    fileMenu->addSeparator();
    fileMenu->addAction("&Quit",
                              qApp,
                              SLOT(closeAllWindows()),
                              QKeySequence("CTRL+Q"));
    menuBar()->addMenu(fileMenu);

    m_windowsMenu = new QMenu("&Windows");
    menuBar()->addMenu(m_windowsMenu);
    connect(m_windowsMenu, SIGNAL(aboutToShow()), SLOT(slotWindows()));
    menuBar()->addSeparator();

    QMenu* helpMenu = new QMenu("&Help");
    helpMenu->addAction("&About", this, SLOT(slotAbout()), Qt::Key_F1);
    menuBar()->addMenu(helpMenu);

    m_area = new QMdiArea;
    m_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    setCentralWidget(m_area);

    m_signalMapper = new QSignalMapper(this);
    connect(m_signalMapper,
            SIGNAL(mapped(QWidget*)),
            this,
            SLOT(slotSetActiveSebWindow(QWidget*)));

    statusBar()->showMessage("Ready", 3000);


}

void MDIProgram::slotNewDoc() {
    createNewDoc()->show();
}

DocWindow* MDIProgram::createNewDoc() {
    DocWindow* doc = new DocWindow;
    m_area->addSubWindow(doc);
    doc->setAttribute(Qt::WA_DeleteOnClose);
    doc->setWindowTitle("Unnamed Document");
    //doc->setWindowIcon(QPixmap(":/newfile.png"));
    connect(doc,
            SIGNAL(changeWindowTitle(const QString&)),
            SLOT(slotChangeWindowTitle(const QString&)));
    return doc;
}

void MDIProgram::slotChangeWindowTitle(const QString& str) {
    qobject_cast<DocWindow*>(sender())->setWindowTitle(str);
}

void MDIProgram::slotLoad() {
    DocWindow* doc = createNewDoc();
    doc->load();
    doc->show();
}

void MDIProgram::slotSave() {
    DocWindow* doc = qobject_cast<DocWindow*>(m_area->activeSubWindow());
    if (doc) doc->save();
}


void MDIProgram::slotSaveAs() {
    DocWindow* doc = qobject_cast<DocWindow*>(m_area->activeSubWindow());
    if (doc) doc->saveAs();
}

void MDIProgram::slotAbout() {
    QMessageBox::about(this, "Application", "MDI Example");
}

void MDIProgram::slotWindows() {
    m_windowsMenu->clear();

    QAction* action = m_windowsMenu->addAction("&Cascade",
                                               m_area,
                                               SLOT(cascadeSubWindows()));
    action->setEnabled(!m_area->subWindowList().isEmpty());

    action = m_windowsMenu->addAction("&Tile",
                                      m_area,
                                      SLOT(tileSubWindows()));
    action->setEnabled(!m_area->subWindowList().isEmpty());
    m_windowsMenu->addSeparator();
    QList<QMdiSubWindow*> docList = m_area->subWindowList();
    for (int i = 0; i < docList.size(); ++i) {
        action = m_windowsMenu->addAction(docList[i]->windowTitle());
        action->setCheckable(true);
        action->setChecked(m_area->activeSubWindow() == docList[i]);
        connect(action, SIGNAL(triggered()), m_signalMapper, SLOT(map()));
        m_signalMapper->setMapping(action, docList[i]);
    }
}

void MDIProgram::slotSetActiveSebWindow(QWidget* widget) {
    if (widget) m_area->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(widget));
}































