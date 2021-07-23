#include "dialog.h"

Dialog::Dialog() {}

QUrl Dialog::openDialog(Mode mode)
{
   if (mode == INPUT)
       return QFileDialog::getOpenFileUrl(this,
                      tr("Open Text"), QString("/"), tr("Text Files (*.txt)"));
   return QFileDialog::getSaveFileUrl(this,
                      tr("Open Text"), QString("/"), tr("Text Files (*.txt)"));
}
