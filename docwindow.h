#pragma once
#include <QtWidgets>

class DocWindow : public QTextEdit {
Q_OBJECT
public:
    DocWindow(QWidget *parent = nullptr);
signals:
    void changeWindowTitle(const QString&);
public slots:
    void load();
    void save();
    void saveAs();
private:
    QString m_fileName;
};

