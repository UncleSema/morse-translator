#ifndef FILEINPUT_H
#define FILEINPUT_H

#include <QObject>

#include "dialog.h"

class FileInput : public QObject
{
    Q_OBJECT
public:
    FileInput(QObject *parent = 0);

    /**
     * Open Dialog and read from chosen file.'
    */
    Q_INVOKABLE QString readFromFile();
};

#endif // FILEINPUT_H
