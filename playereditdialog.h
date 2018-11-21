#ifndef PLAYEREDITDIALOG_H
#define PLAYEREDITDIALOG_H

#include <QDialog>

namespace Ui {
class PlayerEditDialog;
}

class PlayerEditDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PlayerEditDialog(QWidget *parent = nullptr);
    ~PlayerEditDialog();
    QString getText();
    void setText(QString text);
    
private:
    Ui::PlayerEditDialog *ui;
};

#endif // PLAYEREDITDIALOG_H
