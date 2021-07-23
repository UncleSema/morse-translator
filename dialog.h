#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QFileDialog>

class Dialog : QWidget
{
public:
    Dialog();

    enum Mode
    {
        INPUT,
        OUTPUT
    };

    /**
     * Open QFileDialog and return url of chosen file.
    */
    QUrl openDialog(Mode mode);
};

#endif // DIALOG_H
