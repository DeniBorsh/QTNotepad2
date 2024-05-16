#pragma once
#include <QtWidgets>
#include "docwindow.h"

class MDIProgram : public QMainWindow {
Q_OBJECT
public:
    MDIProgram(QWidget *parent = nullptr);
private:
    QMdiArea* m_area;
    QMenu* m_windowsMenu;
    QSignalMapper* m_signalMapper;

    DocWindow* createNewDoc();
private slots:
    void slotChangeWindowTitle(const QString&);
    void slotNewDoc();
    void slotLoad();
    void slotSave();
    void slotSaveAs();
    void slotAbout();
    void slotWindows();
    void slotSetActiveSebWindow(QWidget*);
};
