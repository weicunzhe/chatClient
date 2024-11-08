#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <functional>
#include "global.h"
#include "qjsonobject.h"
#include "qmap.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_get_code_clicked();
    void slot_register_module_finish(RequestId id, QString res, ErrorCodes err);

private:
    void initHttpHandlers();
    void showTip(QString str,bool b_ok);
    Ui::RegisterDialog *ui;
    QMap<RequestId,std::function<void(const QJsonObject&)>> _handlers;
};

#endif // REGISTERDIALOG_H
