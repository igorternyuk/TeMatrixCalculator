#include "widget.h"
#include "matrix.h"
#include "ui_widget.h"
#include "doublespinboxdelegate.h"
#include <QStandardItemModel>
#ifdef DEBUG
#include <QDebug>
#endif
using namespace iat;

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget)
{
    ui->setupUi(this);
    mModelA = new QStandardItemModel(this);
    mModelB = new QStandardItemModel(this);
    mModelR = new QStandardItemModel(this);
    mModelA2 = new QStandardItemModel(this);
    mModelB2 = new QStandardItemModel(this);
    mModelR2 = new QStandardItemModel(this);
    ui->tableViewA->setModel(mModelA);
    ui->tableViewB->setModel(mModelB);
    ui->tableViewR->setModel(mModelR);
    ui->tableViewA2->setModel(mModelA2);
    ui->tableViewB2->setModel(mModelB2);
    ui->tableViewR2->setModel(mModelR2);
    ui->tableViewA->setItemDelegate(new DoubleSpinBoxDelegate(this));
    ui->tableViewB->setItemDelegate(new DoubleSpinBoxDelegate(this));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::synchronizeMatrixes(QStandardItemModel *model1,
                                 QStandardItemModel *model2,int arg1)
{
    switch(arg1)
    {
      case 0: model2->setColumnCount(model1->rowCount());
              model2->setRowCount(model1->columnCount());
              break;
      case 1:
      case 2: model2->setRowCount(model1->rowCount());
              model2->setColumnCount(model1->rowCount());
              break;
      case 3:
      case 4:
      case 5:
      case 6: model2->setRowCount(model1->rowCount());
              model2->setColumnCount(model1->columnCount());
              break;
      case 7:
      case 8: model2->setRowCount(1);
              model2->setColumnCount(1);
              break;
      default: break;
    }
}
void Widget::unaryOperation(QStandardItemModel *inputModel, QStandardItemModel *outputModel,
                            int operationIndex, double scalarValue)
{
    outputModel->clear();
    int inputModelRowCount = inputModel->rowCount();
    int inputModelColumnCount = inputModel->columnCount();
    Matrix<double> matrixA(inputModelRowCount, inputModelColumnCount, 0.0);
    for(int i = 0; i < inputModelRowCount; ++i)
        for(int j = 0; j < inputModelColumnCount; ++j)
            matrixA.setValueAt(i, j, getValueAt(inputModel, i, j));
    switch(operationIndex)
    {
         case 0: {
                    int outputModelRowCount = inputModelColumnCount;
                    int outputModelColumnCount = inputModelRowCount;
                    Matrix<double> matrixTranspose = matrixA.transpose();
                    outputModel->setRowCount(outputModelRowCount);
                    outputModel->setColumnCount(outputModelColumnCount);
                    for(int i = 0; i < outputModelRowCount; ++i)
                      for(int j = 0; j < outputModelColumnCount; ++j)
                         appendTo(outputModel, matrixTranspose.getValueAt(i,j));
                 }
                 break;
         case 1: {
                   Matrix<double> matrixInverse = matrixA.inverse();
                   outputModel->setRowCount(inputModelRowCount);
                   outputModel->setColumnCount(inputModelColumnCount);
                   for(int i = 0; i < inputModelRowCount; ++i)
                      for(int j = 0; j < inputModelColumnCount; ++j)
                          appendTo(outputModel, matrixInverse.getValueAt(i,j));
                 }
                 break;
      case 2: {
                  int exponent = static_cast<int>(scalarValue);
                  Matrix<double> matrixPower = matrixA.power(exponent);
                  for(int i = 0; i < inputModelRowCount; ++i)
                     for(int j = 0; j < inputModelColumnCount; ++j)
#ifdef DEBUG
                         qDebug() << matrixPower.getValueAt(i, j);
#endif
                  outputModel->setRowCount(inputModelRowCount);
                  outputModel->setColumnCount(inputModelColumnCount);
                  for(int i = 0; i < inputModelRowCount; ++i)
                     for(int j = 0; j < inputModelColumnCount; ++j)
                          appendTo(outputModel, matrixPower.getValueAt(i,j));
               }
               break;
      case 3: {
                  matrixA += scalarValue;
                  outputModel->setRowCount(inputModelRowCount);
                  outputModel->setColumnCount(inputModelColumnCount);
                  for(int i = 0; i < inputModelRowCount; ++i)
                     for(int j = 0; j < inputModelColumnCount; ++j)
                         appendTo(outputModel, matrixA.getValueAt(i,j));
              }
              break;
      case 4: {
                 matrixA -= scalarValue;
                 outputModel->setRowCount(inputModelRowCount);
                 outputModel->setColumnCount(inputModelColumnCount);
                  for(int i = 0; i < inputModelRowCount; ++i)
                      for(int j = 0; j < inputModelColumnCount; ++j)
                         appendTo(outputModel, matrixA.getValueAt(i,j));
              }
              break;
      case 5: {
                matrixA *= scalarValue;
                outputModel->setRowCount(inputModelRowCount);
                outputModel->setColumnCount(inputModelColumnCount);
                   for(int i = 0; i < inputModelRowCount; ++i)
                      for(int j = 0; j < inputModelColumnCount; ++j)
                          appendTo(outputModel, matrixA.getValueAt(i,j));
              }
              break;
      case 6: {
                matrixA /= scalarValue;
                outputModel->setRowCount(inputModelRowCount);
                outputModel->setColumnCount(inputModelColumnCount);
                  for(int i = 0; i < inputModelRowCount; ++i)
                     for(int j = 0; j < inputModelColumnCount; ++j)
                         appendTo(outputModel, matrixA.getValueAt(i,j));
              }
              break;
      case 7: {
                 outputModel->setRowCount(1);
                 outputModel->setColumnCount(1);
                 double det = matrixA.determinant();
                 appendTo(outputModel, det);
              }
              break;
      case 8: {
                 outputModel->setRowCount(1);
                 outputModel->setColumnCount(1);
                 double rank = matrixA.rank();
                 appendTo(outputModel, rank);
              }
              break;
      default: break;
    }

}
void Widget::on_pushButtonA_clicked()
{
   unaryOperation(mModelA, mModelA2, ui->comboBoxA->currentIndex(), ui->doubleSpinBoxScalarA->value());
}
void Widget::on_pushButtonB_clicked()
{
   unaryOperation(mModelB, mModelB2, ui->comboBoxB->currentIndex(), ui->doubleSpinBoxScalarB->value());
}
void Widget::on_pushButtonR_clicked()
{
   unaryOperation(mModelR, mModelR2, ui->comboBoxR->currentIndex(), ui->doubleSpinBoxScalarR->value());
}
void Widget::on_pushButtonCalculate_clicked()
{
    mModelR->clear();
    int matrixARowCount = mModelA->rowCount();
    int matrixAColumnCount = mModelA->columnCount();
    int matrixBRowCount = mModelB->rowCount();
    int matrixBColumnCount = mModelB->columnCount();
    Matrix<double> matrixA(matrixARowCount, matrixAColumnCount, 0.0);
    for(int i = 0; i < matrixARowCount; ++i)
        for(int j = 0; j < matrixAColumnCount; ++j)
            matrixA.setValueAt(i, j, getValueAt(mModelA, i, j));
    Matrix<double> matrixB(matrixBRowCount, matrixBColumnCount, 0.0);
    for(int i = 0; i < matrixBRowCount; ++i)
        for(int j = 0; j < matrixBColumnCount; ++j)
            matrixB.setValueAt(i, j, getValueAt(mModelB, i, j));
    switch (ui->comboBoxBinaryOperation->currentIndex())
    {
    case 0: {
              mModelR->setRowCount(matrixARowCount);
              mModelR->setColumnCount(matrixAColumnCount);
              Matrix<double> matrixR = matrixA + matrixB;
              for(int i = 0; i < matrixARowCount; ++i)
                for(int j = 0; j < matrixAColumnCount; ++j)
                    appendTo(mModelR, matrixR.getValueAt(i,j));
            }
            break;
    case 1: {
              mModelR->setRowCount(matrixARowCount);
              mModelR->setColumnCount(matrixAColumnCount);
              Matrix<double> matrixR = matrixA - matrixB;
              for(int i = 0; i < matrixARowCount; ++i)
                for(int j = 0; j < matrixAColumnCount; ++j)
                    appendTo(mModelR, matrixR.getValueAt(i,j));
            }
            break;
    case 2: {
              mModelR->setRowCount(matrixARowCount);
              mModelR->setColumnCount(matrixBColumnCount);
              Matrix<double> matrixR = matrixA * matrixB;
              for(int i = 0; i < matrixARowCount; ++i)
                for(int j = 0; j < matrixBColumnCount; ++j)
                    appendTo(mModelR, matrixR.getValueAt(i,j));
            }
             break;
    default: break;
    }

}
void Widget::appendTo(QStandardItemModel *model, double value) const
{
    const int rowCount = model->rowCount();
    const int colCount = model->columnCount();
    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < colCount; ++j)
        {
            if(!model->item(i, j))
            {
              model->setItem(i, j, new QStandardItem(QString::number(value)));
              return;
            }
        }
}
void Widget::on_pushButtonExit_clicked()
{
   close();
}
void Widget::on_spinBoxRowNumberA_valueChanged(int arg1)
{
    mModelA->setRowCount(arg1);
    // Синхронизируем размеры матрицы-результата бинарных операций
    switch (ui->comboBoxBinaryOperation->currentIndex())
    {
      case 0:
      case 1: ui->spinBoxRowNumberB->setValue(arg1);
              mModelR->setRowCount(arg1);
              break;
      case 2: mModelR->setRowCount(arg1);
              break;
      default: break;
    }
    // Синхронизируем размеры матрицы-результата унарных операций над матрицей-результатом бинарных операций
    synchronizeMatrixes(mModelR, mModelR2,ui->comboBoxR->currentIndex());
    //synchronizeMatrixR2(ui->comboBoxR->currentIndex());
    // Синхронизируем размеры матрицы-результата унарных операций над матрицей A (первый операнд)
    //бинарных операций
    //synchronizeMatrixA2(ui->comboBoxA->currentIndex());
    //synchronizeMatrixB2(ui->comboBoxB->currentIndex());
    synchronizeMatrixes(mModelA, mModelA2,ui->comboBoxA->currentIndex());
    synchronizeMatrixes(mModelB, mModelB2,ui->comboBoxB->currentIndex());
}
void Widget::on_spinBoxColumnNumberA_valueChanged(int arg1)
{
    mModelA->setColumnCount(arg1);
    switch (ui->comboBoxBinaryOperation->currentIndex())
    {
      case 0:
      case 1: //mModelB->setColumnCount(arg1);
              ui->spinBoxColumnNumberB->setValue(arg1);
              mModelR->setColumnCount(arg1);
              break;
      case 2: //mModelB->setRowCount(arg1);
              ui->spinBoxRowNumberB->setValue(arg1);
              break;
      default: break;
    }
    synchronizeMatrixes(mModelR, mModelR2,ui->comboBoxR->currentIndex());
    synchronizeMatrixes(mModelA, mModelA2,ui->comboBoxA->currentIndex());
    synchronizeMatrixes(mModelB, mModelB2,ui->comboBoxB->currentIndex());
}
void Widget::on_spinBoxRowNumberB_valueChanged(int arg1)
{
    mModelB->setRowCount(arg1);
    switch (ui->comboBoxBinaryOperation->currentIndex())
    {
      case 0:
      case 1: //mModelA->setRowCount(arg1);
              ui->spinBoxRowNumberA->setValue(arg1);
              mModelR->setRowCount(arg1);
              break;
      case 2: //mModelA->setColumnCount(arg1);
              ui->spinBoxColumnNumberA->setValue(arg1);
              break;
      default: break;
    }
    synchronizeMatrixes(mModelR, mModelR2,ui->comboBoxR->currentIndex());
    synchronizeMatrixes(mModelA, mModelA2,ui->comboBoxA->currentIndex());
    synchronizeMatrixes(mModelB, mModelB2,ui->comboBoxB->currentIndex());
}
void Widget::on_spinBoxColumnNumberB_valueChanged(int arg1)
{
    mModelB->setColumnCount(arg1);
    switch (ui->comboBoxBinaryOperation->currentIndex())
    {
      case 0:
      case 1: //mModelA->setColumnCount(arg1);
              ui->spinBoxColumnNumberA->setValue(arg1);
              mModelR->setColumnCount(arg1);
              break;
      case 2: mModelR->setColumnCount(arg1);
              break;
      default: break;
    }
    synchronizeMatrixes(mModelR, mModelR2,ui->comboBoxR->currentIndex());
    synchronizeMatrixes(mModelA, mModelA2,ui->comboBoxA->currentIndex());
    synchronizeMatrixes(mModelB, mModelB2,ui->comboBoxB->currentIndex());
}
void Widget::on_comboBoxA_currentIndexChanged(int index)
{
    synchronizeMatrixes(mModelA, mModelA2, index);
}
void Widget::on_comboBoxB_currentIndexChanged(int index)
{
    synchronizeMatrixes(mModelB, mModelB2,index);
}
void Widget::on_comboBoxR_currentIndexChanged(int index)
{
    synchronizeMatrixes(mModelR, mModelR2,index);
}
void Widget::on_comboBoxBinaryOperation_currentIndexChanged(int index)
{
    switch(index)
    {
      case 0:
      case 1:  ui->spinBoxRowNumberB->setValue(mModelA->rowCount());
               ui->spinBoxColumnNumberB->setValue(mModelA->columnCount());
               break;
      case 2:  ui->spinBoxRowNumberB->setValue(mModelA->columnCount());
               break;
      default: break;
    }
    synchronizeMatrixes(mModelA, mModelA2,ui->comboBoxA->currentIndex());
    synchronizeMatrixes(mModelB, mModelB2,ui->comboBoxB->currentIndex());
    synchronizeMatrixes(mModelR, mModelR2,ui->comboBoxR->currentIndex());
}

double Widget::getValueAt(QStandardItemModel *model, int i, int j) const
{
    if(!model->item(i,j)) return 0.0;
    else return model->item(i,j)->text().toDouble();
}

