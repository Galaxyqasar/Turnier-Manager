#include "playereditdialog.h"
#include "ui_playereditdialog.h"

PlayerEditDialog::PlayerEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerEditDialog)
{
    ui->setupUi(this);
}

PlayerEditDialog::~PlayerEditDialog()
{
    delete ui;
}

QString PlayerEditDialog::getText()
{
    return ui->plainTextEdit->toPlainText();
}

void PlayerEditDialog::setText(QString text)
{
    ui->plainTextEdit->setPlainText(text);
}
