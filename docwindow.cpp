#include "docwindow.h"

DocWindow::DocWindow(QWidget *parent) : QTextEdit(parent)
{
}

void DocWindow::load() {
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        setPlainText(stream.readAll());
        file.close();

        m_fileName = fileName;
        emit changeWindowTitle(m_fileName);
    }
}

void DocWindow::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(0, m_fileName);
    if (!fileName.isEmpty()) {
        m_fileName = fileName;
        DocWindow::save();
    }
}

void DocWindow::save() {
    if (m_fileName.isEmpty()) {
        saveAs();
        return;
    }

    QFile file(m_fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << toPlainText();
        file.close();
        emit changeWindowTitle(m_fileName);
    }
}

