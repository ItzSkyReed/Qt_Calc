#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CalculatorWindow;
}
QT_END_NAMESPACE

class CalculatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    CalculatorWindow(QWidget *parent = nullptr);
    ~CalculatorWindow();

private:
    Ui::CalculatorWindow *ui;
    bool is_action_selected; // Флаг, указывающий, что действие было выбрано
    double accumulator; // Переменная для хранения промежуточного результата
    char current_action; // Переменная для хранения текущего действия
    bool is_dot_pressed; // Проверка не была ли нажата точка
    QString saved_num;
private slots:
    void onNumberButtonClicked();
    void onStandartActionClicked();
    void onEqualButtonClicked();
    void onClearButtonClicked();
    void onToCubeButtonClicked();
    void onInverseButtonClicked();
    void on10inNumButtonClicked();
    void onDotButtonClicked();
    void onMSButtonClicked();
    void onMRButtonClicked();
    void onPlusMinusButtonClicked();
    void onMMinusButtonClicked();
    void onMPlusButtonClicked();
    void onMClearButtonClicked();
};
#endif // CALCULATORWINDOW_H
