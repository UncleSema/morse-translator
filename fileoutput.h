#ifndef FILEOUTPUT_H
#define FILEOUTPUT_H

#include <QObject>

#include "dialog.h"

class FileOutput : public QObject
{
    Q_OBJECT
public:
    FileOutput(QObject *parent = 0);

    /**
     * Open Dialog and write to chosen file.'
    */
    Q_INVOKABLE void writeToFile(QString &text);
};

#endif // FILEOUTPUT_H
