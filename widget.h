#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui
{
     class Widget;
}

class QStandardItemModel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonA_clicked();
    void on_pushButtonB_clicked();
    void on_pushButtonR_clicked();
    void on_pushButtonCalculate_clicked();
    void on_pushButtonExit_clicked();
    void on_spinBoxRowNumberA_valueChanged(int arg1);
    void on_spinBoxColumnNumberA_valueChanged(int arg1);
    void on_spinBoxRowNumberB_valueChanged(int arg1);
    void on_spinBoxColumnNumberB_valueChanged(int arg1);
    void on_comboBoxA_currentIndexChanged(int index);
    void on_comboBoxB_currentIndexChanged(int index);
    void on_comboBoxR_currentIndexChanged(int index);
    void unaryOperation(QStandardItemModel *inputModel, QStandardItemModel *outputModel,
                                int operationIndex, double scalarValue);
    void synchronizeMatrixes(QStandardItemModel *model1,
                                     QStandardItemModel *model2,int arg1);
    void on_comboBoxBinaryOperation_currentIndexChanged(int index);
    double getValueAt(QStandardItemModel *model, int i, int j) const;
    void appendTo(QStandardItemModel *model, double value) const;

private:
    Ui::Widget *ui;
    QStandardItemModel *mModelA;
    QStandardItemModel *mModelB;
    QStandardItemModel *mModelR;
    QStandardItemModel *mModelA2;
    QStandardItemModel *mModelB2;
    QStandardItemModel *mModelR2;
};

#endif // WIDGET_H
