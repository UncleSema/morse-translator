#include "fileinput.h"

FileInput::FileInput(QObject *parent) {Q_UNUSED(parent);}

QString FileInput::readFromFile()
{
    Dialog dialog;
    QUrl fileUrl = dialog.openDialog(Dialog::INPUT);
    QFile file = fileUrl.toLocalFile();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "__CANCELED";
    return QString(file.readAll());
}
