#include "fileoutput.h"

FileOutput::FileOutput(QObject *parent) {Q_UNUSED(parent);}

void FileOutput::writeToFile(QString &text)
{
    Dialog dialog;
    QUrl fileUrl = dialog.openDialog(Dialog::OUTPUT);
    QFile file = fileUrl.toLocalFile();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << text;
}
